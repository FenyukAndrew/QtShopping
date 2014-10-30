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
    void null_amount_items(const int _id_shop);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
};

#endif // HISTORYDB_H
