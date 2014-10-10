#ifndef DIALOG_INPUT_NEW_ITEM_H
#define DIALOG_INPUT_NEW_ITEM_H

#include <QDialog>
#include <QDate>
#include "common_struct_data.h"

namespace Ui
{
    class Dialog_Input_New_Item;
}

class Dialog_Input_New_Item : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Input_New_Item(Item& v_Item,e_new_edit_element type_new_edit,QWidget *parent = 0);
    ~Dialog_Input_New_Item();

    //Item& get_Item() {return m_Item;}

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_Input_New_Item *ui;

    Item& m_Item;

};

#endif // DIALOG_INPUT_NEW_ITEM_H
