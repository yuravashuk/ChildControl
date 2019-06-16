/********************************************************************************
** Form generated from reading UI file 'SettingsWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWIDGET_H
#define UI_SETTINGSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsWidget
{
public:
    QPushButton *btSave;
    QCheckBox *chkServer;
    QLabel *label;
    QLineEdit *txtPass2;
    QComboBox *cboLanguage;
    QComboBox *cboTimeLocation;
    QLineEdit *txtPass1;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *lblPass1;
    QCheckBox *chkWebBlock;
    QCheckBox *chkSoftBlock;
    QCheckBox *chkChangePass;
    QLabel *lblPass2;

    void setupUi(QWidget *SettingsWidget)
    {
        if (SettingsWidget->objectName().isEmpty())
            SettingsWidget->setObjectName(QStringLiteral("SettingsWidget"));
        SettingsWidget->resize(693, 490);
        btSave = new QPushButton(SettingsWidget);
        btSave->setObjectName(QStringLiteral("btSave"));
        btSave->setGeometry(QRect(10, 370, 151, 21));
        chkServer = new QCheckBox(SettingsWidget);
        chkServer->setObjectName(QStringLiteral("chkServer"));
        chkServer->setGeometry(QRect(10, 170, 531, 19));
        chkServer->setChecked(true);
        label = new QLabel(SettingsWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 131, 31));
        label->setStyleSheet(QStringLiteral("font: 75 12pt \"MS Shell Dlg 2\";"));
        txtPass2 = new QLineEdit(SettingsWidget);
        txtPass2->setObjectName(QStringLiteral("txtPass2"));
        txtPass2->setEnabled(false);
        txtPass2->setGeometry(QRect(30, 130, 321, 21));
        cboLanguage = new QComboBox(SettingsWidget);
        cboLanguage->setObjectName(QStringLiteral("cboLanguage"));
        cboLanguage->setGeometry(QRect(10, 290, 341, 22));
        cboTimeLocation = new QComboBox(SettingsWidget);
        cboTimeLocation->setObjectName(QStringLiteral("cboTimeLocation"));
        cboTimeLocation->setGeometry(QRect(10, 340, 341, 22));
        txtPass1 = new QLineEdit(SettingsWidget);
        txtPass1->setObjectName(QStringLiteral("txtPass1"));
        txtPass1->setEnabled(false);
        txtPass1->setGeometry(QRect(30, 80, 321, 21));
        label_4 = new QLabel(SettingsWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(true);
        label_4->setGeometry(QRect(10, 270, 321, 16));
        label_5 = new QLabel(SettingsWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setEnabled(true);
        label_5->setGeometry(QRect(10, 320, 411, 16));
        lblPass1 = new QLabel(SettingsWidget);
        lblPass1->setObjectName(QStringLiteral("lblPass1"));
        lblPass1->setEnabled(false);
        lblPass1->setGeometry(QRect(30, 60, 321, 16));
        chkWebBlock = new QCheckBox(SettingsWidget);
        chkWebBlock->setObjectName(QStringLiteral("chkWebBlock"));
        chkWebBlock->setGeometry(QRect(10, 230, 531, 19));
        chkWebBlock->setChecked(true);
        chkSoftBlock = new QCheckBox(SettingsWidget);
        chkSoftBlock->setObjectName(QStringLiteral("chkSoftBlock"));
        chkSoftBlock->setGeometry(QRect(10, 200, 531, 19));
        chkSoftBlock->setChecked(true);
        chkChangePass = new QCheckBox(SettingsWidget);
        chkChangePass->setObjectName(QStringLiteral("chkChangePass"));
        chkChangePass->setGeometry(QRect(10, 40, 531, 19));
        lblPass2 = new QLabel(SettingsWidget);
        lblPass2->setObjectName(QStringLiteral("lblPass2"));
        lblPass2->setEnabled(false);
        lblPass2->setGeometry(QRect(30, 110, 511, 16));

        retranslateUi(SettingsWidget);

        QMetaObject::connectSlotsByName(SettingsWidget);
    } // setupUi

    void retranslateUi(QWidget *SettingsWidget)
    {
        SettingsWidget->setWindowTitle(QApplication::translate("SettingsWidget", "Form", 0));
        btSave->setText(QApplication::translate("SettingsWidget", "\320\227\320\261\320\265\321\200\320\265\320\263\321\202\320\270 \320\275\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", 0));
        chkServer->setText(QApplication::translate("SettingsWidget", "\320\222\320\262\321\226\320\274\320\272\320\275\321\203\321\202\320\270 \321\202\321\200\320\260\320\275\321\201\320\273\321\217\321\206\321\226\321\216 \320\262\320\265\320\261 \321\201\321\202\320\276\321\200\321\226\320\275\320\272\320\270 \320\267 \320\264\320\276\320\264\320\260\321\202\320\272\320\276\320\262\320\276\321\216 \321\226\320\275\321\204\320\276\321\200\320\274\320\260\321\206\321\226\321\224\321\216 \320\277\321\200\320\270 \320\277\320\265\321\200\320\265\321\205\320\276\320\264\321\226 \320\275\320\260 \320\267\320\260\320\261\320\273\320\276\320\272\320\276\320\262\320\260\320\275\321\226 \321\201\320\260\320\271\321\202\320\270?", 0));
        label->setText(QApplication::translate("SettingsWidget", "\320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217", 0));
        cboLanguage->clear();
        cboLanguage->insertItems(0, QStringList()
         << QApplication::translate("SettingsWidget", "\320\243\320\272\321\200\320\260\321\227\320\275\321\201\321\214\320\272\320\260", 0)
         << QApplication::translate("SettingsWidget", "English", 0)
         << QApplication::translate("SettingsWidget", "Deutsch", 0)
         << QApplication::translate("SettingsWidget", "\320\240\321\203\321\201\321\201\320\272\320\270\320\271", 0)
        );
        cboTimeLocation->clear();
        cboTimeLocation->insertItems(0, QStringList()
         << QApplication::translate("SettingsWidget", "Ukraine", 0)
         << QApplication::translate("SettingsWidget", "United_States", 0)
         << QApplication::translate("SettingsWidget", "Germany", 0)
         << QApplication::translate("SettingsWidget", "Mosow", 0)
        );
        label_4->setText(QApplication::translate("SettingsWidget", "\320\234\320\276\320\262\320\260 \320\263\321\200\320\260\321\204\321\226\321\207\320\275\320\276\320\263\320\276 \321\226\320\275\321\202\320\265\321\200\321\204\320\265\320\271\321\201\321\203:", 0));
        label_5->setText(QApplication::translate("SettingsWidget", "\320\234\321\226\321\201\321\206\320\265\320\267\320\275\320\260\321\205\320\276\320\264\320\266\320\265\320\275\320\275\321\217. \320\222\320\270\320\272\320\276\321\200\320\270\321\201\321\202\320\276\320\262\321\203\321\224\321\202\321\214\321\201\321\217 \320\264\320\273\321\217 \320\264\320\276\321\201\321\202\321\203\320\277\321\203 \320\264\320\276 \321\207\320\260\321\201\321\203 \321\207\320\265\321\200\320\265\320\267 \321\226\320\275\321\202\320\265\321\200\320\275\320\265\321\202.", 0));
        lblPass1->setText(QApplication::translate("SettingsWidget", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \321\201\321\202\320\260\321\200\320\270\320\271 \320\277\320\260\321\200\320\276\320\273\321\214:", 0));
        chkWebBlock->setText(QApplication::translate("SettingsWidget", "\320\222\320\262\321\226\320\274\320\272\320\275\321\203\321\202\320\270 \320\261\320\273\320\276\320\272\321\203\320\262\320\260\320\275\320\275\321\217 \320\262\320\265\320\261-\321\201\320\260\320\271\321\202\321\226\320\262?", 0));
        chkSoftBlock->setText(QApplication::translate("SettingsWidget", "\320\222\320\262\321\226\320\274\320\272\320\275\321\203\321\202\320\270 \320\261\320\273\320\276\320\272\321\203\320\262\320\260\320\275\320\275\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\275\320\276\320\263\320\276 \320\267\320\260\320\261\320\265\320\267\320\277\320\265\321\207\320\265\320\275\320\275\321\217?", 0));
        chkChangePass->setText(QApplication::translate("SettingsWidget", "\320\227\320\274\321\226\320\275\320\270\321\202\320\270 \320\277\320\260\321\200\320\276\320\273\321\214?", 0));
        lblPass2->setText(QApplication::translate("SettingsWidget", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \320\275\320\276\320\262\320\270\320\271 \320\277\320\260\321\200\320\276\320\273\321\214:", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsWidget: public Ui_SettingsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWIDGET_H
