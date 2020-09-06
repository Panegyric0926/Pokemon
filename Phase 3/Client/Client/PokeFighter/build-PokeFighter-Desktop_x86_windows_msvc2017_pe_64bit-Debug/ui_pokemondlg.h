/********************************************************************************
** Form generated from reading UI file 'pokemondlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POKEMONDLG_H
#define UI_POKEMONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_PokemonDlg
{
public:

    void setupUi(QDialog *PokemonDlg)
    {
        if (PokemonDlg->objectName().isEmpty())
            PokemonDlg->setObjectName(QString::fromUtf8("PokemonDlg"));
        PokemonDlg->resize(400, 600);

        retranslateUi(PokemonDlg);

        QMetaObject::connectSlotsByName(PokemonDlg);
    } // setupUi

    void retranslateUi(QDialog *PokemonDlg)
    {
        PokemonDlg->setWindowTitle(QApplication::translate("PokemonDlg", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PokemonDlg: public Ui_PokemonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POKEMONDLG_H
