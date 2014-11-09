#ifndef DIALOGHISTORYITEMS_H
#define DIALOGHISTORYITEMS_H

#include <QDialog>

namespace Ui {
class DialogHistoryItems;
}

class DialogHistoryItems : public QDialog
{
    Q_OBJECT

public:
    explicit DialogHistoryItems(QWidget *parent = 0);
    ~DialogHistoryItems();

private:
    Ui::DialogHistoryItems *ui;
};

#endif // DIALOGHISTORYITEMS_H
