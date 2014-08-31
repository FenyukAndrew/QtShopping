#ifndef SHOPDB_H
#define SHOPDB_H

#include "commondb.h"
#include "common_struct_data.h"

class ShopDB
{
public:
    ShopDB();
    ~ShopDB();

    void addShop(const Shop& m_Shop);

    bool getNextShop(Shop& m_Shop);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
    bool isActivatedSelect;
};

#endif // SHOPDB_H
