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
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
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
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionMoveUp;
    QAction *actionMoveDown;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableView *routeTbl;
    QGridLayout *gridLayout;
    QWebView *webView;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QFormLayout *formLayout_2;
    QLabel *arrivalHeadLbl;
    QDateTimeEdit *arrivalTimeEd;
    QPushButton *calcBtn;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QGridLayout *gridLayout_3;
    QLabel *statusLbl;
    QLabel *durationHeadLbl;
    QLabel *durationLbl;
    QLabel *distanceHeadLbl;
    QLabel *distanceLbl;
    QLabel *statusHeadLbl;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuHilfe;
    QMenu *menuBearbeiten;
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
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MyFiles/Icons/resources/help32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon4);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionHelp->setIcon(icon4);
        actionMoveUp = new QAction(MainWindow);
        actionMoveUp->setObjectName(QStringLiteral("actionMoveUp"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MyFiles/Icons/resources/up32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveUp->setIcon(icon5);
        actionMoveDown = new QAction(MainWindow);
        actionMoveDown->setObjectName(QStringLiteral("actionMoveDown"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MyFiles/Icons/resources/down32x32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMoveDown->setIcon(icon6);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        routeTbl = new QTableView(centralWidget);
        routeTbl->setObjectName(QStringLiteral("routeTbl"));

        verticalLayout->addWidget(routeTbl);

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

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout_2 = new QFormLayout(groupBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        arrivalHeadLbl = new QLabel(groupBox);
        arrivalHeadLbl->setObjectName(QStringLiteral("arrivalHeadLbl"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(arrivalHeadLbl->sizePolicy().hasHeightForWidth());
        arrivalHeadLbl->setSizePolicy(sizePolicy1);
        arrivalHeadLbl->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, arrivalHeadLbl);

        arrivalTimeEd = new QDateTimeEdit(groupBox);
        arrivalTimeEd->setObjectName(QStringLiteral("arrivalTimeEd"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, arrivalTimeEd);

        calcBtn = new QPushButton(groupBox);
        calcBtn->setObjectName(QStringLiteral("calcBtn"));

        formLayout_2->setWidget(7, QFormLayout::FieldRole, calcBtn);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        statusLbl = new QLabel(groupBox_2);
        statusLbl->setObjectName(QStringLiteral("statusLbl"));

        gridLayout_3->addWidget(statusLbl, 2, 1, 1, 1);

        durationHeadLbl = new QLabel(groupBox_2);
        durationHeadLbl->setObjectName(QStringLiteral("durationHeadLbl"));
        sizePolicy1.setHeightForWidth(durationHeadLbl->sizePolicy().hasHeightForWidth());
        durationHeadLbl->setSizePolicy(sizePolicy1);
        durationHeadLbl->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(durationHeadLbl, 0, 0, 1, 1);

        durationLbl = new QLabel(groupBox_2);
        durationLbl->setObjectName(QStringLiteral("durationLbl"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(durationLbl->sizePolicy().hasHeightForWidth());
        durationLbl->setSizePolicy(sizePolicy2);
        durationLbl->setMaximumSize(QSize(300, 16777215));

        gridLayout_3->addWidget(durationLbl, 0, 1, 1, 1);

        distanceHeadLbl = new QLabel(groupBox_2);
        distanceHeadLbl->setObjectName(QStringLiteral("distanceHeadLbl"));
        sizePolicy1.setHeightForWidth(distanceHeadLbl->sizePolicy().hasHeightForWidth());
        distanceHeadLbl->setSizePolicy(sizePolicy1);
        distanceHeadLbl->setMaximumSize(QSize(200, 16777215));

        gridLayout_3->addWidget(distanceHeadLbl, 1, 0, 1, 1);

        distanceLbl = new QLabel(groupBox_2);
        distanceLbl->setObjectName(QStringLiteral("distanceLbl"));
        sizePolicy2.setHeightForWidth(distanceLbl->sizePolicy().hasHeightForWidth());
        distanceLbl->setSizePolicy(sizePolicy2);
        distanceLbl->setMaximumSize(QSize(300, 16777215));

        gridLayout_3->addWidget(distanceLbl, 1, 1, 1, 1);

        statusHeadLbl = new QLabel(groupBox_2);
        statusHeadLbl->setObjectName(QStringLiteral("statusHeadLbl"));

        gridLayout_3->addWidget(statusHeadLbl, 2, 0, 1, 1);


        formLayout->setLayout(0, QFormLayout::LabelRole, gridLayout_3);


        formLayout_2->setWidget(10, QFormLayout::LabelRole, groupBox_2);


        verticalLayout_3->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout_3, 0, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 824, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuHilfe = new QMenu(menuBar);
        menuHilfe->setObjectName(QStringLiteral("menuHilfe"));
        menuBearbeiten = new QMenu(menuBar);
        menuBearbeiten->setObjectName(QStringLiteral("menuBearbeiten"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMovable(false);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuBearbeiten->menuAction());
        menuBar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionNewWaypoint);
        menuDatei->addSeparator();
        menuDatei->addAction(actionExit);
        menuHilfe->addAction(actionHelp);
        menuHilfe->addAction(actionAbout);
        menuBearbeiten->addAction(actionEdit);
        menuBearbeiten->addAction(actionDelete);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionMoveUp);
        menuBearbeiten->addAction(actionMoveDown);
        mainToolBar->addAction(actionNewWaypoint);
        mainToolBar->addAction(actionEdit);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionMoveUp);
        mainToolBar->addAction(actionMoveDown);
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
        actionExit->setToolTip(QApplication::translate("MainWindow", "Auf Wiedersehen ;)", 0));
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
        actionAbout->setText(QApplication::translate("MainWindow", "\303\234ber P\303\274nktlichkeitsassistenten", 0));
        actionHelp->setText(QApplication::translate("MainWindow", "Hilfe", 0));
        actionMoveUp->setText(QApplication::translate("MainWindow", "Auf", 0));
        actionMoveUp->setShortcut(QApplication::translate("MainWindow", "Ctrl+Up", 0));
        actionMoveDown->setText(QApplication::translate("MainWindow", "Ab", 0));
        actionMoveDown->setShortcut(QApplication::translate("MainWindow", "Ctrl+Down", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Einstellungen", 0));
        arrivalHeadLbl->setText(QApplication::translate("MainWindow", "Gew\303\274nschte Ankunftszeit", 0));
        arrivalTimeEd->setDisplayFormat(QApplication::translate("MainWindow", "dd.MM.yyyy HH:mm:ss", 0));
        calcBtn->setText(QApplication::translate("MainWindow", "Berechnen", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Ergebnis", 0));
        statusLbl->setText(QString());
        durationHeadLbl->setText(QApplication::translate("MainWindow", "Dauer:", 0));
        durationLbl->setText(QString());
        distanceHeadLbl->setText(QApplication::translate("MainWindow", "Entfernung:", 0));
        distanceLbl->setText(QApplication::translate("MainWindow", "0km", 0));
        statusHeadLbl->setText(QApplication::translate("MainWindow", "Status:", 0));
        menuDatei->setTitle(QApplication::translate("MainWindow", "Datei", 0));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "Hilfe", 0));
        menuBearbeiten->setTitle(QApplication::translate("MainWindow", "Bearbeiten", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
