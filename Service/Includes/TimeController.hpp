
#pragma once

#ifndef _TIME_CONTROLLER_H_
#define _TIME_CONTROLLER_H_

#include "Common.hpp"
#include "DataTypes.hpp"
#include "WebService.hpp"
#include "IService.hpp"
#include "Utils.hpp"
#include "Log.hpp"

class TimeController
{
public:
	TimeController();
	virtual ~TimeController();

	void Initialize(IService* service);
	void Update();
	int	 GetDayNum() const;
	void UpdateEnableFlags();

private:
	IService*	mService;
	tm*			mTime;
	bool		mAligned;
};



#endif //_TIME_CONTROLLER_H_
