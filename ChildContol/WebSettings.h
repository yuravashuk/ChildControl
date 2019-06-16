#ifndef WEBSETTINGS_H
#define WEBSETTINGS_H

#include <QWidget>
#include <QCheckBox>
#include <QMessageBox>
#include <QInputDialog>

#include "../Service/Includes/Common.h"
#include "../Service/Includes/DataDumper.h"
#include "../Service/Includes/DataTypes.h"
#include "../Service/Includes/Utils.h"

namespace Ui {
    class WebSettings;
}

class WebSettings : public QWidget
{
    Q_OBJECT

public:
    explicit WebSettings(QWidget *parent = 0);
    ~WebSettings();

    void InitBoxes();
    void AllocateFileNames();
    void DeallocateFileNames();
    void LoadDumps();

private slots:

    void on_btUnselectAll_clicked();

    void on_btSelectAll_clicked();

    void on_btBack_clicked();

    void on_btSave_clicked();

    void on_lstWeb_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

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

    Ui::WebSettings *ui;
};

#endif // WEBSETTINGS_H
