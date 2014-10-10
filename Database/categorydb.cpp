#include "categorydb.h"
#include "Singleton.h"

CategoryDB::CategoryDB(int m_id_shop,e_select_buy v_select_buy) : isActivatedSelect(false),
    id_shop(m_id_shop),
    m_select_buy(v_select_buy)
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
        //Получение категорий, где есть заказы
        QString select_for_data;
        if (m_select_buy==e_select)
        {
            select_for_data="SELECT * FROM t_Category where id_Shop=:id_Shop order by Name";
        }
        else
        {
            select_for_data="SELECT * FROM t_Category where id_Shop=:id_Shop and id in (SELECT DISTINCT id_category FROM t_List_Items where Amount>0) order by Name";
        };

        mQSqlQuery->prepare(select_for_data);
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
