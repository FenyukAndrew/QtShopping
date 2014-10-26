#include "dialogitems.h"
#include "ui_dialogitems.h"
#include "Common_parameters.h"
#include "Singleton.h"
#include "common_struct_data.h"
#include "Dialog_Input_New/dialog_input_new_item.h"
#include "dialogitems.h"

DialogItems::DialogItems(int m_id_Shop, int m_id_Category, e_select_buy v_select_buy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogItems),
    mItemDB(m_id_Shop,m_id_Category,v_select_buy)
    //id_Shop(m_id_Shop),
    //id_Category(m_id_Category)
{
    ui->setupUi(this);

    signalMapper=new QSignalMapper(this);

    fill_list_items();

    //Сделать возможным добавление товара во время покупки
    //Но не категорию - т.к. она будет пуста и не будет доступна
    /*if (v_select_buy!=e_select)
    {
        ui->pushButton_AddItem->setEnabled(0);
    }*/

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogItems::~DialogItems()
{
    delete ui;
}

void DialogItems::fill_list_items()
{
    Item m_Item;
    while (mItemDB.getNextItem(m_Item))
    {
        QPushButton *button1 = new QPushButton();
        double sum=m_Item.current_Price*m_Item.amount;
        QString str_sum="";
        if (sum>=0.01)
        {
            str_sum="="+Singleton_M::Intance().locale().toString(sum,'f',2);
        }
        button1->setText(m_Item.Name+str_sum);

        connect(button1, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(button1, m_Item.id);

        ui->verticalLayoutScroll->addWidget(button1);
    }
    connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectItem_clicked(const int &)));
}

void DialogItems::clear_list_items()
{
    //В случае QVBoxLayout родительским объектом будет на уровень выше - scrollArea, а не verticalLayoutScroll
    QList<QPushButton*> bList = ui->scrollArea->findChildren<QPushButton*>();

    foreach(QPushButton *x, bList)
    {
        qDebug() << x->objectName() ;
        disconnect(x, SIGNAL(clicked()), signalMapper, SLOT(map()));
        ui->verticalLayoutScroll->removeWidget(x);
        delete x;
    }

    disconnect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectItem_clicked(const int &)));
}

void DialogItems::on_pushButton_SelectItem_clicked(const int& id_Item)
{
    //qDebug() << v1;
    Item m_Item;
    if (mItemDB.selectItemById(id_Item,m_Item))
    {
        //Редактирование объекта

        Dialog_Input_New_Item m_Dialog_Input_New_Item(m_Item,e_edit);
        int retCode = m_Dialog_Input_New_Item.exec();
        if (retCode==QDialog::Accepted)
        {
            mItemDB.updateItem(m_Item);

            clear_list_items();
            fill_list_items();
        }
    }
}

void DialogItems::on_pushButton_AddItem_clicked()
{
    Item m_Item;
    Dialog_Input_New_Item m_Dialog_Input_New_Item(m_Item,e_new);
    int retCode = m_Dialog_Input_New_Item.exec();
    if (retCode==QDialog::Accepted)
    {
        mItemDB.addItem(m_Item);

        clear_list_items();
        fill_list_items();
    }
}

void DialogItems::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
