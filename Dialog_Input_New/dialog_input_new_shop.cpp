#include "dialog_input_new_shop.h"
#include "ui_dialog_input_new_shop.h"
#include <QLineEdit>
#include "Common_parameters.h"

Dialog_Input_New_Shop::Dialog_Input_New_Shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Shop)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

Dialog_Input_New_Shop::~Dialog_Input_New_Shop()
{
    delete ui;
}

void Dialog_Input_New_Shop::on_pushButton_OK_clicked()
{
    m_Shop.id=0;
    m_Shop.Name=ui->LineEdit_Name_Shop->text();
    m_Shop.Note=ui->LineEdit_Note->text();
    m_Shop.Place=ui->LineEdit_Place->text();
    QDialog::accept();
}

void Dialog_Input_New_Shop::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
