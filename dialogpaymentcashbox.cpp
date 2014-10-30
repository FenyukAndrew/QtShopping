#include "dialogpaymentcashbox.h"
#include "ui_dialogpaymentcashbox.h"
#include "Singleton.h"
#include "Common_parameters.h"
#include "Database/historydb.h"

DialogPaymentCashbox::DialogPaymentCashbox(const int _id_shop,const double _payment,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPaymentCashbox),
    id_shop(_id_shop),
    m_payment(_payment)
{
    ui->setupUi(this);

    double sum_cash=m_CashDB.get_current_cash();

    ui->LineEdit_Cash->setText(Singleton_M::Intance().locale().toString(sum_cash,'f',2));
    ui->LineEdit_Payment->setText(Singleton_M::Intance().locale().toString(m_payment,'f',2));
    ui->LineEdit_Sum_After->setText(Singleton_M::Intance().locale().toString(sum_cash-m_payment,'f',2));

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogPaymentCashbox::~DialogPaymentCashbox()
{
    delete ui;
}

void DialogPaymentCashbox::on_pushButton_OK_clicked()
{
    m_CashDB.add_payment(-m_payment);//Т.к. это трата наличных

    HistoryDB m_HistoryDB;
    m_HistoryDB.add_items_shop_history(id_shop);//Все покупки с этого магазина перенести в историю
    m_HistoryDB.null_amount_items(id_shop);//У всех заказов из этого магазина сделать Amount=0

    QDialog::accept();
}

void DialogPaymentCashbox::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
