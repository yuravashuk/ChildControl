
#include "../Includes/WebService.hpp"

WebService::WebService() 
	: mService(nullptr)
	, mReadBytes(0)
	, mPort(80)
{ }

WebService::~WebService()
{
	Log::GetInstance()->Write("Web Service Destriyed!");
}

bool WebService::Initialize(IService* service)
{
#if PLATFORM == PLATFORM_WINDOWS
	WSADATA WsaData;
	if (WSAStartup(MAKEWORD(2, 2), &WsaData) != NO_ERROR)
	{
		Log::GetInstance()->Write("Failed initialize wsa startup!");
		return false;
	}
#endif
	mListener[0] = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#if PLATFORM == PLATFORM_WINDOWS
	unsigned long ulMode = 1;
	ioctlsocket(mListener[0], FIONBIO, (unsigned long*)&ulMode);
#else
	// use fnctl
#endif
	if (mListener[0] < 0)
	{
		Log::GetInstance()->Write("Failed create listener socket!");
		return false;
	}

	// setup address struct params
	mAddress[0].sin_family = AF_INET;
	mAddress[0].sin_port = htons(1234);
	mAddress[0].sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(mListener[0], (struct sockaddr*)&mAddress[0], sizeof(mAddress[0])) < 0)
	{
		Log::GetInstance()->Write("Faild bind listener socket!");
		return false;
	}

	// set listener
	::listen(mListener[0], 5);
	mService = service;

	Log::GetInstance()->Write("Web initialized!");

	return true;
}

void WebService::Destroy()
{
#if PLATFORM == PLATFORM_WINDOWS
	WSACleanup();
#endif
	Log::GetInstance()->Write("Web Destroyed!");
}

void WebService::ReceiveCommand()
{
	bool inputTask = false;
	memset(mBuffer, 0, KBUFFER_SIZE);
	while (true)
	{
		// accept client socket
		mSocket[0] = ::accept(mListener[0], NULL, NULL);
		if (mSocket < 0) continue; //printf("Failed accept socket!\n");

		// read command from client
		while (!inputTask)
		{
			mReadBytes = ::recv(mSocket[0], mBuffer, KBUFFER_SIZE, 0);
			if (mReadBytes <= 0) inputTask = true;
		}

		// select task
		if (inputTask)
		{
			if (!strcmp(mBuffer, "UPDD")) // UPDATE DATA
			{
				mService->LoadDataDump();
				::send(mSocket[0], "done", sizeof(char)*4, 0);
				memset(mBuffer, 0, KBUFFER_SIZE);
			}
			inputTask = false;
		}

#if PLATFORM == PLATFORM_WINDOWS
		::closesocket(mSocket[0]);
#else
		::close(_socket[0]);
#endif
	}
}

void WebService::UpdateLocalServer()
{
	mListener[1] = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPPROTO_TCP
#if PLATFORM == PLATFORM_WINDOWS
	unsigned long ulMode = 1;
	ioctlsocket(mListener[1], FIONBIO, (unsigned long*)&ulMode);
#else
	// use fnctl
#endif
	if (mListener[1] < 0)
	{
		Log::GetInstance()->Write("Failed create server listener socket!");
		return;
	}
	// setup address struct params
	mAddress[1].sin_family = AF_INET;
	mAddress[1].sin_port = htons(80);
	mAddress[1].sin_addr.s_addr = htonl(INADDR_ANY);
	if (::bind(mListener[1], (struct sockaddr*)&mAddress[1], sizeof(mAddress[1])) < 0)
	{
		Log::GetInstance()->Write("Faild bind server listener socket!");
		return;
	}

	::listen(mListener[1], 5);

	while (true)
	{
		mSocket[1] = ::accept(mListener[1], NULL, NULL);
		if (mSocket[1] < 0) continue; // printf("Faild accept socket!\n");

		// send web page to browser
		::send(mSocket[1], kWebPage, sizeof(kWebPage) - 1, 0);

#if PLATFORM == PLATFORM_WINDOWS
		::closesocket(mSocket[1]);
#else
		::close(_socket[1]);
#endif
	}
}

bool WebService::GetTimeFromWeb(char*& time, char*& day)
{
	// clear local variable
	memset(time, 0, sizeof(char) * 6);
	memset(day, 0, sizeof(char)* 10);

	// HTTP settings
	char timeHost[] = "time.is"; // "kek.com.ivan";
	char timeRegion[] = "ukraine";
	char dayHost[] = "kakoysegodnyadennedeli.ru";

	char* page = GetPageFromWeb(timeHost, timeRegion);
	// Get only time from HTML Page - find <div id="twd">17:40:18</div>
	char* begin = strstr(page, "<div id=\"twd\">");
	if (begin == nullptr) return false;
	strncpy(time, begin + 14, 5);
	free(page);

	// Need download new page
	page = GetPageFromWeb(dayHost, "");
	begin = strstr(page, "<div class=\"dayContainer\">\n<h1 class=\"day\">");

	if (begin == nullptr) return false;
	
	strncpy(day, begin + 16, 10);
	
	return true;
}

char* WebService::GetPageFromWeb(char* hostname, char* pagename)
{
	// create query
	char *query = (char*)malloc(2048);

	if (query == nullptr)
	{
		return nullptr;
	}

	strcpy(query, "GET /");
	strcat(query, hostname);
	strcat(query, " HTTP/1.0\nHost: ");
	strcat(query, pagename);
	strcat(query, "\nUser-agent: MMozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/33.0.1750.154 Safari/537.36)");
	strcat(query, "\nAccept: */*\n\n");

	// get ip address from url
	struct hostent *hp;
	if (!(hp = gethostbyname(hostname)))
	{
		free(query);
		return nullptr;
	}

	// initialize socket
#if PLATFORM == PLATFORM_WINDOWS
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
	int sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif
	if (sock < 0)
	{
		free(query);
		return nullptr;
	}

#if PLATFORM == PLATFORM_WINDOWS
	SOCKADDR_IN haddr;
#else
	struct sockaddr_in haddr;
#endif 
	haddr.sin_port = htons(80);
	haddr.sin_family = AF_INET;
	haddr.sin_addr.s_addr = *((unsigned long*)hp->h_addr);

	// connect to web server
#if PLATFORM == PLATFORM_WINDOWS
	if (::connect(sock, (SOCKADDR*)(&haddr), sizeof(haddr)) != 0)
#else
	if (::connect(sock, (sockaddr*)(&haddr), sizeof(haddr)) != 0)
#endif
	{
		free(query);
		return nullptr;
	}

	// Send HTTP request
	::send(sock, query, (int)strlen(query), 0);

	// Read data from web server
	int const size = 709880;	// size of data
	char* htmlBuf = (char*)malloc(size);			// html page buffer

	if (htmlBuf == nullptr)
	{
		return nullptr;
	};

	int readBytes;
	int totalDownloadedLen = 0;

	while ((readBytes = ::recv(sock, &htmlBuf[totalDownloadedLen], size - totalDownloadedLen, 0)) > 0) {
		totalDownloadedLen += readBytes;
	}

#if PLATFORM == PLATFORM_WINDOWS
	::closesocket(sock);
#else
	::close(sock);
#endif

	return htmlBuf;
}


