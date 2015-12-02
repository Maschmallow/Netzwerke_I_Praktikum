#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSortFilterProxyModel>
#include "network.h"

#include "newroutedialog.h"

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

    m_pTableModel = new TableModel(this);

    ui->routeTbl->setModel(m_pTableModel);
    ui->routeTbl->resizeColumnsToContents();
    ui->routeTbl->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->actionEdit->setEnabled(false);
    ui->actionDelete->setEnabled(false);

    connect(ui->routeTbl->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this,
            SIGNAL(SelectionChanged(QItemSelection)));

    connect(this, SIGNAL(SelectionChanged(QItemSelection)),
            this, SLOT(UpdateActions(QItemSelection)));

    for (int c = 0; c < ui->routeTbl->horizontalHeader()->count(); ++c)
    {
        ui->routeTbl->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
    }
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
    } else {
        ui->actionDelete->setEnabled(false);
        ui->actionEdit->setEnabled(false);
    }
}

void MainWindow::RemoveWaypoint() {
    QItemSelectionModel *selectionModel = ui->routeTbl->selectionModel();

    QModelIndexList indexes = selectionModel->selectedRows();

    foreach(QModelIndex index, indexes) {
        int row = index.row();
        m_pTableModel->removeRows(row, 1, QModelIndex());
    }
}

void MainWindow::AddNewWaypointDialog() {
    NewRouteDialog aDialog;

    if (aDialog.exec()) {
        Address a = aDialog.getAddress();
        addEntry(a);
        m_pNetwork->getDirection();
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
}

MainWindow::~MainWindow()
{
    delete m_pNetwork;
    delete ui;
}
