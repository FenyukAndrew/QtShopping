#ifndef HISTORYDB_H
#define HISTORYDB_H

#include "commondb.h"
#include "common_struct_data.h"

class HistoryDB
{
public:
    HistoryDB();
    ~HistoryDB();

    void add_items_shop_history(const int _id_shop);

    //Обнуление количества покупок у магазина
    void null_amount_items(const int _id_shop);

    //Получение истории покупок за текущий день
    bool getNextHistoryItem(HistoryItem &m_HistoryItem);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;

    bool isActivatedSelectHistoryItem;
};

#endif // HISTORYDB_H
