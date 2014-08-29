#include "dialogedititem.h"
#include "ui_dialogedititem.h"

DialogEditItem::DialogEditItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditItem)
{
    ui->setupUi(this);
}

DialogEditItem::~DialogEditItem()
{
    delete ui;
}
