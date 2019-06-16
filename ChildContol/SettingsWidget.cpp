#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget),
    _appSettings(nullptr)
{
    ui->setupUi(this);

    ui->txtPass1->setEchoMode(QLineEdit::Password);
    ui->txtPass1->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText| Qt::ImhNoAutoUppercase);

    ui->txtPass2->setEchoMode(QLineEdit::Password);
    ui->txtPass2->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText| Qt::ImhNoAutoUppercase);
}

void SettingsWidget::ReloadSettings()
{
    // load settigns
    char* fpath = (char*)malloc(sizeof(char)* 300);
    strcpy(fpath, GetSystemRoot());
    strcat(fpath, "\\data\\appst.dat");

    _appSettings = LoadSettings( fpath );
    free(fpath);

    if (_appSettings == nullptr)
    {
        _appSettings = new AppData;
        _appSettings->_language = (char*)malloc(sizeof(char)*30);
        _appSettings->_password = (char*)malloc(sizeof(char)*30);
        _appSettings->_regionTime = (char*)malloc(sizeof(char)*30);
        _appSettings->_enableService = true;
        _appSettings->_enableWebBlock = true;
        _appSettings->_enableWebServer = true;

        strcpy(_appSettings->_password, "q");
        ui->txtPass1->setText("q");

        ui->chkChangePass->setChecked(true);
        ui->lblPass1->setEnabled( true );
        ui->lblPass2->setEnabled( true );
        ui->txtPass1->setEnabled( true );
        ui->txtPass2->setEnabled( true );
        ui->chkChangePass->setText("Змінити пароль? (Ви авторизуєтесь перший раз, тому введіть в поле нового пароля свій пароль)");
    }

    // apply settings
    if (_appSettings != nullptr)
    {
        ui->chkSoftBlock->setChecked(_appSettings->_enableService);
        ui->chkServer->setChecked(_appSettings->_enableWebServer);
        ui->chkWebBlock->setChecked(_appSettings->_enableWebBlock);

        // time zone
        int index = ui->cboTimeLocation->findText(QString(_appSettings->_regionTime));
        if ( index != -1 ) ui->cboTimeLocation->setCurrentIndex(index);

        // language
        index = ui->cboLanguage->findText(QString(_appSettings->_language));
        if ( index != -1 ) ui->cboLanguage->setCurrentIndex(index);

        return;
    }

}

void SettingsWidget::showEvent(QShowEvent *event)
{
    ui->txtPass1->setText("");
    ui->txtPass2->setText("");
    ui->chkChangePass->setChecked(false);
    ui->lblPass1->setEnabled( false );
    ui->lblPass2->setEnabled( false );
    ui->txtPass1->setEnabled( false );
    ui->txtPass2->setEnabled( false );
    ReloadSettings();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::on_chkChangePass_clicked()
{
    ui->lblPass1->setEnabled( !ui->lblPass1->isEnabled() );
    ui->lblPass2->setEnabled( !ui->lblPass2->isEnabled() );
    ui->txtPass1->setEnabled( !ui->txtPass1->isEnabled() );
    ui->txtPass2->setEnabled( !ui->txtPass2->isEnabled() );
}

void SettingsWidget::on_btSave_clicked()
{
    QMessageBox msg;

    // save password
    if (ui->chkChangePass->isChecked())
    {
        if (!strcmp(_appSettings->_password, ui->txtPass1->text().toStdString().c_str()))
        {
            if (strlen(ui->txtPass1->text().toStdString().c_str()) > strlen(_appSettings->_password))
            {
                if (_appSettings->_password) free(_appSettings->_password);
                _appSettings->_password = (char*)malloc(strlen(ui->txtPass2->text().toStdString().c_str()));
            }
            strcpy(_appSettings->_password, ui->txtPass2->text().toStdString().c_str());
        }   
    }

    // save time zone
    size_t sz = strlen( ui->cboTimeLocation->currentText().toStdString().c_str() );
    if (strlen(_appSettings->_regionTime) < sz)
    {
        if (_appSettings->_regionTime) free(_appSettings->_regionTime);
        _appSettings->_regionTime = (char*)malloc(sz);
    }
    strcpy(_appSettings->_regionTime, ui->cboTimeLocation->currentText().toStdString().c_str());

    // save language
    sz = strlen( ui->cboLanguage->currentText().toStdString().c_str() );
    if (strlen(_appSettings->_language) < sz)
    {
        if (_appSettings->_language) free(_appSettings->_language);
        _appSettings->_language = (char*)malloc(sz);
    }
    strcpy(_appSettings->_language, ui->cboLanguage->currentText().toStdString().c_str());

    // save booleans
    _appSettings->_enableService = ui->chkSoftBlock->isChecked();
    _appSettings->_enableWebServer = ui->chkServer->isChecked();
    _appSettings->_enableWebBlock = ui->chkWebBlock->isChecked();

    // save data
    char* fpath = (char*)malloc(sizeof(char)* 300);
    strcpy(fpath, GetSystemRoot());
    strcat(fpath, "\\data\\appst.dat");
    SaveSettings(fpath, _appSettings);
    free(fpath);

    if (ui->cboLanguage->currentText() == "Українська")
        msg.setText("Налаштування успішно збережені!");
    else
        msg.setText("Налаштування успішно збережені!\n"
                    "Вибачте, на даний момент програма не підтримує вибрану вами мову.\n"
                    "Підтримка даної мови з'явиться в наступній версії програми.");
    msg.exec();
}
