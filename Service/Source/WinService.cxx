
#include "../Includes/WinService.hpp"

extern WinService* kService;

VOID WINAPI ThisServiceHandler(DWORD fdwControl)
{
	kService->ThisServiceHandler(fdwControl);
}

VOID WINAPI ThisServiceMain(DWORD argc, LPTSTR *argv)
{
	kService->ThisServiceMain(argc, argv);
}

WinService::WinService() :	mStatusHandle(NULL),
							mServiceStopEvent(INVALID_HANDLE_VALUE)
{
	mServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	mServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;//|SERVICE_ACCEPT_PAUSE_CONTINUE;
	mServiceStatus.dwWin32ExitCode = NO_ERROR;
	mServiceStatus.dwCheckPoint = 0;

	mDesiredAccess = PROCESS_TERMINATE;
	mInheritHandle = FALSE;

	mNumOfProc = mNumOfWeb = 0;
	mIsDateSet = false;
}

WinService::~WinService()
{
	mNamesProcDumper.Free();
	Log::GetInstance()->Write("Service Destroyed!");
}

int WinService::Start()
{
	mServiceTable[0].lpServiceName = KSERVICE_NAME;
	mServiceTable[0].lpServiceProc = ::ThisServiceMain;

	mServiceTable[1].lpServiceName = NULL;
	mServiceTable[1].lpServiceProc = NULL;

	return StartServiceCtrlDispatcher(mServiceTable);
}

void WinService::ThisServiceMain(DWORD dwArgc, LPTSTR *lpszArgv)
{
	mStatusHandle = RegisterServiceCtrlHandler(KSERVICE_NAME, ::ThisServiceHandler);
	//SetStatus(SERVICE_START_PENDING, 1000);
	SetStatus(SERVICE_RUNNING, 0);

	Log::GetInstance()->SetOutputFile("C:\\ServiceLog.txt");

	mProcPool = new ProcessPool;
	mWebPool = new WebPool;

	mWebService = new WebService;
	mWebService->Initialize(this);

	mTimer = new TimeController;
	mTimer->Initialize(this);

	mThreads[0] = std::thread(&WebService::ReceiveCommand, mWebService);
	mThreads[1] = std::thread(&WebService::UpdateLocalServer, mWebService);
	mThreads[2] = std::thread(&TimeController::Update, mTimer);
	mThreads[3] = std::thread(&WinService::OnMainLoop, this);

	for (size_t i = 0; i < 4; ++i)
		if (mThreads[i].joinable()) mThreads[i].join();
}

bool WinService::LoadDataDump()
{
	int dayId = mTimer->GetDayNum();
	char fname[300];
	char day[1];
	_itoa(dayId, day, 10);

	Log::GetInstance()->Write("Data Loading ...");
	//if (_procPool->_enable != nullptr) free(_procPool->_enable);

	/**
	 *	Process data
	 */
	memset(fname, 0, 300);
	strcpy(fname, GetSystemRoot());
	strcat(fname, "\\data\\");
	strcat(fname, day);
	strcat(fname, "nms32prc_dmp.bin");

	mProcPool->Names = mNamesProcDumper.LoadArray(fname, &mNumOfProc);

	if (mProcPool->Names != nullptr)
	{
		Log::GetInstance()->Write(fname);
		Log::GetInstance()->Write("Loaded succesed!");
	}
	
	memset(fname, 0, 300);
	strcpy(fname, GetSystemRoot());
	strcat(fname, "\\data\\");
	strcat(fname, day);
	strcat(fname, "hflg32prc_dmp.bin");

	mProcPool->HFlags = mFlagsProcDumper.Load(fname, &mNumOfProc);
	if (mProcPool->HFlags != nullptr)
	{
		Log::GetInstance()->Write(fname);
		Log::GetInstance()->Write("Loaded succesed!");
	}
	mProcPool->Enable = (bool*)malloc(sizeof(bool)*mNumOfProc);


	/**
	 *	Web pages data
	 */
	memset(fname, 0, 300);
	strcpy(fname, GetSystemRoot());
	strcat(fname, "\\data\\");
	strcat(fname, day);
	strcat(fname, "nms32web_dmp.bin");
	mWebPool->Names = mNamesWebDumper.LoadArray(fname, &mNumOfWeb);
	if (mWebPool->Names != nullptr)
	{
		Log::GetInstance()->Write(fname);
		Log::GetInstance()->Write("Loaded succesed!");
	}

	memset(fname, 0, 300);
	strcpy(fname, GetSystemRoot());
	strcat(fname, "\\data\\");
	strcat(fname, day);
	strcat(fname, "hflg32web_dmp.bin");
	mWebPool->HFlags = mFlagsWebDumper.Load(fname, &mNumOfWeb);
	if (mWebPool->HFlags != nullptr)
	{
		Log::GetInstance()->Write(fname);
		Log::GetInstance()->Write("Loaded succesed!");
	}
	Log::GetInstance()->Write("Data Loaded!");
	mWebPool->Enable = (bool*)malloc(sizeof(bool)*mNumOfWeb);

	mTimer->UpdateEnableFlags();

	// enable main loop
	mIsDateSet = true;

	return true;
}

