#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "additemtolistdialog.h"
#include "addmoldtolistdialog.h"
#include "pricedialog.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addToTable(QString item, int quantity, int price);


private slots:
    void on_pushButton_2_clicked();
    void updateSumText();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    enum NAME_COLUMN {
        ITEM, QUANTITY, PRICE, SUM
    };
    int doar_sum;   
    QLabel sum_label;
};

#endif // MAINWINDOW_H
