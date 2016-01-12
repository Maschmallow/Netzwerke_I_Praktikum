/********************************************************************************
** Form generated from reading UI file 'aboutdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_aboutdialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *kthxbyeLbl;
    QFormLayout *formLayout;
    QLabel *osVersionHeadLbl;
    QLabel *osVersionLbl;
    QLabel *cpuArchitectureHeadLbl;
    QLabel *cpuArchitectureLbl;
    QLabel *authorHeadLbl;
    QLabel *authorLbl;
    QLabel *authorHeadLbl_2;
    QLabel *authorLbl_2;
    QPushButton *closeBtn;

    void setupUi(QDialog *aboutdialog)
    {
        if (aboutdialog->objectName().isEmpty())
            aboutdialog->setObjectName(QStringLiteral("aboutdialog"));
        aboutdialog->resize(360, 170);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(aboutdialog->sizePolicy().hasHeightForWidth());
        aboutdialog->setSizePolicy(sizePolicy);
        aboutdialog->setMaximumSize(QSize(360, 170));
        verticalLayout = new QVBoxLayout(aboutdialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        kthxbyeLbl = new QLabel(aboutdialog);
        kthxbyeLbl->setObjectName(QStringLiteral("kthxbyeLbl"));
        kthxbyeLbl->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(kthxbyeLbl);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        osVersionHeadLbl = new QLabel(aboutdialog);
        osVersionHeadLbl->setObjectName(QStringLiteral("osVersionHeadLbl"));

        formLayout->setWidget(0, QFormLayout::LabelRole, osVersionHeadLbl);

        osVersionLbl = new QLabel(aboutdialog);
        osVersionLbl->setObjectName(QStringLiteral("osVersionLbl"));

        formLayout->setWidget(0, QFormLayout::FieldRole, osVersionLbl);

        cpuArchitectureHeadLbl = new QLabel(aboutdialog);
        cpuArchitectureHeadLbl->setObjectName(QStringLiteral("cpuArchitectureHeadLbl"));

        formLayout->setWidget(2, QFormLayout::LabelRole, cpuArchitectureHeadLbl);

        cpuArchitectureLbl = new QLabel(aboutdialog);
        cpuArchitectureLbl->setObjectName(QStringLiteral("cpuArchitectureLbl"));

        formLayout->setWidget(2, QFormLayout::FieldRole, cpuArchitectureLbl);

        authorHeadLbl = new QLabel(aboutdialog);
        authorHeadLbl->setObjectName(QStringLiteral("authorHeadLbl"));

        formLayout->setWidget(3, QFormLayout::LabelRole, authorHeadLbl);

        authorLbl = new QLabel(aboutdialog);
        authorLbl->setObjectName(QStringLiteral("authorLbl"));

        formLayout->setWidget(3, QFormLayout::FieldRole, authorLbl);

        authorHeadLbl_2 = new QLabel(aboutdialog);
        authorHeadLbl_2->setObjectName(QStringLiteral("authorHeadLbl_2"));

        formLayout->setWidget(4, QFormLayout::LabelRole, authorHeadLbl_2);

        authorLbl_2 = new QLabel(aboutdialog);
        authorLbl_2->setObjectName(QStringLiteral("authorLbl_2"));

        formLayout->setWidget(4, QFormLayout::FieldRole, authorLbl_2);


        verticalLayout->addLayout(formLayout);

        closeBtn = new QPushButton(aboutdialog);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));

        verticalLayout->addWidget(closeBtn);


        retranslateUi(aboutdialog);
        QObject::connect(closeBtn, SIGNAL(clicked()), aboutdialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(aboutdialog);
    } // setupUi

    void retranslateUi(QDialog *aboutdialog)
    {
        aboutdialog->setWindowTitle(QApplication::translate("aboutdialog", "\303\234ber P\303\274nktlichkeitsassistent v.0.1", 0));
        kthxbyeLbl->setText(QApplication::translate("aboutdialog", "Vielen Dank, dass Sie den P\303\274nktlichkeitsassistenten verwenden.", 0));
        osVersionHeadLbl->setText(QApplication::translate("aboutdialog", "Betriebssystem:", 0));
        osVersionLbl->setText(QString());
        cpuArchitectureHeadLbl->setText(QApplication::translate("aboutdialog", "CPU Architektur:", 0));
        cpuArchitectureLbl->setText(QString());
        authorHeadLbl->setText(QApplication::translate("aboutdialog", "Autor:", 0));
        authorLbl->setText(QApplication::translate("aboutdialog", "Paul Masch", 0));
        authorHeadLbl_2->setText(QApplication::translate("aboutdialog", "Erstellt am:", 0));
        authorLbl_2->setText(QApplication::translate("aboutdialog", "10.12.2015", 0));
        closeBtn->setText(QApplication::translate("aboutdialog", "Cool!", 0));
    } // retranslateUi

};

namespace Ui {
    class aboutdialog: public Ui_aboutdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
