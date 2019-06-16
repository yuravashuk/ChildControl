
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
	SERVICE_STATUS			mServiceStatus;
	SERVICE_STATUS_HANDLE	mStatusHandle;
	HANDLE					mServiceStopEvent;
	SERVICE_TABLE_ENTRY		mServiceTable[2];

	HANDLE					mHProcessSnap;
	PROCESSENTRY32			mPe32;
	DWORD					mDesiredAccess;
	BOOL					mInheritHandle;

private:
	/**
	 *	0 - WebService::ReviceCommand
	 *	1 - WebService::UpdateLocalServer
	 *	2 - Timer::Update
	 *	3 -	WinService::OnMainLoop
	 */
	std::thread		mThreads[4];

	/**
	 *	Web service class
	 */
	WebService*		mWebService;

	/** 
	 *	Time controller
	 */
	TimeController*	mTimer;

	/** 
	 *	Process list
	 */
	pProcessPool	mProcPool;

	/** 
	 *	Web site list
	 */
	pWebPool		mWebPool;

	/**
	 *
	 */
	DataDumper<std::string, 4> mNamesProcDumper;

	/**
	 *
	 */
	DataDumper<std::string, 4> mNamesWebDumper;

	/**
	 *
	 */
	DataDumper<int, 4>	mFlagsProcDumper;

	/**
	 *
	 */
	DataDumper<int, 4>	mFlagsWebDumper;

	size_t	mNumOfProc;
	size_t	mNumOfWeb;

	bool mIsDateSet;
};



#endif //_WIN_SERVICE_H_
