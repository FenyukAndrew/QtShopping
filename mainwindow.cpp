#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogshops.h"
#include "Common_parameters.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonOrder_clicked()
{
    DialogShops mDialogShops;
    mDialogShops.exec();
}

void MainWindow::on_pushButtonCash_clicked()
{

}

void MainWindow::on_pushButtonBuy_clicked()
{

}
