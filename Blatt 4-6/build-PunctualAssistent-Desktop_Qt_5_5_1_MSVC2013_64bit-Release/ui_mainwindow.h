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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionClose_2;
    QAction *closeButton;
    QAction *actionZwischenziel_Hinzuf_gen;
    QWidget *centralWidget;
    QTextEdit *StreetTextField;
    QTextEdit *HouseNr;
    QTextEdit *PlzTextField;
    QTextEdit *CityTextField;
    QLabel *StreetLabel;
    QLabel *cityLabel;
    QLabel *countryLabel;
    QComboBox *CountrySelect;
    QPushButton *SearchButton;
    QPushButton *ClearButton;
    QWebView *webView;
    QLabel *distanceInfo;
    QLabel *timeInfo;
    QLabel *distanceLabel;
    QLabel *timeLabel;
    QTimeEdit *Timeselect;
    QLabel *arivialTimeLabel;
    QMenuBar *menuBar;
    QMenu *menuMen;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(937, 624);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionClose_2 = new QAction(MainWindow);
        actionClose_2->setObjectName(QStringLiteral("actionClose_2"));
        closeButton = new QAction(MainWindow);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        actionZwischenziel_Hinzuf_gen = new QAction(MainWindow);
        actionZwischenziel_Hinzuf_gen->setObjectName(QStringLiteral("actionZwischenziel_Hinzuf_gen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        StreetTextField = new QTextEdit(centralWidget);
        StreetTextField->setObjectName(QStringLiteral("StreetTextField"));
        StreetTextField->setGeometry(QRect(170, 30, 271, 31));
        HouseNr = new QTextEdit(centralWidget);
        HouseNr->setObjectName(QStringLiteral("HouseNr"));
        HouseNr->setGeometry(QRect(450, 30, 51, 31));
        PlzTextField = new QTextEdit(centralWidget);
        PlzTextField->setObjectName(QStringLiteral("PlzTextField"));
        PlzTextField->setGeometry(QRect(170, 70, 101, 31));
        CityTextField = new QTextEdit(centralWidget);
        CityTextField->setObjectName(QStringLiteral("CityTextField"));
        CityTextField->setGeometry(QRect(280, 70, 221, 31));
        StreetLabel = new QLabel(centralWidget);
        StreetLabel->setObjectName(QStringLiteral("StreetLabel"));
        StreetLabel->setGeometry(QRect(26, 37, 141, 16));
        cityLabel = new QLabel(centralWidget);
        cityLabel->setObjectName(QStringLiteral("cityLabel"));
        cityLabel->setGeometry(QRect(90, 77, 71, 16));
        countryLabel = new QLabel(centralWidget);
        countryLabel->setObjectName(QStringLiteral("countryLabel"));
        countryLabel->setGeometry(QRect(120, 113, 41, 16));
        CountrySelect = new QComboBox(centralWidget);
        CountrySelect->setObjectName(QStringLiteral("CountrySelect"));
        CountrySelect->setGeometry(QRect(170, 113, 104, 26));
        SearchButton = new QPushButton(centralWidget);
        SearchButton->setObjectName(QStringLiteral("SearchButton"));
        SearchButton->setGeometry(QRect(390, 110, 113, 32));
        ClearButton = new QPushButton(centralWidget);
        ClearButton->setObjectName(QStringLiteral("ClearButton"));
        ClearButton->setGeometry(QRect(270, 110, 113, 32));
        webView = new QWebView(centralWidget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(30, 160, 901, 421));
        webView->setUrl(QUrl(QStringLiteral("file:///Users/florianfrank/Projekte/QT/PunctualAssistent/Maps.html")));
        distanceInfo = new QLabel(centralWidget);
        distanceInfo->setObjectName(QStringLiteral("distanceInfo"));
        distanceInfo->setGeometry(QRect(660, 40, 91, 16));
        distanceInfo->setLayoutDirection(Qt::LeftToRight);
        distanceInfo->setAlignment(Qt::AlignCenter);
        timeInfo = new QLabel(centralWidget);
        timeInfo->setObjectName(QStringLiteral("timeInfo"));
        timeInfo->setGeometry(QRect(740, 40, 91, 16));
        timeInfo->setLayoutDirection(Qt::LeftToRight);
        timeInfo->setAlignment(Qt::AlignCenter);
        distanceLabel = new QLabel(centralWidget);
        distanceLabel->setObjectName(QStringLiteral("distanceLabel"));
        distanceLabel->setGeometry(QRect(680, 70, 59, 16));
        timeLabel = new QLabel(centralWidget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setGeometry(QRect(760, 70, 59, 16));
        Timeselect = new QTimeEdit(centralWidget);
        Timeselect->setObjectName(QStringLiteral("Timeselect"));
        Timeselect->setGeometry(QRect(530, 70, 118, 24));
        arivialTimeLabel = new QLabel(centralWidget);
        arivialTimeLabel->setObjectName(QStringLiteral("arivialTimeLabel"));
        arivialTimeLabel->setGeometry(QRect(540, 40, 72, 16));
        arivialTimeLabel->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 937, 22));
        menuMen = new QMenu(menuBar);
        menuMen->setObjectName(QStringLiteral("menuMen"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuMen->menuAction());
        menuMen->addAction(closeButton);
        menuMen->addAction(actionZwischenziel_Hinzuf_gen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "P\303\274nktlichkeits Assistent", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        actionClose_2->setText(QApplication::translate("MainWindow", "Close", 0));
        closeButton->setText(QApplication::translate("MainWindow", "Close", 0));
        actionZwischenziel_Hinzuf_gen->setText(QApplication::translate("MainWindow", "Zwischenziel Hinzuf\303\274gen", 0));
        StreetLabel->setText(QApplication::translate("MainWindow", "Stra\303\237e/Hausnummer: ", 0));
        cityLabel->setText(QApplication::translate("MainWindow", "PLZ/Stadt:", 0));
        countryLabel->setText(QApplication::translate("MainWindow", "Land:", 0));
        CountrySelect->clear();
        CountrySelect->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Deutschland", 0)
         << QApplication::translate("MainWindow", "\303\226sterreich", 0)
         << QApplication::translate("MainWindow", "Schweiz", 0)
         << QApplication::translate("MainWindow", "Spanien", 0)
         << QApplication::translate("MainWindow", "Niederlande", 0)
         << QApplication::translate("MainWindow", "Polen", 0)
         << QApplication::translate("MainWindow", "Tschechien", 0)
         << QApplication::translate("MainWindow", "D\303\244nemark", 0)
        );
        SearchButton->setText(QApplication::translate("MainWindow", "Search", 0));
        ClearButton->setText(QApplication::translate("MainWindow", "Clear", 0));
        distanceInfo->setText(QApplication::translate("MainWindow", "Entfernung", 0));
        timeInfo->setText(QApplication::translate("MainWindow", "Zeit", 0));
        distanceLabel->setText(QApplication::translate("MainWindow", "0 km", 0));
        timeLabel->setText(QApplication::translate("MainWindow", "00:00 h", 0));
        arivialTimeLabel->setText(QApplication::translate("MainWindow", "Ankunfszeit", 0));
        menuMen->setTitle(QApplication::translate("MainWindow", "Men\303\274", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
