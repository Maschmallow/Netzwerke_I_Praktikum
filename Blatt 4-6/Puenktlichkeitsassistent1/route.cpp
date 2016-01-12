#include "route.h"

#include <QDebug>

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

TableModel::TableModel(QList<Address> listOfAddresses, QObject *parent)
    : QAbstractTableModel(parent)
{
    m_listOfAddresses = listOfAddresses;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_listOfAddresses.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 5;
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_listOfAddresses.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        Address address = m_listOfAddresses.at(index.row());

        switch(index.column()) {
        case 0: return address.street;
            break;
        case 1: return address.streetNr;
            break;
        case 2: return address.plz;
            break;
        case 3: return address.city;
            break;
        case 4: return address.country;
            break;
        }
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Straße");

            case 1:
                return tr("Nr");

            case 2:
                return tr("PLZ");

            case 3:
                return tr("Stadt");

            case 4:
                return tr("Land");

            default:
                return QVariant();
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        Address address;
        m_listOfAddresses.insert(position, address);
    }

    endInsertRows();
    return true;
}
//! [4]

bool TableModel::moveRows(const QModelIndex &sourceParent,
                          int sourceRow,
                          int count,
                          const QModelIndex &destinationParent,
                          int destinationChild)
{
    Q_UNUSED(sourceParent);
    Q_UNUSED(destinationParent);
    beginMoveRows(QModelIndex(), sourceRow, sourceRow, QModelIndex(), destinationChild);

    for (int i = 0; i <= sourceRow-count; i++)
       m_listOfAddresses.swap(sourceRow+i, destinationChild);

    endMoveRows();
    return true;
}


//! [5]
bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        m_listOfAddresses.removeAt(position);
    }

    endRemoveRows();
    return true;
}
//! [5]

//! [6]
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        Address address = m_listOfAddresses.value(row);

        if (index.column() == 0)
            address.street = value.toString();
        else if (index.column() == 1)
            address.streetNr = value.toString();
        else if (index.column() == 2)
            address.plz = value.toString();
        else if (index.column() == 3)
            address.city = value.toString();
        else if (index.column() == 4)
            address.country = value.toString();
        else
            return false;

        m_listOfAddresses.replace(row, address);

        emit(dataChanged(index, index));

        return true;
    }

    return false;
}
//! [6]

//! [7]
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

