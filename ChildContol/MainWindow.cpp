#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFile>

#include "applocalizer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _appSettings(nullptr)
{
    ui->setupUi(this);

    // setup window
    this->setMinimumSize(QSize(_windowWidth,_windowHeight));
    this->setMaximumSize(QSize(_windowWidth,_windowHeight));
    this->setWindowTitle("ChildControl");
    this->setWindowFlags(Qt::FramelessWindowHint);

    // setup frames
    ui->frmMenu->setStyleSheet("QFrame{background-color:rgb(46,46,46);}");
    ui->frmMenu->setGeometry(QRect(0, 0, ui->frmMenu->width(),this->height()));

    // set login frame to screen
    ui->frmLoginFrame->setGeometry(QRect(0,0,_windowWidth,_windowHeight));
    ui->frmLoginFrame->raise();

    ui->txtPassword->setEchoMode(QLineEdit::Password);
    ui->txtPassword->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText| Qt::ImhNoAutoUppercase);

    ui->AppWidget->setGeometry(QRect(ui->frmMenu->width(), 0, this->width() - ui->frmMenu->width(), this->height()));
    ui->WebWidget->setGeometry(ui->AppWidget->geometry());
    ui->StWidget->setGeometry(ui->AppWidget->geometry());

    _prevFrame = ui->AppWidget;
    ui->WebWidget->setVisible(false);
    ui->StWidget->setVisible(false);
    ui->AppWidget->setVisible(true);
    ui->frmLoginFrame->raise();

    ReloadSettings();
    if (_appSettings == nullptr)
    {
        AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_BOTOM_TOP);
        ShowWidget(ui->StWidget);
        return;
    }

    _Locked = false;

    // change language
    AppLocalizer::GetInstance().ReloadLang();
    char* g = (char*)malloc(sizeof(char)*5);
    strcpy(g,"\n\n\n\n");
    ui->btApps->setText( strcpy(g, AppLocalizer::GetInstance().langArray[11].toStdString().c_str())  );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReloadSettings()
{
    // load settigns
    char* fpath = (char*)malloc(sizeof(char)* 300);
    strcpy(fpath, GetSystemRoot());
    strcat(fpath, "\\data\\appst.dat");

    if (_appSettings != nullptr)
    {
        if (_appSettings->_password) free(_appSettings->_password);
        if (_appSettings->_regionTime) free(_appSettings->_regionTime);
        delete _appSettings;
    }

    _appSettings = LoadSettings( fpath );

    free(fpath);
}

void MainWindow::AnimateFrameSwap(QWidget *frame, const int speed, AnimStyle style)
{
    switch (style)
    {
        case AnimStyle::AS_TOP_BOTTOM:
            _animFrame1 = new QPropertyAnimation(frame, "pos");
            _animFrame1->setEasingCurve(QEasingCurve::InOutQuart);
            _animFrame1->setDuration(speed);
            _animFrame1->setStartValue(frame->pos());
            _animFrame1->setEndValue(QPoint(0, 0));
            _animFrame1->start();
            return;
            break;
        case AnimStyle::AS_BOTOM_TOP:
            _animFrame1 = new QPropertyAnimation(frame, "pos");
            _animFrame1->setEasingCurve(QEasingCurve::InOutQuart);
            _animFrame1->setDuration(speed);
            _animFrame1->setStartValue(QPoint(0,0));
            _animFrame1->setEndValue(QPoint(0, -_windowHeight));
            _animFrame1->start();
            return;
            break;
        case AnimStyle::AS_RIGHT_LEFT:
            _prevFrame->setVisible(true);
            _animFrame1 = new QPropertyAnimation(frame, "pos");
            _animFrame1->setEasingCurve(QEasingCurve::InOutQuart);
            _animFrame1->setDuration(speed);
            _animFrame1->setStartValue(frame->pos());
            _animFrame1->setEndValue(QPoint(ui->frmMenu->width(), 0));

            _animFrame2 = new QPropertyAnimation(_prevFrame, "pos");
            _animFrame2->setEasingCurve(QEasingCurve::InOutQuart);
            _animFrame2->setDuration(speed/2);
            _animFrame2->setStartValue(_prevFrame->pos());
            _animFrame2->setEndValue(QPoint(this->width(), 0));

            _animFrame1->start();
            _animFrame2->start();
            break;
    }
}

void MainWindow::ShowWidget(QWidget *widget)
{
    if (_prevFrame == widget) return;
    ui->AppWidget->setVisible(false);
    ui->WebWidget->setVisible(false);
    ui->StWidget->setVisible(false);

    widget->setGeometry(QRect(this->width(), 0, widget->width(), widget->height()));
    widget->setVisible(true);
    widget->raise();

    AnimateFrameSwap(widget, _animSpeed, AnimStyle::AS_RIGHT_LEFT);

    _prevFrame = widget;
}

void MainWindow::on_btCancel_clicked()
{
    this->close();
}

void MainWindow::on_btLogin_clicked()
{
    if (_appSettings == nullptr)
        AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_BOTOM_TOP);

    if (!strcmp(ui->txtPassword->text().toStdString().c_str(), _appSettings->_password))
        AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_BOTOM_TOP);
}

void MainWindow::on_btLock_clicked()
{
    ReloadSettings();
    ui->frmLoginFrame->raise();
    AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_TOP_BOTTOM);
    ui->txtPassword->setText("");
}

void MainWindow::on_btExit_clicked()
{
    this->close();
}

void MainWindow::on_btWeb_clicked()
{
    ShowWidget(ui->WebWidget);
}

void MainWindow::on_btApps_clicked()
{
    ShowWidget(ui->AppWidget);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    _OldPoint = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint delta = event->globalPos() - _OldPoint;
    if (_Locked)
       move(x()+delta.x(), y());
    else
       move(x()+delta.x(), y()+delta.y());
    _OldPoint = event->globalPos();
}

void MainWindow::on_btSettings_clicked()
{
    ShowWidget(ui->StWidget);
}

void MainWindow::on_txtPassword_returnPressed()
{
    if (_appSettings == nullptr)
        AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_BOTOM_TOP);

    if (!strcmp(ui->txtPassword->text().toStdString().c_str(), _appSettings->_password))
        AnimateFrameSwap(ui->frmLoginFrame, _animSpeed, AnimStyle::AS_BOTOM_TOP);
}
