#ifndef DIALOG_INPUT_NEW_CATEGORY_H
#define DIALOG_INPUT_NEW_CATEGORY_H

#include <QDialog>
#include <QDate>
#include "common_struct_data.h"

namespace Ui
{
class Dialog_Input_New_Category;
}

class Dialog_Input_New_Category : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Input_New_Category(QWidget *parent = 0);
    ~Dialog_Input_New_Category();

    Category& get_Category() {return m_Category;}

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_Input_New_Category *ui;

    Category m_Category;

};

#endif // DIALOG_INPUT_NEW_CATEGORY_H
