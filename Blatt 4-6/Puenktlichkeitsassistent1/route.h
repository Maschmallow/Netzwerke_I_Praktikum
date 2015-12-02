#ifndef ROUTE_H
#define ROUTE_H

#include <QString>
#include <QTime>
#include <QAbstractTableModel>
#include <QList>

struct Address {
    QString street;
    QString streetNr;
    QString country;
    QString city;
    QString plz;

    Address() :
        street(""), streetNr(""), country(""), city(""), plz("") {}

    Address(QString s, QString nr, QString co, QString ci, QString pl) :
        street(s), streetNr(nr), country(co), city(ci), plz(pl)
    {}

    void setAddress(QString s, QString nr, QString co, QString ci, QString pl) {
        street = s;
        streetNr = nr;
        country = co;
        city = ci;
        plz = pl;
    }

    inline bool operator==(const Address& rhs) {
        return street == rhs.street && streetNr == rhs.streetNr &&
                country == rhs.country && city == rhs.city && plz == rhs.plz;
    }

    inline bool operator!=(const Address& rhs) {
        return street != rhs.street || streetNr != rhs.streetNr ||
                country != rhs.country || city != rhs.city || plz != rhs.plz;
    }
};

class Route {
private:
    typedef Address Destination;
    typedef Address Start;

    Destination m_destination;
    Start m_start;
    QTime m_travelTime;

public:
    bool isTooLate();
    void setDestination(QString s, QString nr, QString country, QString city, QString plz) {
        m_destination.setAddress(s, nr, country, city, plz);
    }
    void setStart(QString s, QString nr, QString country, QString city, QString plz) {
        m_start.setAddress(s, nr, country, city, plz);
    }

    Destination getDestination() const { return m_destination; }
    Start getStart() const {return m_start; }

    void setTravelTime(int h, int m, int s) {
        m_travelTime.setHMS(h, m, s);
    }

    QTime getTravelTime() {
        return m_travelTime;
    }
};

class TableModel : public QAbstractTableModel
{
public:
    TableModel(QObject *parent = 0);
    TableModel(QList<Address> listOfAddresses, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) Q_DECL_OVERRIDE;

    QList<Address> getList() { return m_listOfAddresses; }

private:
    QList<Address> m_listOfAddresses;
};

#endif // ROUTE-H

