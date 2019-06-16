
#pragma once

#ifndef _LOG_H_
#define _LOG_H_

#include "Common.hpp"

class Log
{
public:
	static Log* GetInstance();
	void SetOutputFile(char* fname);
	void Write(char* msg);
	void Close();
	FILE* GetFilePtr() const;

private:
	static Log* mInstance;
	FILE*		mFilePtr;
	char*		mFileName;

private:
	Log();
	Log(const Log&);
};


#endif //_LOG_H_