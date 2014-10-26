#ifndef DIALOGCATEGORIES_H
#define DIALOGCATEGORIES_H

#include <QDialog>
#include <QSignalMapper>
#include "Database/categorydb.h"

namespace Ui {
class DialogCategories;
}

class DialogCategories : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCategories(int m_id_shop,e_select_buy v_select_buy,QWidget *parent = 0);
    ~DialogCategories();

private slots:
    void on_pushButton_SelectCategory_clicked(const int &);

    void on_pushButton_AddCategory_clicked();

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Payment_at_checkout();

private:
    Ui::DialogCategories *ui;

    QSignalMapper *signalMapper;

    CategoryDB mCategoryDB;
    const e_select_buy m_select_buy;

    void fill_list_categories();
    void clear_list_categories();

    const int id_shop;

};

#endif // DIALOGCATEGORIES_H
