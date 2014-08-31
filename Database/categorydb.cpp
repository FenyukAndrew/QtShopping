#include "categorydb.h"
#include "Singleton.h"

CategoryDB::CategoryDB(int m_id_shop) : id_shop(m_id_shop)
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

CategoryDB::~CategoryDB()
{
    delete mQSqlQuery;
}

void CategoryDB::addCategory(const Category& m_Category)
{
    mQSqlQuery->prepare("INSERT INTO t_Category (id_Shop,Name,Note)"
                     " VALUES (:id_Shop,:Name,:Note)");
    mQSqlQuery->bindValue(":id_Shop", id_shop);
    mQSqlQuery->bindValue(":Name", m_Category.Name);
    mQSqlQuery->bindValue(":Note", m_Category.Note);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error insert Category";
    }
}

bool CategoryDB::getNextCategory(Category& m_Category)
{
    if (!isActivatedSelect)
    {
        mQSqlQuery->prepare("SELECT * FROM t_Category where id_Shop=:id_Shop order by Name");
        mQSqlQuery->bindValue(":id_Shop", id_shop);
        if (!mQSqlQuery->exec())
        {
            qDebug() << "Error select Category";
            return false;
        }
        rec = mQSqlQuery->record();
        isActivatedSelect=true;
    }

    if (mQSqlQuery->next())
    {
        m_Category.id=mQSqlQuery->value(rec.indexOf("id")).toInt();
        m_Category.Name=mQSqlQuery->value(rec.indexOf("Name")).toString();
        m_Category.Note=mQSqlQuery->value(rec.indexOf("Note")).toString();

        return true;
    }
    isActivatedSelect=false;
    return false;
}
