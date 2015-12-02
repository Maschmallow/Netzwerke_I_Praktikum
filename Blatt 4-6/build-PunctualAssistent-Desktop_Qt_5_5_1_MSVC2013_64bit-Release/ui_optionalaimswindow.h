/********************************************************************************
** Form generated from reading UI file 'optionalaimswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONALAIMSWINDOW_H
#define UI_OPTIONALAIMSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_OptionalAimsWindow
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *cityLabel;
    QLabel *countryLabel;
    QComboBox *CountrySelect;
    QTextEdit *StreetTextField;
    QLabel *StreetLabel;
    QTextEdit *HouseNr;
    QTextEdit *PlzTextField;
    QTextEdit *CityTextField;

    void setupUi(QDialog *OptionalAimsWindow)
    {
        if (OptionalAimsWindow->objectName().isEmpty())
            OptionalAimsWindow->setObjectName(QStringLiteral("OptionalAimsWindow"));
        OptionalAimsWindow->resize(680, 300);
        buttonBox = new QDialogButtonBox(OptionalAimsWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        cityLabel = new QLabel(OptionalAimsWindow);
        cityLabel->setObjectName(QStringLiteral("cityLabel"));
        cityLabel->setGeometry(QRect(110, 117, 71, 16));
        countryLabel = new QLabel(OptionalAimsWindow);
        countryLabel->setObjectName(QStringLiteral("countryLabel"));
        countryLabel->setGeometry(QRect(140, 153, 41, 16));
        CountrySelect = new QComboBox(OptionalAimsWindow);
        CountrySelect->setObjectName(QStringLiteral("CountrySelect"));
        CountrySelect->setGeometry(QRect(190, 153, 104, 26));
        StreetTextField = new QTextEdit(OptionalAimsWindow);
        StreetTextField->setObjectName(QStringLiteral("StreetTextField"));
        StreetTextField->setGeometry(QRect(190, 70, 271, 31));
        StreetLabel = new QLabel(OptionalAimsWindow);
        StreetLabel->setObjectName(QStringLiteral("StreetLabel"));
        StreetLabel->setGeometry(QRect(46, 77, 141, 16));
        HouseNr = new QTextEdit(OptionalAimsWindow);
        HouseNr->setObjectName(QStringLiteral("HouseNr"));
        HouseNr->setGeometry(QRect(470, 70, 51, 31));
        PlzTextField = new QTextEdit(OptionalAimsWindow);
        PlzTextField->setObjectName(QStringLiteral("PlzTextField"));
        PlzTextField->setGeometry(QRect(190, 110, 101, 31));
        CityTextField = new QTextEdit(OptionalAimsWindow);
        CityTextField->setObjectName(QStringLiteral("CityTextField"));
        CityTextField->setGeometry(QRect(300, 110, 221, 31));

        retranslateUi(OptionalAimsWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), OptionalAimsWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), OptionalAimsWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(OptionalAimsWindow);
    } // setupUi

    void retranslateUi(QDialog *OptionalAimsWindow)
    {
        OptionalAimsWindow->setWindowTitle(QApplication::translate("OptionalAimsWindow", "Dialog", 0));
        cityLabel->setText(QApplication::translate("OptionalAimsWindow", "PLZ/Stadt:", 0));
        countryLabel->setText(QApplication::translate("OptionalAimsWindow", "Land:", 0));
        CountrySelect->clear();
        CountrySelect->insertItems(0, QStringList()
         << QApplication::translate("OptionalAimsWindow", "Deutschland", 0)
         << QApplication::translate("OptionalAimsWindow", "\303\226sterreich", 0)
         << QApplication::translate("OptionalAimsWindow", "Schweiz", 0)
         << QApplication::translate("OptionalAimsWindow", "Spanien", 0)
         << QApplication::translate("OptionalAimsWindow", "Niederlande", 0)
         << QApplication::translate("OptionalAimsWindow", "Polen", 0)
         << QApplication::translate("OptionalAimsWindow", "Tschechien", 0)
         << QApplication::translate("OptionalAimsWindow", "D\303\244nemark", 0)
        );
        StreetLabel->setText(QApplication::translate("OptionalAimsWindow", "Stra\303\237e/Hausnummer: ", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionalAimsWindow: public Ui_OptionalAimsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONALAIMSWINDOW_H
