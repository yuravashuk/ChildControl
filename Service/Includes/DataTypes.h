
#pragma once

#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include "Common.hpp"

/**
 * SOA data struct
 */
typedef struct
{
	std::string*	_names;		// array of process or web page names
	int* 			_hFlags;	// indicate turn on and turn off hours in 00:00 - 23:00
	bool* 			_enable;	// compare process flag
} ProcessPool, WebPool, *pProcessPool, *pWebPool;

/**
 *	Application settings structure
 */
typedef struct
{
	char*	_regionTime;
    char*   _password;
    char*   _language;
	bool	_enableWebServer;
    bool    _enableService;
    bool    _enableWebBlock;
} AppData, *pAppData;



#endif //_DATA_TYPES_H_