void WinService::OnMainLoop()
{
	Log::GetInstance()->Write("Begin main loop!");

	do
	{
		switch (mServiceStatus.dwCurrentState)
		{
		case SERVICE_RUNNING:
			OnIdle();
			break;
		case SERVICE_PAUSE_PENDING:
			OnPause();
			SetStatus(SERVICE_PAUSED, 0);
			break;
		case SERVICE_PAUSED:
			OnPauseIdle();
			break;
		case SERVICE_CONTINUE_PENDING:
			OnContinue();
			SetStatus(SERVICE_RUNNING, 0);
			break;
		case SERVICE_STOP_PENDING:
			OnStop();
			SetStatus(SERVICE_STOPPED, 0);
			break;
		default:
			mServiceStatus.dwCurrentState = SERVICE_STOPPED;
			break;
		};
		
		mHProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (mHProcessSnap == INVALID_HANDLE_VALUE)
		{
			//Log::GetInstance()->Write("_hProcessSnap == INVALID_HANDLE_VALUE");
			continue;
		}
		mPe32.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(mHProcessSnap, &mPe32))
		{
			//Log::GetInstance()->Write("!Process32First(_hProcessSnap, &_pe32");
			CloseHandle(mHProcessSnap);
			continue;
		}
		do
		{
			if (!mIsDateSet || mNumOfProc == 0) continue; // wait for timer prepare date and time
			for (size_t i = 0; i < mNumOfProc; ++i) //for (size_t i = _numOfProc - 1; i != 0; --i)
			{
				//Log::GetInstance()->Write("Inside for prc!");
				if (!mProcPool->Enable[i])
				{
					if (!strcmp(mProcPool->Names[i].c_str(), mPe32.szExeFile))
					{
						//Log::GetInstance()->Write(" -- Application killed!");
						HANDLE hProcess = OpenProcess(mDesiredAccess, mInheritHandle, mPe32.th32ProcessID);
						if (hProcess == NULL) continue;
						BOOL result = TerminateProcess(hProcess, 1);
						CloseHandle(hProcess);
					}
				}
			}
		} while (Process32Next(mHProcessSnap, &mPe32));
		CloseHandle(mHProcessSnap);
	} while (mServiceStatus.dwCurrentState != SERVICE_STOPPED);
}

void WinService::SetStatus(DWORD dwCurrentState, DWORD timeout)
{
	mServiceStatus.dwCurrentState = dwCurrentState;
	mServiceStatus.dwWaitHint = timeout;
	SetServiceStatus(mStatusHandle, &mServiceStatus);
}

#define OP_TIMEOUT 1000
void WinService::ThisServiceHandler(DWORD fdwControl)
{
	switch (fdwControl)
	{
	case SERVICE_CONTROL_STOP:
		//fShutdown = FALSE;
		SetStatus(SERVICE_STOP_PENDING, OP_TIMEOUT);
		break;
	case SERVICE_CONTROL_PAUSE:
		SetStatus(SERVICE_PAUSE_PENDING, OP_TIMEOUT);
		break;
	case SERVICE_CONTROL_CONTINUE:
		SetStatus(SERVICE_CONTINUE_PENDING, OP_TIMEOUT);
		break;
	case SERVICE_CONTROL_INTERROGATE:
		SetStatus(mServiceStatus.dwCurrentState, 0);
		break;
	case SERVICE_CONTROL_SHUTDOWN:
		//fShutdown = TRUE;
		SetStatus(SERVICE_STOP_PENDING, OP_TIMEOUT);
		break;
	default:
		break;
	}
}

WebService* WinService::GetWebService() const
{
	return mWebService;
}

TimeController* WinService::GetTimeController() const
{
	return mTimer;
}

pProcessPool WinService::GetProcessPool() const
{
	return mProcPool;
}

pWebPool WinService::GetWebPool() const
{
	return mWebPool;
}

size_t WinService::GetProcNums() const
{
	return mNumOfProc;
}

size_t WinService::GetWebNums() const
{
	return mNumOfWeb;
}

bool WinService::BlockWebSite(const char* host)
{
#if PLATFORM == PLATFORM_WINDOWS
	char* path = GetSystemRoot();
	if (path)
		strcat(path, "\\System32\\drivers\\etc\\hosts");
#else
	char* path = GetSystemRoot();
	if (path)
		strcat(path, "./etc/hosts");
#endif
	std::ofstream out;
	out.open(path, std::ios::app);
	if (!out)
		return false;
	else
	{
		out << "127.0.0.1 " << host << std::endl;
		out << "127.0.0.1 www." << host << std::endl;
	}
	out.close();

	return true;
}

bool WinService::UnblockWebSite(const char* host)
{
#if PLATFORM == PLATFORM_WINDOWS
	char* path = GetSystemRoot();
	if (path)
		strcat(path, "/System32/drivers/etc/hosts");
#else
	char* path = GetSystemRoot();
	if (path)
		strcat(path, "./etc/hosts");
#endif
	std::string line = "";
	std::ifstream fl;
	std::ofstream of;
	fl.open(path);
	std::string temp;

	while (std::getline(fl, line))
	{
		for (size_t i = 0; i <= mNumOfWeb; ++i)
		{
			if (mWebPool->Names[i] == "") continue;
			if (!strcmp(line.c_str(), mWebPool->Names[i].c_str())) continue;
		}
		temp = line + "\n";
	}
	fl.close();

	of.open(path);
	of << temp;
	of.close();

	return true;
}

void WinService::OnIdle()
{

}

void WinService::OnContinue()
{

}

void WinService::OnPause()
{

}

void WinService::OnPauseIdle()
{

}

void WinService::OnStop()
{
	// call once when stop service
	mWebService->Destroy();
	mIsDateSet = false;
}