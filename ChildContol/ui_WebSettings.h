/********************************************************************************
** Form generated from reading UI file 'WebSettings.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBSETTINGS_H
#define UI_WEBSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebSettings
{
public:
    QPushButton *pushButton_7;
    QLabel *label;
    QLabel *label_2;
    QListWidget *lstWeb;
    QPushButton *pushButton_8;
    QPushButton *pushButton_6;
    QWidget *editWidget;
    QPushButton *btUnselectAll;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_8;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_10;
    QPushButton *btSave;
    QPushButton *btBack;
    QPushButton *btSelectAll;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_12;
    QPushButton *btSaveAll;

    void setupUi(QWidget *WebSettings)
    {
        if (WebSettings->objectName().isEmpty())
            WebSettings->setObjectName(QStringLiteral("WebSettings"));
        WebSettings->resize(701, 536);
        pushButton_7 = new QPushButton(WebSettings);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(170, 50, 151, 21));
        label = new QLabel(WebSettings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 131, 31));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(WebSettings);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 641, 16));
        lstWeb = new QListWidget(WebSettings);
        lstWeb->setObjectName(QStringLiteral("lstWeb"));
        lstWeb->setGeometry(QRect(10, 80, 681, 451));
        pushButton_8 = new QPushButton(WebSettings);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(330, 50, 191, 21));
        pushButton_6 = new QPushButton(WebSettings);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 50, 151, 21));
        editWidget = new QWidget(WebSettings);
        editWidget->setObjectName(QStringLiteral("editWidget"));
        editWidget->setGeometry(QRect(10, 80, 681, 451));
        btUnselectAll = new QPushButton(editWidget);
        btUnselectAll->setObjectName(QStringLiteral("btUnselectAll"));
        btUnselectAll->setGeometry(QRect(110, 260, 71, 21));
        label_3 = new QLabel(editWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setEnabled(true);
        label_3->setGeometry(QRect(20, 50, 641, 21));
        label_4 = new QLabel(editWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(90, 130, 21, 16));
        label_4->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        label_8 = new QLabel(editWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(90, 170, 21, 16));
        label_8->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        label_5 = new QLabel(editWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(90, 110, 21, 16));
        label_5->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        label_6 = new QLabel(editWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(true);
        label_6->setGeometry(QRect(110, 90, 641, 21));
        label_10 = new QLabel(editWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(90, 230, 21, 16));
        label_10->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        btSave = new QPushButton(editWidget);
        btSave->setObjectName(QStringLiteral("btSave"));
        btSave->setGeometry(QRect(410, 260, 80, 21));
        btBack = new QPushButton(editWidget);
        btBack->setObjectName(QStringLiteral("btBack"));
        btBack->setGeometry(QRect(500, 260, 80, 21));
        btSelectAll = new QPushButton(editWidget);
        btSelectAll->setObjectName(QStringLiteral("btSelectAll"));
        btSelectAll->setGeometry(QRect(190, 260, 71, 21));
        label_7 = new QLabel(editWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 10, 311, 31));
        label_7->setStyleSheet(QStringLiteral("font: 75 12pt \"MS Shell Dlg 2\";"));
        label_9 = new QLabel(editWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(90, 190, 21, 16));
        label_9->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        label_11 = new QLabel(editWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(90, 150, 21, 16));
        label_11->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        label_12 = new QLabel(editWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(90, 210, 21, 16));
        label_12->setStyleSheet(QStringLiteral("font: 10pt \"MS Shell Dlg 2\";"));
        btSaveAll = new QPushButton(WebSettings);
        btSaveAll->setObjectName(QStringLiteral("btSaveAll"));
        btSaveAll->setGeometry(QRect(530, 50, 161, 21));

        retranslateUi(WebSettings);

        QMetaObject::connectSlotsByName(WebSettings);
    } // setupUi

    void retranslateUi(QWidget *WebSettings)
    {
        WebSettings->setWindowTitle(QApplication::translate("WebSettings", "Form", 0));
        pushButton_7->setText(QApplication::translate("WebSettings", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270 \320\267 \321\201\320\277\320\270\321\201\320\272\321\203", 0));
        label->setText(QApplication::translate("WebSettings", "\320\222\320\265\320\261-\321\201\320\260\320\271\321\202\320\270", 0));
        label_2->setText(QApplication::translate("WebSettings", "\320\222 \320\264\320\260\320\275\320\276\320\274\321\203 \321\201\320\277\320\270\321\201\320\272\321\203 \320\267\320\275\320\260\321\205\320\276\320\264\321\217\321\202\321\214\321\201\321\217 \320\260\320\264\321\200\320\265\321\201\320\270 \320\262\320\265\320\261-\321\201\320\260\320\271\321\202\321\226\320\262, \321\217\320\272\321\226 \320\276\320\261\320\274\320\265\320\266\320\265\320\275\321\226 \320\262 \321\207\320\260\321\201\321\226 \320\262\320\270\320\272\320\276\320\275\320\260\320\275\320\275\321\217.", 0));
        pushButton_8->setText(QApplication::translate("WebSettings", "\320\240\320\265\320\264\320\260\320\263\321\203\320\262\320\260\321\202\320\270 \320\263\321\200\320\260\321\204\321\226\320\272 \320\262\320\270\320\272\320\276\320\275\320\260\320\275\320\275\321\217", 0));
        pushButton_6->setText(QApplication::translate("WebSettings", "\320\224\320\276\320\264\320\260\321\202\320\270 \320\275\320\276\320\262\320\265 \320\277\320\276\321\201\320\270\320\273\320\260\320\275\320\275\321\217", 0));
        btUnselectAll->setText(QApplication::translate("WebSettings", "\320\227\320\275\321\217\321\202\320\270 \320\262\321\201\321\226", 0));
        label_3->setText(QApplication::translate("WebSettings", "\320\237\320\276\320\267\320\275\320\260\321\207\321\202\320\265 \321\207\320\260\321\201\320\276\320\262\321\226 \320\274\320\265\320\266\321\226 \320\262 \321\217\320\272\320\270\321\205 \321\201\320\260\320\271\321\202 \320\261\321\203\320\264\320\265 \320\264\320\276\321\201\321\202\321\203\320\277\320\275\320\270\320\271 \320\264\320\273\321\217 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\321\226\320\262.", 0));
        label_4->setText(QApplication::translate("WebSettings", "\320\222\321\202", 0));
        label_8->setText(QApplication::translate("WebSettings", "\320\247\321\202", 0));
        label_5->setText(QApplication::translate("WebSettings", "\320\237\320\275", 0));
        label_6->setText(QApplication::translate("WebSettings", " 0    1     2    3     4     5    6     7     8    9    10   11  12   13   14   15   16  17   18   19   20  21   22   23", 0));
        label_10->setText(QApplication::translate("WebSettings", "\320\235\320\264", 0));
        btSave->setText(QApplication::translate("WebSettings", "\320\227\320\261\320\265\321\200\320\265\320\263\321\202\320\270", 0));
        btBack->setText(QApplication::translate("WebSettings", "\320\235\320\260\320\267\320\260\320\264", 0));
        btSelectAll->setText(QApplication::translate("WebSettings", "\320\236\320\261\321\200\320\260\321\202\320\270 \320\262\321\201\321\226", 0));
        label_7->setText(QApplication::translate("WebSettings", "\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217 \320\263\321\200\320\260\321\204\321\226\320\272\321\203 \321\200\320\276\320\261\320\276\321\202\320\270 \320\262\320\265\320\261-\321\201\320\260\320\271\321\202\321\226\320\262", 0));
        label_9->setText(QApplication::translate("WebSettings", "\320\237\321\202", 0));
        label_11->setText(QApplication::translate("WebSettings", "\320\241\320\264", 0));
        label_12->setText(QApplication::translate("WebSettings", "\320\241\320\261", 0));
        btSaveAll->setText(QApplication::translate("WebSettings", "\320\227\320\261\320\265\321\200\320\265\320\263\321\202\320\270 \320\267\320\274\321\226\320\275\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class WebSettings: public Ui_WebSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBSETTINGS_H
