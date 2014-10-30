#include "historydb.h"
#include "Singleton.h"

HistoryDB::HistoryDB()
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

HistoryDB::~HistoryDB()
{
    delete mQSqlQuery;
}

void HistoryDB::add_items_shop_history(const int _id_shop)
{
    mQSqlQuery->prepare("insert into t_History_purchases (DateTime, id_item, Price, Amount)"
    " select datetime('now','localtime'), id, Current_Price,Amount from t_List_Items where Amount>0 and id_shop=:id_shop");
    mQSqlQuery->bindValue(":id_shop", _id_shop);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error HistoryDB::add_items_shop_history";
    }

}

void HistoryDB::null_amount_items(const int _id_shop)
{
    mQSqlQuery->prepare("UPDATE t_List_Items SET Amount=0 WHERE id_shop=:_id_shop");
    mQSqlQuery->bindValue(":_id_shop", _id_shop);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error HistoryDB::null_amount_items";
    }

}
