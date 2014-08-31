#ifndef DIALOGITEMS_H
#define DIALOGITEMS_H

#include <QDialog>
#include <QSignalMapper>
#include "Database/itemdb.h"

namespace Ui {
class DialogItems;
}

class DialogItems : public QDialog
{
    Q_OBJECT

public:
    explicit DialogItems(int m_id_Shop,int m_id_Category,QWidget *parent = 0);
    ~DialogItems();

private slots:
    void on_pushButton_SelectItem_clicked(const int &);

    void on_pushButton_AddItem_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::DialogItems *ui;

    QSignalMapper *signalMapper;

    ItemDB mItemDB;

    void fill_list_items();
    void clear_list_items();

    //int id_Shop;
    //int id_Category;
};

#endif // DIALOGITEMS_H
