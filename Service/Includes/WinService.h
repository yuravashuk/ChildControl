
#pragma once

#ifndef _WIN_SERVICE_H_
#define _WIN_SERVICE_H_

#include "DataTypes.hpp"
#include "DataDumper.hpp"
#include "TimeController.hpp"
#include "WebService.hpp"
#include "IService.hpp"
#include "Log.hpp"

class WinService : public IService
{
public:
	/**
	 *	Constructor/Destructor. Set inital values to private variables.
	 */
	WinService();
	virtual ~WinService();

	/**
	 *	Start service
	 */
	virtual int Start() override;

	/**
	 *
	 */
	virtual WebService* GetWebService() const override;

	/**
	 *
	 */
	virtual TimeController* GetTimeController() const override;

	/**
	 *
	 */
	virtual pProcessPool GetProcessPool() const override;

	/**
	 *
	 */
	virtual pWebPool GetWebPool() const override;

	/**
	 *
	 */
	virtual bool LoadDataDump() override;

	/** 
	 *
	 */
	virtual size_t GetProcNums() const override;

	/**
	 *
	 */
	virtual size_t GetWebNums() const override;

	/**
	 *
	 */
	virtual bool BlockWebSite(const char* host) override;

	/**
	 *
	 */
	virtual bool UnblockWebSite(const char* host) override;

	/**
	* Static service methods
	*/
	friend VOID WINAPI ThisServiceMain(DWORD, LPTSTR*);
	friend VOID WINAPI ThisServiceHandler(DWORD);

protected:
	/**
	 *	Wrapper methods for static ThisServiceMain & ThisServiceHandle
	 */
	void ThisServiceHandler(DWORD);
	void ThisServiceMain(DWORD, LPTSTR*);

	/**
	 *	Change service status
	 */
	void SetStatus(DWORD, DWORD);

	/**
	 *	Service basic events
	 */
	virtual void OnStop();
	virtual void OnContinue();
	virtual void OnPause();
	virtual void OnPauseIdle();
	virtual void OnIdle();
	virtual void OnMainLoop();

private:
	SERVICE_STATUS			_serviceStatus;
	SERVICE_STATUS_HANDLE	_statusHandle;
	HANDLE					_serviceStopEvent;
	SERVICE_TABLE_ENTRY		_serviceTable[2];

	HANDLE					_hProcessSnap;
	PROCESSENTRY32			_pe32;
	DWORD					_dwDesiredAccess;
	BOOL					_bInheritHandle;

private:
	/**
	 *	0 - WebService::ReviceCommand
	 *	1 - WebService::UpdateLocalServer
	 *	2 - Timer::Update
	 *	3 -	WinService::OnMainLoop
	 */
	std::thread		_threads[4];

	/**
	 *	Web service class
	 */
	WebService*		_webService;

	/** 
	 *	Time controller
	 */
	TimeController*	_timer;

	/** 
	 *	Process list
	 */
	pProcessPool	_procPool;

	/** 
	 *	Web site list
	 */
	pWebPool		_webPool;

	/**
	 *
	 */
	DataDumper<std::string, 4> _namesProcDumper;

	/**
	 *
	 */
	DataDumper<std::string, 4> _namesWebDumper;

	/**
	 *
	 */
	DataDumper<int, 4>			_hFlagsProcDumper;

	/**
	 *
	 */
	DataDumper<int, 4>			_hFlagsWebDumper;

	size_t					_numOfProc;
	size_t					_numOfWeb;

	bool					_isDateSet;
};



#endif //_WIN_SERVICE_H_
