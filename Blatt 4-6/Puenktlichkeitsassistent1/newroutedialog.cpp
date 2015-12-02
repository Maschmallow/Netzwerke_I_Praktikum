#include "newroutedialog.h"
#include "ui_newroutedialog.h"

#include <QAbstractButton>
#include <qdebug.h>

NewRouteDialog::NewRouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRouteDialog)
{
    ui->setupUi(this);
    QWidget::setFixedSize(300,160);
    connect(ui->applyNCloseBtnBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(buttons(QAbstractButton*)));
}

void NewRouteDialog::buttons(QAbstractButton *button) {
    if(button->text() == tr("Close")) {
        this->close();
    } else if (button->text() == tr("Apply")) {
        accept();
    }
    else
        qDebug() << "Button was pressed but no handled properly.";
}

void NewRouteDialog::setAddress(Address &address) {
    ui->cityEdit->setText(address.city);
    int index = ui->countryCmbBox->findText(address.country);
    ui->countryCmbBox->setCurrentIndex(index);
    ui->plzEdit->setText(address.plz);
    ui->streetEdit->setText(address.street);
    ui->streetNrEdit->setText(address.streetNr);
}

Address NewRouteDialog::getAddress() {
    Address ret;
    ret.city = ui->cityEdit->text();
    ret.country = ui->countryCmbBox->currentText();
    ret.plz = ui->plzEdit->text();
    ret.street = ui->streetEdit->text();
    ret.streetNr = ui->streetNrEdit->text();
    return ret;
}

NewRouteDialog::~NewRouteDialog()
{
    delete ui;
}
