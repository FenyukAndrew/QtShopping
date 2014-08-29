#include "dialogshops.h"
#include "ui_dialogshops.h"

DialogShops::DialogShops(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShops)
{
    ui->setupUi(this);
}

DialogShops::~DialogShops()
{
    delete ui;
}
