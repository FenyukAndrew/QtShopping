#include "dialogcash.h"
#include "ui_dialogcash.h"
#include "Singleton.h"
#include "Common_parameters.h"

DialogCash::DialogCash(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCash)
{
    ui->setupUi(this);

    double sum_cash=m_CashDB.get_current_cash();
    ui->text_Cash_Balance->setText(Singleton_M::Intance().locale().toString(sum_cash,'f',2));//Отображение остатка от преведущих операций

    ui->LineEdit_Cash->setText(Singleton_M::Intance().locale().toString(0.0,'f',2));
    ui->LineEdit_Cash->setValidator( new QDoubleValidator(0, std::numeric_limits<float>::max(), 2, this) );

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

DialogCash::~DialogCash()
{
    delete ui;
}

void DialogCash::on_pushButton_OK_clicked()
{
    bool ok;
    double sum_cash=Singleton_M::Intance().locale().toDouble(ui->LineEdit_Cash->text(),&ok);

    if (ok)
    {
        m_CashDB.init_cash(sum_cash);

        QDialog::accept();
    }
}

void DialogCash::on_pushButton_Cancel_clicked()
{
    QDialog::reject();
}
