#include "shopdb.h"
#include "Singleton.h"

ShopDB::ShopDB(e_select_buy v_select_buy) : isActivatedSelect(false), m_select_buy(v_select_buy)
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
        //Получение магазинов, где есть заказы
        QString select_for_data;
        if (m_select_buy==e_select)
        {
            //select_for_data="SELECT * FROM t_Shop_list order by Name";
            select_for_data="select t_s.*,t_sum.sum from"
                 " (select id_shop,sum(Current_Price*Amount) sum from t_List_Items"
                 " group by id_shop) t_sum"
                 " join t_Shop_list t_s on t_s.id=t_sum.id_shop order by Name";
        }
        else
        {
            //select_for_data="SELECT * FROM t_Shop_list where id in (SELECT DISTINCT id_shop FROM t_List_Items where Amount>0) order by Name";
            select_for_data="select t_s.*,t_sum.sum from"
                 " (select id_shop,sum(Current_Price*Amount) sum from t_List_Items where Amount>0"
                 " group by id_shop having sum>0) t_sum"
                 " join t_Shop_list t_s on t_s.id=t_sum.id_shop order by Name";
        };

        if (!mQSqlQuery->exec(select_for_data))
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
        m_Shop.sum=mQSqlQuery->value(rec.indexOf("sum")).toDouble();

        return true;
    }
    isActivatedSelect=false;
    return false;
}
