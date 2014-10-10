#include "dialogshops.h"
#include "ui_dialogshops.h"
#include "Singleton.h"
#include "common_struct_data.h"
#include "Dialog_Input_New/dialog_input_new_shop.h"
#include "Common_parameters.h"
#include "dialogcategories.h"

DialogShops::DialogShops(e_select_buy v_select_buy,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogShops),
    mShopDB(v_select_buy),
    m_select_buy(v_select_buy)
  {
    ui->setupUi(this);

    signalMapper=new QSignalMapper(this);

    fill_list_shops();

    if (m_select_buy!=e_select)
    {
        ui->pushButton_AddShop->setEnabled(0);
    }

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogShops::~DialogShops()
{
    delete ui;
    delete signalMapper;
}

void DialogShops::fill_list_shops()
{
    Shop m_Shop;
    while (mShopDB.getNextShop(m_Shop))
    {
        QPushButton *button1 = new QPushButton();
        button1->setText(m_Shop.Name);

        connect(button1, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(button1, m_Shop.id);

        ui->verticalLayoutScroll->addWidget(button1);
    }
    connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectShop_clicked(const int &)));
}

void DialogShops::clear_list_shops()
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

    disconnect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectShop_clicked(const int &)));
}

void DialogShops::on_pushButton_SelectShop_clicked(const int& v1)
{
    //qDebug() << v1;
    DialogCategories m_DialogCategories(v1,m_select_buy);//Передача выбранного магазина
    m_DialogCategories.exec();
}

void DialogShops::on_pushButton_AddShop_clicked()
{
    Dialog_Input_New_Shop m_Dialog_Input_New_Shop;
    int retCode = m_Dialog_Input_New_Shop.exec();
    if (retCode==QDialog::Accepted)
    {
        Shop m_Shop=m_Dialog_Input_New_Shop.get_Shop();
        mShopDB.addShop(m_Shop);

        clear_list_shops();
        fill_list_shops();
    }
}

void DialogShops::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
