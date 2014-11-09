#include "dialoghistoryitems.h"
#include "ui_dialoghistoryitems.h"

DialogHistoryItems::DialogHistoryItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHistoryItems)
{
    ui->setupUi(this);
}

DialogHistoryItems::~DialogHistoryItems()
{
    delete ui;
}
