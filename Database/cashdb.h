#ifndef CASHDB_H
#define CASHDB_H

#include "commondb.h"
#include "common_struct_data.h"

class CashDB
{
public:
    CashDB();
    ~CashDB();

    void init_cash(double sum);
    void add_payment(double sum_payment);
    double get_current_cash();

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
};

#endif // CASHDB_H
