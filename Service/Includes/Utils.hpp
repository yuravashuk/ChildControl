
#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "Common.hpp"
#include "DataTypes.hpp"

/**
 *
 */
inline int SetBitInInt(int value, int index)
{
	return (value |= 1 << index);
}

/**
 *
 */
inline int UnsetBitInInt(int value, int index)
{
	return (value &= ~(1 << index));
}

/**
 *
 */
inline bool GetBitInInt(int value, int index)
{
	return ((value & (1 << index)) == (1 << index));
}

/**
 *
 */
inline void GetExePath(char*& fpath)
{
	char path[FILENAME_MAX];
        if (!GetCurrentDir(path, sizeof(path))) fpath = path;
                //fpath = "";

	path[sizeof(path)-1] = '\0';
	fpath = path;
}

/**
 *
 */
inline char* GetSystemRoot()
{
#if PLATFORM == PLATFORM_WINDOWS
	char* path = getenv("SystemRoot");
#else
	char* path = _getenv("SystemRoot");
#endif
	return path;
}

inline pAppData LoadSettings(char* filename)
{
    pAppData data = new AppData;
    FILE *fp;
    size_t sz = 0;

    fp = fopen(filename, "rb");

    if (fp != NULL)
    {
        if (data != nullptr)
        {
            // password
            fread(&sz, sizeof(size_t), 1, fp);
            data->Password = (char*)malloc(sizeof(char)*sz);

			if (data->Password != nullptr)
			{
				fread(data->Password, sz, 1, fp);
			}
            
            // region
            fread(&sz, sizeof(size_t), 1, fp);
            data->RegionTime = (char*)malloc(sizeof(char)*sz);

			if (data->RegionTime)
			{
				fread(data->RegionTime, sz, 1, fp);
			}
            
            // language
            fread(&sz, sizeof(size_t), 1, fp);
            data->Language = (char*)malloc(sizeof(char)*sz);

			if (data->Language)
			{
				fread(data->Language, sz, 1, fp);
			}
            
            // booleans
            fread(&data->EnableService, sizeof(bool), 1, fp);
            fread(&data->EnableWebServer, sizeof(bool), 1, fp);
            fread(&data->EnableWebBlock, sizeof(bool), 1, fp);
        }

        fclose(fp);
        return data;
    }
    delete data;
    return nullptr;
}

inline bool SaveSettings(char* filename, pAppData data)
{
    FILE *fp;
    size_t sz = 0;
    if (data != nullptr)
    {
        if ((fp = fopen(filename, "wb")) != nullptr)
        {
            // pass
            sz = strlen(data->Password) +1;
            fwrite(&sz, sizeof(size_t) , 1, fp);
            fwrite(data->Password, sz, 1, fp);

            // region
            sz = strlen(data->RegionTime) +1;
            fwrite(&sz, sizeof(size_t), 1, fp);
            fwrite(data->RegionTime, sz, 1, fp);

            // language
            sz = strlen(data->Language) +1;
            fwrite(&sz, sizeof(size_t), 1, fp);
            fwrite(data->Language, sz, 1, fp);

            // booleans
            fwrite(&data->EnableService, sizeof(bool), 1, fp);
            fwrite(&data->EnableWebServer, sizeof(bool), 1, fp);
            fwrite(&data->EnableWebBlock, sizeof(bool), 1, fp);

            fclose(fp);
            return true;
        }
    }
    return false;
}


#endif //_UTILS_H_
