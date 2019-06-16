
#pragma once

#ifndef _ISERVICE_H_
#define _ISERVICE_H_

#include "DataTypes.hpp"

class WebService;
class TimeController;

class IService
{
public:
	virtual int Start(void) = 0;
	virtual WebService* GetWebService(void) const = 0;
	virtual TimeController* GetTimeController(void) const = 0;
	virtual pProcessPool GetProcessPool(void) const = 0;
	virtual pWebPool GetWebPool(void) const = 0;
	virtual bool LoadDataDump() = 0;
	virtual size_t GetProcNums(void) const = 0;
	virtual size_t GetWebNums(void) const = 0;
	virtual bool BlockWebSite(const char* host) = 0;
	virtual bool UnblockWebSite(const char* host) = 0;
};

#endif //_ISERVICE_H_