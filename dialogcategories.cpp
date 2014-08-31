#include "dialogcategories.h"
#include "ui_dialogcategories.h"
#include "Common_parameters.h"
#include "Singleton.h"
#include "common_struct_data.h"
#include "Dialog_Input_New/dialog_input_new_category.h"
#include "dialogcategories.h"
#include "dialogitems.h"

DialogCategories::DialogCategories(int m_id_shop,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCategories),
   id_shop(m_id_shop),
   mCategoryDB(m_id_shop)
{
    ui->setupUi(this);

    signalMapper=new QSignalMapper(this);

    fill_list_categories();

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogCategories::~DialogCategories()
{
    delete ui;
}

void DialogCategories::fill_list_categories()
{
    Category m_Category;
    while (mCategoryDB.getNextCategory(m_Category))
    {
        QPushButton *button1 = new QPushButton();
        button1->setText(m_Category.Name);

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
    DialogItems m_DialogItems(id_shop,v1);//Передача выбранного магазина и категории
    m_DialogItems.exec();
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
