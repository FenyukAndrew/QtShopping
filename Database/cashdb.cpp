#include "cashdb.h"
#include "Singleton.h"

CashDB::CashDB()
{
    mQSqlQuery=Singleton_M::Intance().get_new_query();
}

CashDB::~CashDB()
{
    delete mQSqlQuery;
}

void CashDB::init_cash(double sum)
{
//Удаление всех записей и внесение одной записи
   if (!mQSqlQuery->exec("DELETE FROM t_Cash"))
   {
       qDebug() << "Error delete from Cash";
   }
   add_payment(sum);
}

void CashDB::add_payment(double sum_payment)
{
    mQSqlQuery->prepare("INSERT INTO t_Cash (DateTime,sum1)"
                     " VALUES (datetime('now','localtime'),:sum_payment)");
    mQSqlQuery->bindValue(":sum_payment", sum_payment);

    if (!mQSqlQuery->exec())
    {
        qDebug() << "Error insert Cash";
    }
}

double CashDB::get_current_cash()
{
    if (!mQSqlQuery->exec("SELECT sum(sum1) total_sum FROM t_Cash"))
    {
        qDebug() << "Error select Currect Cash";
        return -999999;
    }
    rec = mQSqlQuery->record();

    if (mQSqlQuery->next())
    {
        return mQSqlQuery->value(rec.indexOf("total_sum")).toDouble();
    }
    return -999999;
}
