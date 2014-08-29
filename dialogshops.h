#ifndef DIALOGSHOPS_H
#define DIALOGSHOPS_H

#include <QDialog>

namespace Ui {
class DialogShops;
}

class DialogShops : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShops(QWidget *parent = 0);
    ~DialogShops();

private:
    Ui::DialogShops *ui;
};

#endif // DIALOGSHOPS_H
