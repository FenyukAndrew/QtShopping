#include "dialogitems.h"
#include "ui_dialogitems.h"

DialogItems::DialogItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogItems)
{
    ui->setupUi(this);
}

DialogItems::~DialogItems()
{
    delete ui;
}
