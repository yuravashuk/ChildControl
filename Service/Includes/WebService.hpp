
#pragma once

#ifndef _WEB_SERVICE_H_
#define _WEB_SERVICE_H_

#include "Common.hpp"
#include "IService.hpp"
#include "Log.hpp"


#define KBUFFER_SIZE 1024

/**
 *	Local server web page
 */
const char kWebPage[] = "HTTP/1.1 200 Okay\r\nContent-Type: text/html; charset=ISO-8859-4 \r\n\r\n"
						"<html><title>Blocked Page</title><body bgcolor=red>"
						"<h1><center>This web page is blocked by ChildControl...</center></h1>"
						"</body></html>";

class WebService
{
public:
	/**
	 *	Class constructor/destructor
	 */
	WebService();
	virtual ~WebService();

	/**
	 *	Initialize winsock system in windows and command listeners
	 */
	bool Initialize(IService* service);

	/**
	 *	Destroy winsock system in windows
	 */
	void Destroy();

	/**
	 *	Download timer and day from web
	 */
	bool GetTimeFromWeb(char*& time, char*& day);

	/**
	 *	Receive command from ChildControll application
	 */
	void ReceiveCommand();

	/**
	 *	Send HTML page to localhost
	 */
	void UpdateLocalServer();

protected:

	/**
	 *	Download html page by host
	 */
	char* GetPageFromWeb(char* hostname, char* pagename);

private:
	IService*	mService;
	struct sockaddr_in mAddress[2];
#if PLATFORM == PLATFORM_WINDOWS
	SOCKET		mSocket[2];
	SOCKET		mListener[2];
#else
	int			mSocket[2];
	int			mListener[2];
#endif
	char		mBuffer[KBUFFER_SIZE];
	int			mReadBytes;
	uint32_t	mPort;
};


#endif //_WEB_SERVICE_H_
