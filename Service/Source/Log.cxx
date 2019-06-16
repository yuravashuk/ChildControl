
#include "../Includes/Log.hpp"

Log* Log::mInstance = 0;

Log::Log()
	: mFilePtr(nullptr)
	, mFileName("")
{ }

Log::Log(const Log &)
	: mFilePtr(nullptr)
	, mFileName("")
{ }

Log* Log::GetInstance()
{
	if (mInstance == nullptr)
		mInstance = new Log;

	return mInstance;
}

void Log::SetOutputFile(char* fname)
{
	mFileName = fname;
}

void Log::Write(char* msg)
{
	mFilePtr = fopen(mFileName, "a");
	if (mFilePtr == NULL)
		return;

	fprintf(mFilePtr, "%s\n", msg);
	fclose(mFilePtr);
}

void Log::Close()
{
	fclose(mFilePtr);
}

FILE* Log::GetFilePtr() const
{
	return mFilePtr;
}
