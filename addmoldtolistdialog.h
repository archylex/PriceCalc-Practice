#ifndef ADDMOLDTOLISTDIALOG_H
#define ADDMOLDTOLISTDIALOG_H

#include <QDialog>
#include "sqldb.h"

namespace Ui {
class addMoldToListDialog;
}

class addMoldToListDialog : public QDialog {
    Q_OBJECT

public:
    explicit addMoldToListDialog(QWidget *parent = 0);
    ~addMoldToListDialog();
    QString getItem() const;
    int getQuantity() const;
    int getPrice() const;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_2_currentIndexChanged(const QString &arg1);
    void on_comboBox_3_currentIndexChanged(const QString &arg1);

private:
    Ui::addMoldToListDialog *ui;
    SQLdb database;
};

#endif // ADDMOLDTOLISTDIALOG_H
