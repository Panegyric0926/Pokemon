/********************************************************************************
** Form generated from reading UI file 'logondlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGONDLG_H
#define UI_LOGONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_LogonDlg
{
public:

    void setupUi(QDialog *LogonDlg)
    {
        if (LogonDlg->objectName().isEmpty())
            LogonDlg->setObjectName(QString::fromUtf8("LogonDlg"));
        LogonDlg->resize(400, 300);

        retranslateUi(LogonDlg);

        QMetaObject::connectSlotsByName(LogonDlg);
    } // setupUi

    void retranslateUi(QDialog *LogonDlg)
    {
        LogonDlg->setWindowTitle(QApplication::translate("LogonDlg", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogonDlg: public Ui_LogonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGONDLG_H
