#ifndef DIALOGEDITITEM_H
#define DIALOGEDITITEM_H

#include <QDialog>

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
