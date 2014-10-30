#ifndef DIALOGPAYMENTCASHBOX_H
#define DIALOGPAYMENTCASHBOX_H

#include <QDialog>
#include "Database/cashdb.h"

namespace Ui {
class DialogPaymentCashbox;
}

class DialogPaymentCashbox : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPaymentCashbox(const int _id_shop, const double _payment, QWidget *parent = 0);
    ~DialogPaymentCashbox();

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::DialogPaymentCashbox *ui;

    CashDB m_CashDB;
    const int id_shop;
    const double m_payment;
};

#endif // DIALOGPAYMENTCASHBOX_H
