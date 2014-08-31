#ifndef DIALOGEDITITEM_H
#define DIALOGEDITITEM_H

#include <QDialog>

//НЕ ИСПОЛЬЗУЕТСЯ - добавление и редактирование осуществляется в Dialog_Input_New_Item

namespace Ui {
class DialogEditItem;
}

class DialogEditItem : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEditItem(QWidget *parent = 0);
    ~DialogEditItem();

private:
    Ui::DialogEditItem *ui;
};

#endif // DIALOGEDITITEM_H
