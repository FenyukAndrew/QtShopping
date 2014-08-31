#include "shopdb.h"
#include "Singleton.h"

ShopDB::ShopDB()
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

ShopDB::~ShopDB()
{
    delete mQSqlQuery;
}

void ShopDB::addShop(const Shop& m_Shop)
{
    mQSqlQuery->prepare("INSERT INTO t_Shop_list (Name,Note,Place)"
                     " VALUES (:Name,:Note,:Place)");
    mQSqlQuery->bindValue(":Name", m_Shop.Name);
    mQSqlQuery->bindValue(":Note", m_Shop.Note);
    mQSqlQuery->bindValue(":Place", m_Shop.Place);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error insert Shop";
    }
}

bool ShopDB::getNextShop(Shop& m_Shop)
{
    if (!isActivatedSelect)
    {
        if (!mQSqlQuery->exec("SELECT * FROM t_Shop_list order by Name"))
        {
            qDebug() << "Error select Shop";
            return false;
        }
        rec = mQSqlQuery->record();
        isActivatedSelect=true;
    }

    if (mQSqlQuery->next())
    {
        m_Shop.id=mQSqlQuery->value(rec.indexOf("id")).toInt();
        m_Shop.Name=mQSqlQuery->value(rec.indexOf("Name")).toString();
        m_Shop.Note=mQSqlQuery->value(rec.indexOf("Note")).toString();
        m_Shop.Place=mQSqlQuery->value(rec.indexOf("Place")).toString();

        return true;
    }
    isActivatedSelect=false;
    return false;
}
