/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewWaypoint;
    QAction *actionExit;
    QAction *actionEdit;
    QAction *actionDelete;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_2;
    QTableView *routeTbl;
    QGridLayout *gridLayout;
    QWebView *webView;
    QFormLayout *formLayout;
    QLabel *distanceLbl;
    QLabel *distanceHeadLbl;
    QLabel *durationHeadLbl;
    QLabel *durationLbl;
    QTimeEdit *arrivalTimeEd;
    QLabel *arrivalHeadLbl;
    QPushButton *calcBtn;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(824, 609);
        actionNewWaypoint = new QAction(MainWindow);
        actionNewWaypoint->setObjectName(QStringLiteral("actionNewWaypoint"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MyFiles/Icons/resources/earthicon256x256.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewWaypoint->setIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MyFiles/Icons/resources/Exit32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionEdit = new QAction(MainWindow);
        actionEdit->setObjectName(QStringLiteral("actionEdit"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MyFiles/Icons/resources/edit32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEdit->setIcon(icon2);
        actionDelete = new QAction(MainWindow);
        actionDelete->setObjectName(QStringLiteral("actionDelete"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MyFiles/Icons/resources/delete32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon3);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        routeTbl = new QTableView(centralWidget);
        routeTbl->setObjectName(QStringLiteral("routeTbl"));

        gridLayout_2->addWidget(routeTbl, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetNoConstraint);
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(webView->sizePolicy().hasHeightForWidth());
        webView->setSizePolicy(sizePolicy);
        webView->setUrl(QUrl(QStringLiteral("file:///C:/Users/Paul/Documents/Netzwerke_I_Praktikum/Blatt 4-6/Puenktlichkeitsassistent1/Maps.html")));

        gridLayout->addWidget(webView, 0, 2, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setSizeConstraint(QLayout::SetFixedSize);
        distanceLbl = new QLabel(centralWidget);
        distanceLbl->setObjectName(QStringLiteral("distanceLbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(distanceLbl->sizePolicy().hasHeightForWidth());
        distanceLbl->setSizePolicy(sizePolicy1);
        distanceLbl->setMaximumSize(QSize(300, 16777215));

        formLayout->setWidget(3, QFormLayout::FieldRole, distanceLbl);

        distanceHeadLbl = new QLabel(centralWidget);
        distanceHeadLbl->setObjectName(QStringLiteral("distanceHeadLbl"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(distanceHeadLbl->sizePolicy().hasHeightForWidth());
        distanceHeadLbl->setSizePolicy(sizePolicy2);
        distanceHeadLbl->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(3, QFormLayout::LabelRole, distanceHeadLbl);

        durationHeadLbl = new QLabel(centralWidget);
        durationHeadLbl->setObjectName(QStringLiteral("durationHeadLbl"));
        sizePolicy2.setHeightForWidth(durationHeadLbl->sizePolicy().hasHeightForWidth());
        durationHeadLbl->setSizePolicy(sizePolicy2);
        durationHeadLbl->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(4, QFormLayout::LabelRole, durationHeadLbl);

        durationLbl = new QLabel(centralWidget);
        durationLbl->setObjectName(QStringLiteral("durationLbl"));
        sizePolicy1.setHeightForWidth(durationLbl->sizePolicy().hasHeightForWidth());
        durationLbl->setSizePolicy(sizePolicy1);
        durationLbl->setMaximumSize(QSize(300, 16777215));

        formLayout->setWidget(4, QFormLayout::FieldRole, durationLbl);

        arrivalTimeEd = new QTimeEdit(centralWidget);
        arrivalTimeEd->setObjectName(QStringLiteral("arrivalTimeEd"));

        formLayout->setWidget(0, QFormLayout::FieldRole, arrivalTimeEd);

        arrivalHeadLbl = new QLabel(centralWidget);
        arrivalHeadLbl->setObjectName(QStringLiteral("arrivalHeadLbl"));
        sizePolicy2.setHeightForWidth(arrivalHeadLbl->sizePolicy().hasHeightForWidth());
        arrivalHeadLbl->setSizePolicy(sizePolicy2);
        arrivalHeadLbl->setMaximumSize(QSize(200, 16777215));

        formLayout->setWidget(0, QFormLayout::LabelRole, arrivalHeadLbl);

        calcBtn = new QPushButton(centralWidget);
        calcBtn->setObjectName(QStringLiteral("calcBtn"));

        formLayout->setWidget(5, QFormLayout::FieldRole, calcBtn);


        gridLayout->addLayout(formLayout, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 824, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuDatei->addAction(actionNewWaypoint);
        menuDatei->addAction(actionEdit);
        menuDatei->addAction(actionDelete);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExit);
        mainToolBar->addAction(actionNewWaypoint);
        mainToolBar->addAction(actionEdit);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "P\303\274nktlichkeitsassistent", 0));
        actionNewWaypoint->setText(QApplication::translate("MainWindow", "Neuer Wegpunkt", 0));
#ifndef QT_NO_TOOLTIP
        actionNewWaypoint->setToolTip(QApplication::translate("MainWindow", "F\303\274ge einen Wegpunkt hinzu", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionNewWaypoint->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        actionNewWaypoint->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        actionNewWaypoint->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Schlie\303\237en", 0));
#ifndef QT_NO_TOOLTIP
        actionExit->setToolTip(QApplication::translate("MainWindow", "Tschau bis bald Noob :D", 0));
#endif // QT_NO_TOOLTIP
        actionExit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
        actionEdit->setText(QApplication::translate("MainWindow", "Bearbeiten", 0));
#ifndef QT_NO_TOOLTIP
        actionEdit->setToolTip(QApplication::translate("MainWindow", "Bearbeite einen Wegpunkt", 0));
#endif // QT_NO_TOOLTIP
        actionEdit->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        actionDelete->setText(QApplication::translate("MainWindow", "L\303\266schen", 0));
#ifndef QT_NO_TOOLTIP
        actionDelete->setToolTip(QApplication::translate("MainWindow", "L\303\266sche einen Wegpunkt", 0));
#endif // QT_NO_TOOLTIP
        actionDelete->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        distanceLbl->setText(QApplication::translate("MainWindow", "0km", 0));
        distanceHeadLbl->setText(QApplication::translate("MainWindow", "Entfernung:", 0));
        durationHeadLbl->setText(QApplication::translate("MainWindow", "Dauer:", 0));
        durationLbl->setText(QApplication::translate("MainWindow", "0km", 0));
        arrivalTimeEd->setDisplayFormat(QApplication::translate("MainWindow", "HH:mm:ss", 0));
        arrivalHeadLbl->setText(QApplication::translate("MainWindow", "Gew\303\274nschte Ankunftszeit", 0));
        calcBtn->setText(QApplication::translate("MainWindow", "Berechnen", 0));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
