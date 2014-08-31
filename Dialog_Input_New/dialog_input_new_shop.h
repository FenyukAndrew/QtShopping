#ifndef DIALOG_INPUT_NEW_SHOP_H
#define DIALOG_INPUT_NEW_SHOP_H

#include <QDialog>
#include <QDate>
#include "common_struct_data.h"

namespace Ui
{
class Dialog_Input_New_Shop;
}

class Dialog_Input_New_Shop : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Input_New_Shop(QWidget *parent = 0);
    ~Dialog_Input_New_Shop();

    Shop& get_Shop() {return m_Shop;}

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_Input_New_Shop *ui;

    Shop m_Shop;

};

#endif // DIALOG_INPUT_NEW_SHOP_H
