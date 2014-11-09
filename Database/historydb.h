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
    void get_history_items();

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
};

#endif // HISTORYDB_H
