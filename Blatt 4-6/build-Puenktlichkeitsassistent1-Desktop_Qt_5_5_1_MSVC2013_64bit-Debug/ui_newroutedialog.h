/********************************************************************************
** Form generated from reading UI file 'newroutedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWROUTEDIALOG_H
#define UI_NEWROUTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewRouteDialog
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QGridLayout *gridLayout;
    QLabel *countryLbl;
    QDialogButtonBox *applyNCloseBtnBox;
    QTextEdit *streetNrTxt;
    QTextEdit *streetTxt;
    QTextEdit *plzTxt;
    QComboBox *countryCmbBox;
    QSpacerItem *horizontalSpacer;
    QLabel *streetLbl;
    QLabel *plzCityLbl;
    QTextEdit *cityTxt;

    void setupUi(QDialog *NewRouteDialog)
    {
        if (NewRouteDialog->objectName().isEmpty())
            NewRouteDialog->setObjectName(QStringLiteral("NewRouteDialog"));
        NewRouteDialog->resize(557, 106);
        NewRouteDialog->setModal(true);
        verticalLayout = new QVBoxLayout(NewRouteDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton = new QPushButton(NewRouteDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        countryLbl = new QLabel(NewRouteDialog);
        countryLbl->setObjectName(QStringLiteral("countryLbl"));

        gridLayout->addWidget(countryLbl, 2, 0, 1, 1);

        applyNCloseBtnBox = new QDialogButtonBox(NewRouteDialog);
        applyNCloseBtnBox->setObjectName(QStringLiteral("applyNCloseBtnBox"));
        applyNCloseBtnBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        gridLayout->addWidget(applyNCloseBtnBox, 2, 2, 1, 1);

        streetNrTxt = new QTextEdit(NewRouteDialog);
        streetNrTxt->setObjectName(QStringLiteral("streetNrTxt"));

        gridLayout->addWidget(streetNrTxt, 0, 1, 1, 1);

        streetTxt = new QTextEdit(NewRouteDialog);
        streetTxt->setObjectName(QStringLiteral("streetTxt"));

        gridLayout->addWidget(streetTxt, 0, 2, 1, 1);

        plzTxt = new QTextEdit(NewRouteDialog);
        plzTxt->setObjectName(QStringLiteral("plzTxt"));

        gridLayout->addWidget(plzTxt, 1, 1, 1, 1);

        countryCmbBox = new QComboBox(NewRouteDialog);
        QIcon icon;
        icon.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/de.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/Italy.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/Poland.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/fr.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/Spain.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MyFiles/FlagIcons/resources/countries/Austria.png"), QSize(), QIcon::Normal, QIcon::Off);
        countryCmbBox->addItem(icon5, QString());
        countryCmbBox->setObjectName(QStringLiteral("countryCmbBox"));

        gridLayout->addWidget(countryCmbBox, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        streetLbl = new QLabel(NewRouteDialog);
        streetLbl->setObjectName(QStringLiteral("streetLbl"));

        gridLayout->addWidget(streetLbl, 0, 0, 1, 1);

        plzCityLbl = new QLabel(NewRouteDialog);
        plzCityLbl->setObjectName(QStringLiteral("plzCityLbl"));

        gridLayout->addWidget(plzCityLbl, 1, 0, 1, 1);

        cityTxt = new QTextEdit(NewRouteDialog);
        cityTxt->setObjectName(QStringLiteral("cityTxt"));

        gridLayout->addWidget(cityTxt, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(NewRouteDialog);

        QMetaObject::connectSlotsByName(NewRouteDialog);
    } // setupUi

    void retranslateUi(QDialog *NewRouteDialog)
    {
        NewRouteDialog->setWindowTitle(QApplication::translate("NewRouteDialog", "Neue Route", 0));
        pushButton->setText(QApplication::translate("NewRouteDialog", "PushButton", 0));
        countryLbl->setText(QApplication::translate("NewRouteDialog", "Land:", 0));
        countryCmbBox->setItemText(0, QApplication::translate("NewRouteDialog", "Deutschland", 0));
        countryCmbBox->setItemText(1, QApplication::translate("NewRouteDialog", "Italien", 0));
        countryCmbBox->setItemText(2, QApplication::translate("NewRouteDialog", "Polen", 0));
        countryCmbBox->setItemText(3, QApplication::translate("NewRouteDialog", "Frankreich", 0));
        countryCmbBox->setItemText(4, QApplication::translate("NewRouteDialog", "Spanien", 0));
        countryCmbBox->setItemText(5, QApplication::translate("NewRouteDialog", "\303\226sterreich", 0));

        streetLbl->setText(QApplication::translate("NewRouteDialog", "Stra\303\237e/Hausnummer:", 0));
        plzCityLbl->setText(QApplication::translate("NewRouteDialog", "PLZ/Stadt:", 0));
    } // retranslateUi

};

namespace Ui {
    class NewRouteDialog: public Ui_NewRouteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWROUTEDIALOG_H
