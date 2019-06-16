
#include "../Includes/TimeController.hpp"

TimeController::TimeController()
	: mService(nullptr)
	, mTime(nullptr)
	, mAligned(false)
{ }

TimeController::~TimeController()
{
	Log::GetInstance()->Write("Time controller Destroyed!");
}

void TimeController::Initialize(IService* service)
{
	Log::GetInstance()->Write("Timer initialized!");

	time_t now = time(0);
	mTime = localtime(&now);

	mService = service;
	mService->LoadDataDump();
}

int TimeController::GetDayNum() const
{
	return mTime->tm_wday;
}

void TimeController::UpdateEnableFlags()
{
	size_t	i = 0, n = 0, m = 0;		// proc and web nums

	// First get all pointers to avoid method calls insie cycle
	WebService* pWServ = mService->GetWebService();
	pProcessPool pProc = mService->GetProcessPool();
	pWebPool pWeb = mService->GetWebPool();

	// Update enable flags for loaded data
	n = mService->GetProcNums();
	m = mService->GetWebNums();

	// now set only enabled processes
	for (i = 0; i < n; ++i)
	{
		pProc->Enable[i] = GetBitInInt(pProc->HFlags[i], mTime->tm_hour);
	}

	for (i = 0; i < m; ++i)
	{
		pWeb->Enable[i] = GetBitInInt(pWeb->HFlags[i], mTime->tm_hour);
	}

	// One per update
	for (size_t i = 0; i < m; ++i)
	{
		if (pWeb->Enable[i])
		{
			mService->UnblockWebSite(pWeb->Names[i].c_str());
			continue;
		}

		mService->BlockWebSite(pWeb->Names[i].c_str());
	}
}

void TimeController::Update()
{
	Log::GetInstance()->Write("Start time controller update loop!");

	size_t	i = 0;				// counter
	time_t	now;				// time now
	tm*		lTime = nullptr;	// time struct (_time is old time wich compare with new time)

	// get current time and date, from web if we can
	now = time(0);
	lTime = localtime(&now);

	// check for wating time to 00:00, 01:00, 02:00 ... etc.
	// sleep use miliseconds:
	// 1 s = 1000 ms
	// 1 m = 60 s
	// 1 h = 60 m
	// 3600000s = 1 hour
	mTime = lTime;
	if (!mAligned)
		Sleep(((59 - lTime->tm_min) * 60) * 1000); // wait some minutes to start update in aligned time
						
	// now we calculate time with static offset = 1 hour
	mAligned = true;
	
	// General time update loop
	while (true)
	{
		// get current time and date, from web if we can
		now = time(0);
		lTime = localtime(&now);

		// new day started, need to reload all dump data
		if (mTime->tm_wday < lTime->tm_wday)
		{
			mService->LoadDataDump();
		}

		// 
		UpdateEnableFlags();

		// set old time value to compare day cycle
		mTime = lTime;
		
		Sleep(3600000); // wait for an one hour
	}
}