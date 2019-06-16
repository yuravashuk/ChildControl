#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QWidget>
#include <QFileDialog>
#include <QCheckBox>

#include <QMessageBox>
#include <QFileInfo>

#include "../Service/Includes/Common.h"
#include "../Service/Includes/DataDumper.h"
#include "../Service/Includes/DataTypes.h"
#include "../Service/Includes/Utils.h"

namespace Ui {
    class AppSettings;
}

class AppSettings : public QWidget
{
    Q_OBJECT

public:
    explicit AppSettings(QWidget *parent = 0);
    ~AppSettings();

    void InitBoxes();
    void AllocateFileNames();
    void DeallocateFileNames();
    void LoadDumps();

    bool InitSocket();
    void DestroySocket();
    bool SendMessageToService();

private slots:
    void on_btEdit_clicked();

    void on_btAdd_clicked();

    void on_btBack_clicked();

    void on_btSave_clicked();

    void on_lstProc_clicked(const QModelIndex &index);

    void on_btRemove_clicked();

    void on_btSelectAll_clicked();

    void on_btUnselectAll_clicked();

    void on_btSaveAll_clicked();

private:
    QCheckBox* _day1boxes[24];
    QCheckBox* _day2boxes[24];
    QCheckBox* _day3boxes[24];
    QCheckBox* _day4boxes[24];
    QCheckBox* _day5boxes[24];
    QCheckBox* _day6boxes[24];
    QCheckBox* _day7boxes[24];

    QString _selectedApp;

    std::vector<std::string> _names;
    std::vector<int> _hFlgs[7];

    pProcessPool _procPool;
    DataDumper<std::string, 0> _procNamesDmp;
    DataDumper<int, 0> _procHflgDmp;

    char* fNamesPath[7];
    char* fHflgPath[7];

#if PLATFORM == PLATFORM_WINDOWS
    SOCKET _socket;
#else
    int    _socket;
#endif

    Ui::AppSettings *ui;
};

#endif // APPSETTINGS_H
