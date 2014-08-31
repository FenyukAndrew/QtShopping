#ifndef DIALOGSHOPS_H
#define DIALOGSHOPS_H

#include <QDialog>
#include <QSignalMapper>
#include "Database/shopdb.h"

namespace Ui {
class DialogShops;
}

class DialogShops : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShops(QWidget *parent = 0);
    ~DialogShops();

private slots:
    void on_pushButton_SelectShop_clicked(const int &);

    void on_pushButton_AddShop_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::DialogShops *ui;

    QSignalMapper *signalMapper;

    ShopDB mShopDB;

    void fill_list_shops();
    void clear_list_shops();

};

#endif // DIALOGSHOPS_H
