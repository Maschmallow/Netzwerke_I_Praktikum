#ifndef NEWROUTE_H
#define NEWROUTE_H

#include <QDialog>

#include "route.h"

class QAbstractButton;

namespace Ui {
class NewRouteDialog;
}

class NewRouteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewRouteDialog(QWidget *parent = 0);
    ~NewRouteDialog();

    Address getAddress();
    void setAddress(Address &address);

private slots:
    void buttons(QAbstractButton *button);

private:
    Ui::NewRouteDialog *ui;
};

#endif // NEWROUTE_H
