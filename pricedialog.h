#ifndef PRICEDIALOG_H
#define PRICEDIALOG_H

#include <QDialog>
#include <addtopricedialog.h>
#include "sqldb.h"

namespace Ui {
class PriceDialog;
}

class PriceDialog : public QDialog {
    Q_OBJECT

public:
    explicit PriceDialog(QWidget *parent = 0);
    ~PriceDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::PriceDialog *ui;
    addToPriceDialog apd;
    SQLdb database;
};

#endif // PRICEDIALOG_H
