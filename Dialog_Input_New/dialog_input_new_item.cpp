#include "dialog_input_new_item.h"
#include "ui_dialog_input_new_item.h"
#include <QLineEdit>
#include "Common_parameters.h"
#include <limits>
#include "Singleton.h"

Dialog_Input_New_Item::Dialog_Input_New_Item(Item& v_Item,e_new_edit_element type_new_edit,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Item),
    m_Item(v_Item)
{
    ui->setupUi(this);

    if (type_new_edit==e_new)
    {
        ui->label_type_new_edit->setText("Новый продукт");
    }
    else
    {
        ui->label_type_new_edit->setText("Редактирование");
    }

    ui->LineEdit_Name->setText(m_Item.Name);

    ui->LineEdit_Current_Price->setText(Singleton_M::Intance().locale().toString(m_Item.current_Price,'f',2));
    ui->LineEdit_Current_Price->setValidator( new QDoubleValidator(0, std::numeric_limits<float>::max(), 2, this) );

    ui->LineEdit_Amount->setText(Singleton_M::Intance().locale().toString(m_Item.amount,'g',4));
    //Нужно 4 - т.к. при 3 обрезается до 2 знаков после запятой
    //Т.к. здесь будет учитываться вес - нужен float
    //ui->LineEdit_Amount->setValidator( new QIntValidator(0, std::numeric_limits<int>::max(), this) );
    ui->LineEdit_Amount->setValidator( new QDoubleValidator(0, std::numeric_limits<float>::max(), 3, this) );

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
    //m_Item.amount=Singleton_M::Intance().locale().toInt(ui->LineEdit_Amount->text());
    m_Item.amount=Singleton_M::Intance().locale().toDouble(ui->LineEdit_Amount->text());
    m_Item.priority+=1;//Увеличение приоритета - Поднимание в списке товаров
    QDialog::accept();
}

void Dialog_Input_New_Item::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}

void Dialog_Input_New_Item::on_LineEdit_Current_Price_textChanged(const QString &arg1)
{
    calculate();
}

void Dialog_Input_New_Item::on_LineEdit_Amount_textChanged(const QString &arg1)
{
    calculate();
}

void Dialog_Input_New_Item::calculate()
{
    bool ok,ok_amount;
    double current_Price=Singleton_M::Intance().locale().toDouble(ui->LineEdit_Current_Price->text(),&ok);
    double amount=Singleton_M::Intance().locale().toDouble(ui->LineEdit_Amount->text(),&ok_amount);
    if (ok&&ok_amount)
    {
        ui->Value_Total->setText(Singleton_M::Intance().locale().toString(current_Price*amount,'f',2));
    }
    else
    {
        ui->Value_Total->setText("--.--");
    }
}

