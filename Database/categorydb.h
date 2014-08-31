#ifndef CATEGORYDB_H
#define CATEGORY_H

#include "commondb.h"
#include "common_struct_data.h"

class CategoryDB
{
public:
    CategoryDB(int m_id_shop);
    ~CategoryDB();

    void addCategory(const Category& m_Category);

    bool getNextCategory(Category& m_Category);

private:
    QSqlQuery* mQSqlQuery;
    QSqlRecord rec;
    bool isActivatedSelect;

    const int id_shop;
};

#endif // CATEGORYDB_H
