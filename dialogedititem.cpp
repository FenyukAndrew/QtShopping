#include "dialogedititem.h"
#include "ui_dialogedititem.h"
#include "Common_parameters.h"

DialogEditItem::DialogEditItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEditItem)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogEditItem::~DialogEditItem()
{
    delete ui;
}
