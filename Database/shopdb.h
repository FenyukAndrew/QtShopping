#ifndef SHOPDB_H
#define SHOPDB_H

#include "commondb.h"
#include "common_struct_data.h"

class ShopDB
{
public:
    ShopDB(e_select_buy v_select_buy);
    ~ShopDB();

    void addShop(const Shop& m_Shop);

    bool getNextShop(Shop& m_Shop);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
    bool isActivatedSelect;
    const e_select_buy m_select_buy;
};

#endif // SHOPDB_H
