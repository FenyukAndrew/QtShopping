#ifndef COMMON_STRUCT_DATA_H
#define COMMON_STRUCT_DATA_H

#include "QString"

struct Shop
{
    int id;
    QString Name;
    QString Place;
    QString Note;
    double sum;//Сумма цен всех товаров в данном магазине умноженное на количество

    Shop()
    {
        id=0;
        sum=0.0;
    }
};

struct Category
{
    int id;
    QString Name;
    QString Note;
    double sum;//Сумма цен всех товаров в данной категории умноженное на количество

    Category()
    {
        id=0;
        sum=0.0;
    }
};

struct Item
{
    int id;
    int id_shop;
    int id_category;
    QString Name;
    float current_Price;
    float amount;
    short priority;

    Item()
    {
        id=-1;//Новое значение
        id_shop=0;
        id_category=0;
        current_Price=0.0;
        amount=0.0;
        priority=0;
    }

};

enum e_new_edit_element {e_new,e_edit};

//Выбор продуктов или покупка
enum e_select_buy {e_select,e_buy};

#endif // COMMON_STRUCT_DATA_H
