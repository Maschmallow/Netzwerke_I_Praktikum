#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QStandardItemModel>

#include <chrono>
#include <ctime>

#include "network.h"

#include "newroutedialog.h"
#include "aboutdialog.h"
#include "parsejson.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_pNetwork(new MyNetwork)
{
    ui->setupUi(this);

    // setup toolbar background
    ui->mainToolBar->setStyleSheet("QToolBar {background: rgb(215,215,215)}");
    connect(ui->actionNewWaypoint, SIGNAL(triggered()), this, SLOT(AddNewWaypointDialog()));
    connect(ui->actionEdit, SIGNAL(triggered()), this, SLOT(EditWaypointDialog()));
    connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(RemoveWaypoint()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(AboutDialog()));
    connect(ui->actionMoveUp, SIGNAL(triggered()), this, SLOT(MoveUp()));
    connect(ui->actionMoveDown, SIGNAL(triggered()), this, SLOT(MoveDown()));

    m_pTableModel = new TableModel(this);

    ui->routeTbl->setModel(m_pTableModel);
    ui->routeTbl->resizeColumnsToContents();
    ui->routeTbl->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->actionEdit->setEnabled(false);
    ui->actionDelete->setEnabled(false);
    ui->actionMoveUp->setEnabled(false);
    ui->actionMoveDown->setEnabled(false);

    connect(ui->routeTbl->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this,
            SIGNAL(SelectionChanged(QItemSelection)));

    connect(this, SIGNAL(SelectionChanged(QItemSelection)),
            this, SLOT(UpdateActions(QItemSelection)));

    connect(ui->calcBtn, SIGNAL(clicked()), this, SLOT(CalcButtonPressed()));

    for (int c = 0; c < ui->routeTbl->horizontalHeader()->count(); ++c)
    {
        ui->routeTbl->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }

    ui->arrivalTimeEd->setTime(QTime::currentTime());
    ui->arrivalTimeEd->setDate(QDate::currentDate());
}

void MainWindow::CalcButtonPressed() {
    if (m_pTableModel->getList().size() < 2) {
        QMessageBox::information(this, tr("Zu wenig Wegpunkte"),
                                 tr("Es braucht eine Start- und eine Zieladdresse."));
        return;
    }

    QString querie = SetupMessage();
    QString reply = m_pNetwork->getDirection(querie);

    // Now parse reply
    ParseJson p(this);
    if (p.parse(reply))
    {
        QTime duration(0,0);
        duration = duration.addSecs(p.getDuration());
        ui->durationLbl->setText(duration.toString());

        double distanceInKm = p.getDistance() / 1000.0;
        QString number = QString::number(distanceInKm);

        ui->distanceLbl->setText( number.replace(".",",") + " km");

        QDateTime desiredArrivalTime = ui->arrivalTimeEd->dateTime();
        qint64 curTime = QDateTime::currentDateTime().toTime_t();
        qint64 actualArrivalTime = curTime + p.getDuration();

        int difference =
                desiredArrivalTime.toTime_t() - actualArrivalTime;

        if (difference > 15000) {
            // too early
            ui->statusLbl->setText("Sie sind zu früh. :/");
            m_pNetwork->activateLamp(MyNetwork::Yellow);
        }
        else if(difference <= 15000 && difference >= 0)
        {
            // perfect timing
            ui->statusLbl->setText("Sie werden rechtzeitig ankommen :).");
            m_pNetwork->activateLamp(MyNetwork::Green);
        }
        else {
            // too late
            ui->statusLbl->setText("Sie werden zu spät ankommen. :(");
            m_pNetwork->activateLamp(MyNetwork::Red);
        }
    }
}

QString MainWindow::SetupMessage() {
    QString getRequest = "GET /maps/api/directions/json?origin=";

    QList<Address> *list = &m_pTableModel->getList();

    Address StartAddress = list->first();
    getRequest += StartAddress.getStreet() +
            StartAddress.getStreetNr() +
            StartAddress.getPlz() +
            StartAddress.getCity() +
            StartAddress.country;

    getRequest += "&destination=";
    Address EndAddress = list->last();
    getRequest += EndAddress.getStreet() +
            EndAddress.getStreetNr() +
            EndAddress.getPlz() +
            EndAddress.getCity() +
            EndAddress.country;

    if (list->size() > 2) {
        getRequest += "&waypoints=";
        int nrOfIntermediatWaypoints = list->size()-1;

        for(int i = 1; i < nrOfIntermediatWaypoints; i++) {
            Address tmp = list->at(i);
            getRequest += tmp.getStreet() +
                    tmp.getStreetNr() +
                    tmp.getPlz() +
                    tmp.getCity() +
                    tmp.country + "|";
        }
    }
    getRequest += "&language=de";
    return getRequest;
}

