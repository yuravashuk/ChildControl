
#pragma once

#ifndef _DEAMON_H_
#define _DEAMON_H_

#include "DataTypes.h"
#include "WebService.h"
#include "TimeController.h"

class Deamon
{
public:
	Deamon();
	virtual ~Deamon();

	int Start();

protected:
	bool InitSystem();
	bool KillProcess(const char* name);	
	void Run();

private:
	pid_t 	_processId;
	pid_t	_sessionId;
	//FILE*	_filePtr;

	std::thread _threads[4];

	WebService*	_webService;

	TimeController* _timer;
};

#endif //_DEAMON_H_
