#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include <QSysInfo>

aboutdialog::aboutdialog(QWidget *parent) :
    QDialog(parent, Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint),
    ui(new Ui::aboutdialog)
{
    ui->setupUi(this);

    ui->osVersionLbl->setText(QSysInfo::prettyProductName());
    ui->cpuArchitectureLbl->setText(QSysInfo::buildCpuArchitecture());
}

aboutdialog::~aboutdialog()
{
    delete ui;
}
