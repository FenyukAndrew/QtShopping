#ifndef CATEGORYDB_H
#define CATEGORY_H

#include "commondb.h"
#include "common_struct_data.h"

class CategoryDB
{
public:
    CategoryDB(int m_id_shop,e_select_buy v_select_buy);
    ~CategoryDB();

    void addCategory(const Category& m_Category);

    bool getNextCategory(Category& m_Category);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
    bool isActivatedSelect;

    const int id_shop;
    const e_select_buy m_select_buy;
};

#endif // CATEGORYDB_H
