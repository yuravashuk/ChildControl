
#pragma once

#ifndef _DATA_DUMPER_H_
#define _DATA_DUMPER_H_

/**
*
*/
template<class T, size_t size>
class DataDumper
{
public:

	/**
	*
	*/
	DataDumper()
	{
        mBuffer = nullptr;
		mSize = 0;
	}

	/**
	*
	*/
	~DataDumper()
	{
		Free();
	}

	/**
	*
	*/
	T* Create(size_t Size)
	{
		// Free a previously created buffer
		Free();
		return (mBuffer = new T[(mSize = Size)]);
	}

	/**
	* Free the allocated memory
	*/
	void Free()
	{
        if (mBuffer != nullptr)
		{
			delete[] mBuffer;
			mBuffer = nullptr;
		}
		mSize = 0;
	}

	/**
	*
	*/
	bool Save(char *Filename)
	{
		FILE *fp;
		// Make sure there’s something to write
		if (mBuffer != nullptr && mSize) {
			// Open file, write size and data
			if ((fp = fopen(Filename, "wb")) != nullptr) {
				fwrite(&mSize, sizeof(size_t), 1, fp);
				fwrite(mBuffer, sizeof(T), mSize, fp);
				fclose(fp);
				return true;
			}
		}
		return false;
	}

	/**
	*
	*/
	bool SaveArray(char *Filename)
	{
		FILE *fp;
		size_t len = 0;
		// Make sure there’s something to write
		if (mBuffer != nullptr && mSize) {
			// Open file, write size and data
			if ((fp = fopen(Filename, "wb")) != nullptr) {
				fwrite(&mSize, sizeof(size_t), 1, fp); // num of processes
				for (size_t i = 0; i < mSize; ++i)
				{
					len = reinterpret_cast<std::string*>(mBuffer)[i].length() + 1; // get string len
					fwrite(&len, sizeof(size_t), 1, fp); // write string len
					fwrite(&reinterpret_cast<std::string*>(mBuffer)[i][0], len, 1, fp);
				}

				fclose(fp);
				return true;
			}
		}
		return false;
	}

	T* Load(char *Filename, size_t* Size)
	{
		FILE *fp;

		// Free a prior buffer
		Free();

		if ((fp = fopen(Filename, "rb")) != NULL) {

			// Read in size and data
			fread(&mSize, sizeof(size_t), 1, fp);

			if ((mBuffer = new T[mSize]) != nullptr)
                fread(mBuffer, sizeof(T), mSize, fp);

			fclose(fp);

			// Store size to return
			if (Size != NULL)
				*Size = mSize;

			// return pointer
			return mBuffer;
		}
		return nullptr;
	}

	T* LoadArray(char *Filename, size_t* Size)
	{
		FILE *fp;
		size_t len = 0;
		Free();
		if ((fp = fopen(Filename, "rb")) != NULL) {
			// Read in size and data
			fread(&mSize, sizeof(size_t), 1, fp);
			if ((mBuffer = new T[mSize]) != nullptr)
			{
				for (size_t i = 0; i < mSize; ++i)
				{
					fread(&len, sizeof(size_t), 1, fp); // get len of string
					fread(&reinterpret_cast<std::string*>(mBuffer)[i][0], len, 1, fp);
				}
			}
			fclose(fp);

			// Store size to return
			if (Size != NULL)
				*Size = mSize;

			// return pointer
			return mBuffer;
		}
		return nullptr;
	}

protected:
	// Data buffer and size
	T*		mBuffer;
	size_t	mSize;
};

#endif //_DATA_DUMPER_H_
