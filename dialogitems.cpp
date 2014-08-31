#include "dialogitems.h"
#include "ui_dialogitems.h"
#include "Common_parameters.h"
#include "Singleton.h"
#include "common_struct_data.h"
#include "Dialog_Input_New/dialog_input_new_item.h"
#include "dialogitems.h"

DialogItems::DialogItems(int m_id_Shop,int m_id_Category,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogItems),
    mItemDB(m_id_Shop,m_id_Category)
    //id_Shop(m_id_Shop),
    //id_Category(m_id_Category)
{
    ui->setupUi(this);

    signalMapper=new QSignalMapper(this);

    fill_list_items();

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
        button1->setText(m_Item.Name);

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

        Dialog_Input_New_Item m_Dialog_Input_New_Item(m_Item);
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
    Dialog_Input_New_Item m_Dialog_Input_New_Item(m_Item);
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
