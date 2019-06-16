
#pragma once

#ifndef APPLOCALIZER
#define APPLOCALIZER

#include <QFile>
#include <QTextStream>

#include "../Service/Includes/Common.h"
#include "../Service/Includes/DataDumper.h"
#include "../Service/Includes/DataTypes.h"

class AppLocalizer
{
public:
    static AppLocalizer GetInstance()
    {
        static AppLocalizer _instance;
        return _instance;
    }

    void LoadCurLang()
    {
        // load settigns
        char* fpath = (char*)malloc(sizeof(char)* 300);
        strcpy(fpath, GetSystemRoot());
        strcat(fpath, "\\data\\appst.dat");

        mAppSettings = LoadSettings( fpath );
        free(fpath);

        if (mAppSettings == nullptr)
        {
            mAppSettings = new AppData;
            mAppSettings->_language = (char*)malloc(sizeof(char)*30);
            strcpy(mAppSettings->_language, "en");
        }
    }

    void ReloadLang()
    {
        QString il;

        LoadCurLang();
        if (strcmp(mAppSettings->_language, "English"))
        {
            il = "en";
        }
        if (strcmp(mAppSettings->_language, "Українська"))
        {
            il = "ua";
        }
        if (strcmp(mAppSettings->_language, "Русский"))
        {
            il = "ru";
        }
        // DE
        QFile file(QString(":/lang/lang/") + il + QString(".txt"));
        if (file.open(QFile::ReadOnly))
        {
            size_t i = 0;
            QTextStream line(&file);
            while (!line.atEnd())
            {
                if (i > 50) break;
                langArray[i] = file.readLine();
                i++;
            }
        }
    }

    QString langArray[51];
private:
    pAppData mAppSettings;
};

#endif // APPLOCALIZER

