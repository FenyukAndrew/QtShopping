#include "dialogcategories.h"
#include "ui_dialogcategories.h"
#include "Common_parameters.h"
#include "Singleton.h"
#include "common_struct_data.h"
#include "Dialog_Input_New/dialog_input_new_category.h"
#include "dialogcategories.h"
#include "dialogitems.h"
#include "dialogpaymentcashbox.h"

DialogCategories::DialogCategories(int m_id_shop,e_select_buy v_select_buy,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCategories),
   mCategoryDB(m_id_shop,v_select_buy),
   m_select_buy(v_select_buy),
   id_shop(m_id_shop)
{
    ui->setupUi(this);

    signalMapper=new QSignalMapper(this);

    fill_list_categories();

    //Кнопка имеет двойное назначение, в зависимости от выбор или покупка
    if (m_select_buy==e_select)
    {
        //AddCategory
        ui->pushButton_Custom->setText("Добавить категорию");
        connect(ui->pushButton_Custom, SIGNAL(clicked()), this, SLOT(on_pushButton_AddCategory_clicked()));
    }
    else
    {
        ui->pushButton_Custom->setText("Оплата на кассе");
        connect(ui->pushButton_Custom, SIGNAL(clicked()), this, SLOT(on_pushButton_Payment_at_checkout()));
    }

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogCategories::~DialogCategories()
{
    delete ui;
}

void DialogCategories::fill_list_categories()
{
    total_sum_shop=0;
    Category m_Category;
    while (mCategoryDB.getNextCategory(m_Category))
    {
        QPushButton *button1 = new QPushButton();
        QString str_sum="";
        if (m_Category.sum>=0.01)
        {
            str_sum="="+Singleton_M::Intance().locale().toString(m_Category.sum,'f',2);
        }
        button1->setText(m_Category.Name+str_sum);

        total_sum_shop+=m_Category.sum;

        connect(button1, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(button1, m_Category.id);

        ui->verticalLayoutScroll->addWidget(button1);
    }
    connect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectCategory_clicked(const int &)));
}

void DialogCategories::clear_list_categories()
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

    disconnect(signalMapper, SIGNAL(mapped(const int &)), this, SLOT(on_pushButton_SelectCategory_clicked(const int &)));
}

void DialogCategories::on_pushButton_SelectCategory_clicked(const int& v1)
{
    //qDebug() << v1;
    DialogItems m_DialogItems(id_shop,v1,m_select_buy);//Передача выбранного магазина и категории
    m_DialogItems.exec();

    //Иначе после изменения цены или количества не изменяется сумма отображаемая напротив категории
    clear_list_categories();
    fill_list_categories();
}

void DialogCategories::on_pushButton_Payment_at_checkout()
{
    DialogPaymentCashbox m_DialogPaymentCashbox(id_shop,total_sum_shop);
    int retCode = m_DialogPaymentCashbox.exec();
    if (retCode==QDialog::Accepted)
    {//Оплата произведена больше покупок в этом мазине нет
        //clear_list_categories();
        //fill_list_categories();
        QDialog::reject();
    }
}

void DialogCategories::on_pushButton_AddCategory_clicked()
{
    Dialog_Input_New_Category m_Dialog_Input_New_Category;
    int retCode = m_Dialog_Input_New_Category.exec();
    if (retCode==QDialog::Accepted)
    {
        Category m_Category=m_Dialog_Input_New_Category.get_Category();
        mCategoryDB.addCategory(m_Category);

        clear_list_categories();
        fill_list_categories();
    }
}

void DialogCategories::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
