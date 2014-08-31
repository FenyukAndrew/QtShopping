#include "dialog_input_new_category.h"
#include "ui_dialog_input_new_category.h"
#include <QLineEdit>
#include "Common_parameters.h"

Dialog_Input_New_Category::Dialog_Input_New_Category(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Category)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

Dialog_Input_New_Category::~Dialog_Input_New_Category()
{
    delete ui;
}

void Dialog_Input_New_Category::on_pushButton_OK_clicked()
{
    m_Category.id=0;
    m_Category.Name=ui->LineEdit_Name_Category->text();
    m_Category.Note=ui->LineEdit_Note->text();
    QDialog::accept();
}

void Dialog_Input_New_Category::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
