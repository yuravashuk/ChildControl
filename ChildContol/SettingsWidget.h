#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QMessageBox>

#include "../Service/Includes/Common.h"
#include "../Service/Includes/DataDumper.h"
#include "../Service/Includes/DataTypes.h"
#include "../Service/Includes/Utils.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

    void ReloadSettings();
    void showEvent( QShowEvent * event );

private slots:
    void on_chkChangePass_clicked();

    void on_btSave_clicked();

private:
    pAppData _appSettings;
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
