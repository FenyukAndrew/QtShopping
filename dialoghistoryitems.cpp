#include "dialoghistoryitems.h"
#include "ui_dialoghistoryitems.h"
#include "Singleton.h"
#include "Common_parameters.h"
#include "Database/historydb.h"

DialogHistoryItems::DialogHistoryItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHistoryItems)
{
    ui->setupUi(this);

    fill_table_view();

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogHistoryItems::~DialogHistoryItems()
{
    delete ui;
}

void DialogHistoryItems::fill_table_view()
{
    HistoryDB m_HistoryDB;

    constexpr int HEADER_NAME=1;

    QStringList strlist;
    strlist << "Дата" << "Название" << "Количество" << "Цена" << "Сумма";
    ui->simple_table->setColumnCount( 5 );
    ui->simple_table->setHorizontalHeaderLabels( strlist );
    //ui->simple_table->setRowCount( 10 );
    ui->simple_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    //connect(simple_table, SIGNAL(itemSelectionChanged()),this,SLOT(selectionChanged()));
    QTableWidgetItem *item;
    HistoryItem m_HistoryItem;
    HistoryDB mHistoryDB;
    int i=0;
    while (mHistoryDB.getNextHistoryItem(m_HistoryItem))
    {
        ui->simple_table->setRowCount( i+1 );

        // Ограничиваем возможности первого столбца только отображением.

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText( Singleton_M::Intance().locale().toString(m_HistoryItem.mDateTime,"dd.MM.yyyy hh:mm"));
        ui->simple_table->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText( m_HistoryItem.Name);
        ui->simple_table->setItem(i,HEADER_NAME,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText( Singleton_M::Intance().locale().toString(m_HistoryItem.amount,'f',3));
        ui->simple_table->setItem(i,2,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText( Singleton_M::Intance().locale().toString(m_HistoryItem.price,'f',2));
        ui->simple_table->setItem(i,3,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        item->setText( Singleton_M::Intance().locale().toString(m_HistoryItem.amount*m_HistoryItem.price,'f',2));
        ui->simple_table->setItem(i,4,item);

        i++;
    }

    //Оптимизировать ширину колонок
    ui->simple_table->resizeColumnsToContents();
}

void DialogHistoryItems::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
