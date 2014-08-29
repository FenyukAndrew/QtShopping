#ifndef DIALOGITEMS_H
#define DIALOGITEMS_H

#include <QDialog>

namespace Ui {
class DialogItems;
}

class DialogItems : public QDialog
{
    Q_OBJECT

public:
    explicit DialogItems(QWidget *parent = 0);
    ~DialogItems();

private:
    Ui::DialogItems *ui;
};

#endif // DIALOGITEMS_H