void MainWindow::EditWaypointDialog() {
    QItemSelectionModel *selectionModel = ui->routeTbl->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();
    Address address;
    int row = -1;

    foreach(QModelIndex index, indexes) {
        row = index.row();
        QModelIndex streetIndex = m_pTableModel->index(row, 0, QModelIndex());
        QVariant streetName = m_pTableModel->data(streetIndex, Qt::DisplayRole);
        address.street = streetName.toString();

        QModelIndex streetNrIndex = m_pTableModel->index(row, 1, QModelIndex());
        QVariant streetNrName = m_pTableModel->data(streetNrIndex, Qt::DisplayRole);
        address.streetNr = streetNrName.toString();

        QModelIndex plzIndex = m_pTableModel->index(row, 2, QModelIndex());
        QVariant plz = m_pTableModel->data(plzIndex, Qt::DisplayRole);
        address.plz = plz.toString();

        QModelIndex cityIndex = m_pTableModel->index(row, 3, QModelIndex());
        QVariant cityName = m_pTableModel->data(cityIndex, Qt::DisplayRole);
        address.city = cityName.toString();

        QModelIndex countryIndex = m_pTableModel->index(row, 4, QModelIndex());
        QVariant country = m_pTableModel->data(countryIndex, Qt::DisplayRole);
        address.country = country.toString();
    }

    NewRouteDialog aDialog;
    aDialog.setWindowTitle(tr("Wegpunkt bearbeiten"));
    aDialog.setAddress(address);
    if (aDialog.exec()) {
        Address newAddress = aDialog.getAddress();
        if (newAddress != address) {
            QModelIndex index = m_pTableModel->index(row, 0, QModelIndex());
            m_pTableModel->setData(index, newAddress.street, Qt::EditRole);
            index = m_pTableModel->index(row, 1, QModelIndex());
            m_pTableModel->setData(index, newAddress.streetNr, Qt::EditRole);
            index = m_pTableModel->index(row, 2, QModelIndex());
            m_pTableModel->setData(index, newAddress.plz, Qt::EditRole);
            index = m_pTableModel->index(row, 3, QModelIndex());
            m_pTableModel->setData(index, newAddress.city, Qt::EditRole);
            index = m_pTableModel->index(row, 4, QModelIndex());
            m_pTableModel->setData(index, newAddress.country, Qt::EditRole);
        }
    }
}

void MainWindow::UpdateActions(const QItemSelection &selection) {
    QModelIndexList indexes = selection.indexes();

    if(!indexes.isEmpty()) {
        ui->actionEdit->setEnabled(true);
        ui->actionDelete->setEnabled(true);
        if (m_pTableModel->getList().size() > 1) {
            ui->actionMoveDown->setEnabled(true);
            ui->actionMoveUp->setEnabled(true);
        }
    } else {
        ui->actionDelete->setEnabled(false);
        ui->actionEdit->setEnabled(false);
        ui->actionMoveDown->setEnabled(false);
        ui->actionMoveUp->setEnabled(false);
    }
}

void MainWindow::RemoveWaypoint() {
    QItemSelectionModel *selectionModel = ui->routeTbl->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach(QModelIndex index, indexes) {
        int row = index.row();
        m_pTableModel->removeRows(row, 1, QModelIndex());
    }

    if (m_pTableModel->getList().size() < 5) {
        ui->actionNewWaypoint->setEnabled(true);
    }
}

void MainWindow::MoveUp() {
    QItemSelectionModel *selectionModel = ui->routeTbl->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach(QModelIndex index, indexes) {
        int row = index.row();
        if(row == 0)
            continue;
        m_pTableModel->moveRows(QModelIndex(), row, row, QModelIndex(), row-1);
    }
}

void MainWindow::MoveDown()
{
    QItemSelectionModel *selectionModel = ui->routeTbl->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach(QModelIndex index, indexes) {
        int row = index.row();
        if(row == m_pTableModel->getList().size()-1)
            continue;
        m_pTableModel->moveRows(QModelIndex(), row+1, row+1, QModelIndex(), row);
    }
}

void MainWindow::AboutDialog() {
    aboutdialog aDialog;

    aDialog.exec();
}

void MainWindow::AddNewWaypointDialog() {
    NewRouteDialog aDialog;

    if (aDialog.exec()) {
        Address a = aDialog.getAddress();
        addEntry(a);
    }
}

void MainWindow::addEntry(Address& address) {
    QList<Address> list = m_pTableModel->getList();
    if(!list.contains(address)) {
        int newRow = m_pTableModel->rowCount(QModelIndex());
        m_pTableModel->insertRows(
                    newRow,
                    1,
                    QModelIndex());

        QModelIndex index = m_pTableModel->index(newRow, 0, QModelIndex());
        m_pTableModel->setData(index, address.street, Qt::EditRole);
        index = m_pTableModel->index(newRow, 1, QModelIndex());
        m_pTableModel->setData(index, address.streetNr, Qt::EditRole);
        index = m_pTableModel->index(newRow, 2,QModelIndex());
        m_pTableModel->setData(index, address.plz, Qt::EditRole);
        index = m_pTableModel->index(newRow, 3, QModelIndex());
        m_pTableModel->setData(index, address.city, Qt::EditRole);
        index = m_pTableModel->index(newRow, 4, QModelIndex());
        m_pTableModel->setData(index, address.country, Qt::EditRole);
    } else {
        QMessageBox::information(this, tr("Doppelte Adressen"),
                                 tr("Die Addresse existiert bereits"));
    }

    if (m_pTableModel->getList().size() > 4) {
        ui->actionNewWaypoint->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete m_pNetwork;
    delete ui;
}
