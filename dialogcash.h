#ifndef DIALOGCASH_H
#define DIALOGCASH_H

#include <QDialog>
#include "Database/cashdb.h"

namespace Ui {
class DialogCash;
}

class DialogCash : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCash(QWidget *parent = 0);
    ~DialogCash();

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::DialogCash *ui;

    CashDB m_CashDB;
};

#endif // DIALOGCASH_H
