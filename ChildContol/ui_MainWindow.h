/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <AppSettings.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <SettingsWidget.h>
#include <WebSettings.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frmLoginFrame;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *txtPassword;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *btLogin;
    QPushButton *btCancel;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QFrame *frmMenu;
    QPushButton *btApps;
    QPushButton *btWeb;
    QPushButton *btSettings;
    QPushButton *btExit;
    QPushButton *btLock;
    AppSettings *AppWidget;
    WebSettings *WebWidget;
    SettingsWidget *StWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(850, 981);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frmLoginFrame = new QFrame(centralWidget);
        frmLoginFrame->setObjectName(QStringLiteral("frmLoginFrame"));
        frmLoginFrame->setGeometry(QRect(0, 580, 851, 401));
        frmLoginFrame->setFrameShape(QFrame::StyledPanel);
        frmLoginFrame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frmLoginFrame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 146, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(270, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(frmLoginFrame);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);

        verticalLayout->addWidget(label);

        txtPassword = new QLineEdit(frmLoginFrame);
        txtPassword->setObjectName(QStringLiteral("txtPassword"));

        verticalLayout->addWidget(txtPassword);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(270, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(270, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btLogin = new QPushButton(frmLoginFrame);
        btLogin->setObjectName(QStringLiteral("btLogin"));

        horizontalLayout->addWidget(btLogin);

        btCancel = new QPushButton(frmLoginFrame);
        btCancel->setObjectName(QStringLiteral("btCancel"));

        horizontalLayout->addWidget(btCancel);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(270, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 145, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        frmMenu = new QFrame(centralWidget);
        frmMenu->setObjectName(QStringLiteral("frmMenu"));
        frmMenu->setGeometry(QRect(0, 0, 151, 581));
        btApps = new QPushButton(frmMenu);
        btApps->setObjectName(QStringLiteral("btApps"));
        btApps->setGeometry(QRect(0, 10, 151, 101));
        btApps->setStyleSheet(QLatin1String("background-color: rgb(46,46,46);\n"
"border: 0px solid gray;\n"
"border-radius: 4px;\n"
"background: url(:/Img/Images/Apps.jpg) top center no-repeat;\n"
"padding-top: 32px;"));
        btApps->setCheckable(true);
        btWeb = new QPushButton(frmMenu);
        btWeb->setObjectName(QStringLiteral("btWeb"));
        btWeb->setGeometry(QRect(0, 120, 151, 101));
        btWeb->setStyleSheet(QLatin1String("background-color: rgb(46,46,46);\n"
"border: 0px solid gray;\n"
"border-radius: 4px;\n"
"background: url(:/Img/Images/Web.jpg) top center no-repeat;\n"
"padding-top: 20px;"));
        btWeb->setCheckable(true);
        btSettings = new QPushButton(frmMenu);
        btSettings->setObjectName(QStringLiteral("btSettings"));
        btSettings->setGeometry(QRect(0, 230, 151, 101));
        btSettings->setStyleSheet(QLatin1String("background-color: rgb(46,46,46);\n"
"border: 0px solid gray;\n"
"border-radius: 4px;\n"
"background: url(:/Img/Images/Settings.jpg) top center no-repeat;\n"
"padding-top: 24px;"));
        btSettings->setCheckable(true);
        btExit = new QPushButton(frmMenu);
        btExit->setObjectName(QStringLiteral("btExit"));
        btExit->setGeometry(QRect(0, 320, 151, 101));
        btExit->setStyleSheet(QLatin1String("background-color: rgb(46,46,46);\n"
"border: 0px solid gray;\n"
"border-radius: 4px;\n"
"background: url(:/Img/Images/Exit.jpg) top center no-repeat;\n"
"padding-top: 32px;"));
        btExit->setCheckable(true);
        btLock = new QPushButton(frmMenu);
        btLock->setObjectName(QStringLiteral("btLock"));
        btLock->setGeometry(QRect(0, 430, 151, 101));
        btLock->setStyleSheet(QLatin1String("background-color: rgb(46,46,46);\n"
"border: 0px solid gray;\n"
"border-radius: 4px;\n"
"background: url(:/Img/Images/Lock.jpg) top center no-repeat;\n"
"padding-top: 32px;"));
        AppWidget = new AppSettings(centralWidget);
        AppWidget->setObjectName(QStringLiteral("AppWidget"));
        AppWidget->setGeometry(QRect(149, -1, 201, 211));
        WebWidget = new WebSettings(centralWidget);
        WebWidget->setObjectName(QStringLiteral("WebWidget"));
        WebWidget->setGeometry(QRect(360, 0, 201, 211));
        StWidget = new SettingsWidget(centralWidget);
        StWidget->setObjectName(QStringLiteral("StWidget"));
        StWidget->setGeometry(QRect(580, 30, 120, 80));
        MainWindow->setCentralWidget(centralWidget);
        WebWidget->raise();
        frmMenu->raise();
        frmLoginFrame->raise();
        AppWidget->raise();
        StWidget->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \320\277\320\260\321\200\320\276\320\273\321\214 \320\264\320\273\321\217 \320\260\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\321\226\321\227", 0));
        txtPassword->setText(QString());
        btLogin->setText(QApplication::translate("MainWindow", "\320\222\320\262\321\226\320\271\321\202\320\270", 0));
        btCancel->setText(QApplication::translate("MainWindow", "\320\222\320\270\321\205\321\226\320\264", 0));
        btApps->setText(QApplication::translate("MainWindow", "\n"
"\n"
"\n"
"\n"
"\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\270", 0));
        btWeb->setText(QApplication::translate("MainWindow", "\n"
"\n"
"\n"
"\n"
"\n"
"\320\222\320\265\320\261 \321\201\320\260\320\271\321\202\320\270", 0));
        btSettings->setText(QApplication::translate("MainWindow", "\n"
"\n"
"\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", 0));
        btExit->setText(QApplication::translate("MainWindow", "\n"
"\n"
"\n"
"\n"
"\320\222\320\270\321\205\321\226\320\264", 0));
        btLock->setText(QApplication::translate("MainWindow", "\n"
"\n"
"\n"
"\n"
"\320\227\320\260\320\261\320\273\320\276\320\272\321\203\320\262\320\260\321\202\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
