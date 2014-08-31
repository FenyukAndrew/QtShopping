#include "itemdb.h"
#include "Singleton.h"

ItemDB::ItemDB(int m_id_Shop,int m_id_Category) : id_Shop(m_id_Shop),id_Category(m_id_Category)
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
    mQSqlQuery->prepare("UPDATE t_List_Items (Name,Current_Price,Amount,Priority)"
                     " VALUES (:Name,:Current_Price,:Amount,:Priority)"
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
        m_Item.amount=mQSqlQuery->value(rec.indexOf("Amount")).toInt();
        m_Item.priority=mQSqlQuery->value(rec.indexOf("Priority")).toInt();

        return true;
    }
    return false;
}

bool ItemDB::getNextItem(Item& m_Item)
{
    if (!isActivatedSelect)
    {
        mQSqlQuery->prepare("SELECT * FROM t_List_Items where id_shop=:id_shop and id_category=:id_category order by Priority,Name");
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
        m_Item.amount=mQSqlQuery->value(rec.indexOf("Amount")).toInt();

        return true;
    }
    isActivatedSelect=false;
    return false;
}
