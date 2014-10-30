#include "itemdb.h"
#include "Singleton.h"

ItemDB::ItemDB(int m_id_Shop,int m_id_Category,e_select_buy v_select_buy) : isActivatedSelect(false),
    id_Shop(m_id_Shop),
    id_Category(m_id_Category),
    m_select_buy(v_select_buy)
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

ItemDB::~ItemDB()
{
    delete mQSqlQuery;
}

void ItemDB::addItem(const Item& m_Item)
{
    mQSqlQuery->prepare("INSERT INTO t_List_Items (id_shop,id_category,Name,Current_Price,Amount,Priority)"
                     " VALUES (:id_shop,:id_category,:Name,:Current_Price,:Amount,:Priority)");
    mQSqlQuery->bindValue(":id_shop", id_Shop);//Т.к. новый объект, нужно заполнить правильным значением
    mQSqlQuery->bindValue(":id_category", id_Category);
    mQSqlQuery->bindValue(":Name", m_Item.Name);
    mQSqlQuery->bindValue(":Current_Price", m_Item.current_Price);
    mQSqlQuery->bindValue(":Amount", m_Item.amount);
    mQSqlQuery->bindValue(":Priority", 0);//Чем выше тем востребованней продукт

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error insert Item";
    }
}

void ItemDB::updateItem(const Item& m_Item)
{
    mQSqlQuery->prepare("UPDATE t_List_Items"
                     " SET Name=:Name,Current_Price=:Current_Price,Amount=:Amount,Priority=:Priority"
                     " WHERE id=:id");
    mQSqlQuery->bindValue(":id", m_Item.id);
    mQSqlQuery->bindValue(":Name", m_Item.Name);
    mQSqlQuery->bindValue(":Current_Price", m_Item.current_Price);
    mQSqlQuery->bindValue(":Amount", m_Item.amount);
    mQSqlQuery->bindValue(":Priority", m_Item.priority);//Чем выше тем востребованней продукт

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error update Item";
    }

}

void ItemDB::addPriceNewItemToHistory(const double price)
{
    mQSqlQuery->prepare("insert into t_History_price (id_Item,DateTime,Price)"
    " select max(id), datetime('now','localtime'), :price from t_List_Items");
    mQSqlQuery->bindValue(":price", price);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error addPriceNewItemToHistory";
    }

}

void ItemDB::addPriceItemToHistory(const int id_item,const double price)
{
    mQSqlQuery->prepare("insert into t_History_price (id_Item,DateTime,Price)"
    " values (:id_item, datetime('now','localtime'), :price)");
    mQSqlQuery->bindValue(":id_item", id_item);
    mQSqlQuery->bindValue(":price", price);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error addPriceItemToHistory";
    }

}

//Для редактирования выбранного объекта
bool ItemDB::selectItemById(int id_Item,Item& m_Item)
{
    mQSqlQuery->prepare("SELECT * FROM t_List_Items where id=:id_Item");
    mQSqlQuery->bindValue(":id_Item", id_Item);
    if (!mQSqlQuery->exec())
    {
       qDebug() << "Error select Item by ID";
       return false;
    }
    rec = mQSqlQuery->record();

    if (mQSqlQuery->next())
    {
        m_Item.id=mQSqlQuery->value(rec.indexOf("id")).toInt();
        m_Item.id_shop=mQSqlQuery->value(rec.indexOf("id_shop")).toInt();
        m_Item.id_category=mQSqlQuery->value(rec.indexOf("id_category")).toInt();
        m_Item.Name=mQSqlQuery->value(rec.indexOf("Name")).toString();
        m_Item.current_Price=mQSqlQuery->value(rec.indexOf("Current_Price")).toDouble();
        m_Item.amount=mQSqlQuery->value(rec.indexOf("Amount")).toDouble();
        m_Item.priority=mQSqlQuery->value(rec.indexOf("Priority")).toInt();

        return true;
    }
    return false;
}

bool ItemDB::getNextItem(Item& m_Item)
{
    if (!isActivatedSelect)
    {
        //Получение заказанных продуктов
        QString select_for_data;
        if (m_select_buy==e_select)
        {
            select_for_data="SELECT * FROM t_List_Items where id_shop=:id_shop and id_category=:id_category order by Priority DESC,Name";
        }
        else
        {
            select_for_data="SELECT * FROM t_List_Items where id_shop=:id_shop and id_category=:id_category and Amount>0 order by Priority DESC,Name";
        };

        mQSqlQuery->prepare(select_for_data);
        mQSqlQuery->bindValue(":id_shop", id_Shop);
        mQSqlQuery->bindValue(":id_category", id_Category);
        if (!mQSqlQuery->exec())
        {
            qDebug() << "Error select Item";
            return false;
        }
        rec = mQSqlQuery->record();
        isActivatedSelect=true;
    }

    if (mQSqlQuery->next())
    {
        m_Item.id=mQSqlQuery->value(rec.indexOf("id")).toInt();
        m_Item.Name=mQSqlQuery->value(rec.indexOf("Name")).toString();
        m_Item.current_Price=mQSqlQuery->value(rec.indexOf("Current_Price")).toDouble();
        m_Item.amount=mQSqlQuery->value(rec.indexOf("Amount")).toDouble();

        return true;
    }
    isActivatedSelect=false;
    return false;
}
