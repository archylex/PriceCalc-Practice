#ifndef ADDITEMTOLISTDIALOG_H
#define ADDITEMTOLISTDIALOG_H

#include <QDialog>
#include <qdynamicbutton.h>
#include <qdynamiccombobox.h>
#include "sqldb.h"

namespace Ui {
class addItemToListDialog;
}

class addItemToListDialog : public QDialog {
    Q_OBJECT

public:
    explicit addItemToListDialog(QWidget *parent = 0);
    ~addItemToListDialog();

    QString getItem() const;
    int getQuantity() const;
    int getPrice() const;


private slots:
    void on_collection_currentIndexChanged(const QString &arg1);
    void on_model_currentIndexChanged(const QString &arg1);
    void on_type_currentIndexChanged(const QString &arg1);
    void on_pattern_currentIndexChanged(const QString &arg1);
    void on_option_category_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void deleteComboBox();    
    void deleteComboRow();
	   

private:
    Ui::addItemToListDialog *ui;
    int new_height = 133;
    SQLdb database;

};

#endif // ADDITEMTOLISTDIALOG_H
