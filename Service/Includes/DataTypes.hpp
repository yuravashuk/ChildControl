
#pragma once

#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include "Common.hpp"

/**
 * SOA data struct
 */
typedef struct
{
	std::string*	Names;	// array of process or web page names
	int* 			HFlags;	// indicate turn on and turn off hours in 00:00 - 23:00
	bool* 			Enable;	// compare process flag
} ProcessPool, WebPool, *pProcessPool, *pWebPool;

/**
 *	Application settings structure
 */
typedef struct
{
	char*	RegionTime;
    char*   Password;
    char*   Language;
	bool	EnableWebServer;
    bool    EnableService;
    bool    EnableWebBlock;
} AppData, *pAppData;



#endif //_DATA_TYPES_H_
