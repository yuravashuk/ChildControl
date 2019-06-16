
#pragma once

#ifndef _COMMON_H_
#define _COMMON_H_

/**
 *	Supported platforms
 */
#define PLATFORM_WINDOWS 1
#define PLATFORM_LINUX 2
#define PLATFORM_MAC 3

/**
 *	Detect current platform
 */
#if defined(_WIN32) || defined(_WIN64)
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__linux__)
	#define PLATFORM PLATFORM_LINUX
#elif defined(__APPLE__)
	#define PLATFORM PLATFORM_MAC
#endif // PLATFORM

/**
 *	Common includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <cstdlib>

/**
 *	Windows includes
 */
#if PLATFORM == PLATFORM_WINDOWS
	#include <windows.h>
	// #include <WinSock2.h> not use this header, it already included in Windows.h
	#include <tchar.h>
	#include <process.h>
	#include <tlhelp32.h>
	#include <direct.h>

	#define GetCurrentDir _getcwd 
	// Need precompile socket library
	#pragma comment( lib, "wsock32.lib" )
#endif // PLATFORM_WINDOWS

/**
 *	Linux and OS X includes
 */
#if PLATFORM == PLATFORM_LINUX || PLATFORM == PLATFORM_MAC
	#include <stdio.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <sys/time.h>
	#include <unistd.h>
	#include <string.h>
	#include <signal.h>
	#include <dirent.h>
	#include <errno.h>
	#include <fcntl.h>
	#include <syslog.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <netdb.h>
	#include <resolv.h>

	#define Sleep(x) usleep((x)*1000)
	#define GetCurrentDir getcwd 
#endif // PLATFORM_LINUX & PLATFORM_MAC

/**
 *	String defines
 */
#define KSERVICE_INSTANCE_EXP_1 "Service Instance not incialized!"
#define KSERVICE_NAME "Service"
#define KSERVICE_DISPLAY_NAME L"Task Service Manager";




#endif //_COMMON_H_
