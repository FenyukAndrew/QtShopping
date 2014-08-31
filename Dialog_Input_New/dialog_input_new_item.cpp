#include "dialog_input_new_item.h"
#include "ui_dialog_input_new_item.h"
#include <QLineEdit>
#include "Common_parameters.h"
#include <limits>
#include "Singleton.h"

Dialog_Input_New_Item::Dialog_Input_New_Item(Item& v_Item,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Item),
    m_Item(v_Item)
{
    ui->setupUi(this);

    ui->LineEdit_Name->setText(m_Item.Name);

    ui->LineEdit_Current_Price->setText(Singleton_M::Intance().locale().toString(m_Item.current_Price,'f',2));
    ui->LineEdit_Current_Price->setValidator( new QDoubleValidator(0, std::numeric_limits<float>::max(), 2, this) );

    ui->LineEdit_Amount->setText(Singleton_M::Intance().locale().toString(m_Item.amount));
    ui->LineEdit_Amount->setValidator( new QIntValidator(0, std::numeric_limits<int>::max(), this) );

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

Dialog_Input_New_Item::~Dialog_Input_New_Item()
{
    delete ui;
}

void Dialog_Input_New_Item::on_pushButton_OK_clicked()
{
    m_Item.Name=ui->LineEdit_Name->text();
    m_Item.current_Price=Singleton_M::Intance().locale().toDouble(ui->LineEdit_Current_Price->text());
    m_Item.amount=Singleton_M::Intance().locale().toInt(ui->LineEdit_Amount->text());
    m_Item.priority+=1;//Увеличение приоритета - Поднимание в списке товаров
    QDialog::accept();
}

void Dialog_Input_New_Item::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
