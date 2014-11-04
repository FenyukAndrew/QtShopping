#include "commondb.h"
#include "Common.h"

CommonDB::CommonDB() : dbase(QSqlDatabase::addDatabase("QSQLITE"))
{
    dbase.setDatabaseName(pathDB);
    if (!dbase.open())
    {
        qDebug() << "Error connect!";
        return;
    }

    //a_query=new QSqlQuery(dbase);
}

CommonDB::~CommonDB()
{
    //delete a_query;
}

QSqlQuery* CommonDB::get_new_query()
{
    return new QSqlQuery(dbase);
}
