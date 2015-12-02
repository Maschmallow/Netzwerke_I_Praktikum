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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NewRouteDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *streetNrEdit;
    QLineEdit *plzEdit;
    QLabel *label;
    QLineEdit *streetEdit;
    QLineEdit *cityEdit;
    QLabel *label_2;
    QLabel *streetLbl;
    QLabel *plzCityLbl;
    QLabel *countryLbl;
    QHBoxLayout *horizontalLayout;
    QComboBox *countryCmbBox;
    QDialogButtonBox *applyNCloseBtnBox;

    void setupUi(QDialog *NewRouteDialog)
    {
        if (NewRouteDialog->objectName().isEmpty())
            NewRouteDialog->setObjectName(QStringLiteral("NewRouteDialog"));
        NewRouteDialog->setWindowModality(Qt::NonModal);
        NewRouteDialog->resize(448, 149);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewRouteDialog->sizePolicy().hasHeightForWidth());
        NewRouteDialog->setSizePolicy(sizePolicy);
        NewRouteDialog->setMaximumSize(QSize(692, 439));
        NewRouteDialog->setModal(true);
        verticalLayout = new QVBoxLayout(NewRouteDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 0, 0);
        streetNrEdit = new QLineEdit(NewRouteDialog);
        streetNrEdit->setObjectName(QStringLiteral("streetNrEdit"));
        sizePolicy.setHeightForWidth(streetNrEdit->sizePolicy().hasHeightForWidth());
        streetNrEdit->setSizePolicy(sizePolicy);
        streetNrEdit->setMinimumSize(QSize(0, 20));
        streetNrEdit->setMaximumSize(QSize(30, 20));
        streetNrEdit->setStyleSheet(QStringLiteral(""));
        streetNrEdit->setInputMethodHints(Qt::ImhNone);

        gridLayout->addWidget(streetNrEdit, 2, 1, 1, 1);

        plzEdit = new QLineEdit(NewRouteDialog);
        plzEdit->setObjectName(QStringLiteral("plzEdit"));
        sizePolicy.setHeightForWidth(plzEdit->sizePolicy().hasHeightForWidth());
        plzEdit->setSizePolicy(sizePolicy);
        plzEdit->setMinimumSize(QSize(0, 20));
        plzEdit->setMaximumSize(QSize(60, 20));

        gridLayout->addWidget(plzEdit, 3, 1, 1, 1);

        label = new QLabel(NewRouteDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        streetEdit = new QLineEdit(NewRouteDialog);
        streetEdit->setObjectName(QStringLiteral("streetEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(streetEdit->sizePolicy().hasHeightForWidth());
        streetEdit->setSizePolicy(sizePolicy1);
        streetEdit->setMinimumSize(QSize(0, 0));
        streetEdit->setMaximumSize(QSize(16777215, 20));
        streetEdit->setSizeIncrement(QSize(30, 0));

        gridLayout->addWidget(streetEdit, 0, 1, 1, 1);

        cityEdit = new QLineEdit(NewRouteDialog);
        cityEdit->setObjectName(QStringLiteral("cityEdit"));
        sizePolicy.setHeightForWidth(cityEdit->sizePolicy().hasHeightForWidth());
        cityEdit->setSizePolicy(sizePolicy);
        cityEdit->setMinimumSize(QSize(200, 20));
        cityEdit->setMaximumSize(QSize(300, 20));

        gridLayout->addWidget(cityEdit, 4, 1, 1, 1);

        label_2 = new QLabel(NewRouteDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        streetLbl = new QLabel(NewRouteDialog);
        streetLbl->setObjectName(QStringLiteral("streetLbl"));

        gridLayout->addWidget(streetLbl, 0, 0, 1, 1);

        plzCityLbl = new QLabel(NewRouteDialog);
        plzCityLbl->setObjectName(QStringLiteral("plzCityLbl"));

        gridLayout->addWidget(plzCityLbl, 4, 0, 1, 1);

        countryLbl = new QLabel(NewRouteDialog);
        countryLbl->setObjectName(QStringLiteral("countryLbl"));

        gridLayout->addWidget(countryLbl, 8, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
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

        horizontalLayout->addWidget(countryCmbBox);

        applyNCloseBtnBox = new QDialogButtonBox(NewRouteDialog);
        applyNCloseBtnBox->setObjectName(QStringLiteral("applyNCloseBtnBox"));
        applyNCloseBtnBox->setStandardButtons(QDialogButtonBox::Apply|QDialogButtonBox::Close);

        horizontalLayout->addWidget(applyNCloseBtnBox);


        gridLayout->addLayout(horizontalLayout, 8, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        QWidget::setTabOrder(streetEdit, streetNrEdit);
        QWidget::setTabOrder(streetNrEdit, plzEdit);
        QWidget::setTabOrder(plzEdit, cityEdit);
        QWidget::setTabOrder(cityEdit, countryCmbBox);

        retranslateUi(NewRouteDialog);

        QMetaObject::connectSlotsByName(NewRouteDialog);
    } // setupUi

    void retranslateUi(QDialog *NewRouteDialog)
    {
        NewRouteDialog->setWindowTitle(QApplication::translate("NewRouteDialog", "Neuer Wegpunkt", 0));
        label->setText(QApplication::translate("NewRouteDialog", "Hausnummer:", 0));
        label_2->setText(QApplication::translate("NewRouteDialog", "PLZ", 0));
        streetLbl->setText(QApplication::translate("NewRouteDialog", "Stra\303\237e:", 0));
        plzCityLbl->setText(QApplication::translate("NewRouteDialog", "Stadt:", 0));
        countryLbl->setText(QApplication::translate("NewRouteDialog", "Land:", 0));
        countryCmbBox->setItemText(0, QApplication::translate("NewRouteDialog", "Deutschland", 0));
        countryCmbBox->setItemText(1, QApplication::translate("NewRouteDialog", "Italien", 0));
        countryCmbBox->setItemText(2, QApplication::translate("NewRouteDialog", "Polen", 0));
        countryCmbBox->setItemText(3, QApplication::translate("NewRouteDialog", "Frankreich", 0));
        countryCmbBox->setItemText(4, QApplication::translate("NewRouteDialog", "Spanien", 0));
        countryCmbBox->setItemText(5, QApplication::translate("NewRouteDialog", "\303\226sterreich", 0));

    } // retranslateUi

};

namespace Ui {
    class NewRouteDialog: public Ui_NewRouteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWROUTEDIALOG_H
