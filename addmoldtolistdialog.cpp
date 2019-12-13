#include "addmoldtolistdialog.h"
#include "ui_addmoldtolistdialog.h"
#include <QMessageBox>

addMoldToListDialog::addMoldToListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addMoldToListDialog) {
    ui->setupUi(this);

    for(int a = 1; a <= 20; a++) {
        ui->comboBox->addItem(QString::number(a));
    }

    database.openDB();

    QSqlQuery query;
    
	query.exec("SELECT collection FROM item_price WHERE category='ПОГОНАЖ' GROUP BY collection HAVING COUNT(*)>0");

    while (query.next()) {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

addMoldToListDialog::~addMoldToListDialog() {
    database.closeDB();
    delete ui;
}

void addMoldToListDialog::on_pushButton_clicked() {
    reject();
}

void addMoldToListDialog::on_pushButton_2_clicked() {
    accept();
}

void addMoldToListDialog::on_comboBox_2_currentIndexChanged(const QString &arg1) {
    ui->comboBox_3->clear();

    QSqlQuery query;
    
	query.exec("SELECT type FROM item_price WHERE category='ПОГОНАЖ' AND collection='"+ui->comboBox_2->currentText()+"' GROUP BY type HAVING COUNT(*)>0");

    while (query.next()) {
        ui->comboBox_3->addItem(query.value(0).toString());
    }
}

void addMoldToListDialog::on_comboBox_3_currentIndexChanged(const QString &arg1) {
    ui->comboBox_4->clear();

    QSqlQuery query;
    
	query.exec("SELECT item FROM item_price WHERE category='ПОГОНАЖ' AND collection='"+ui->comboBox_2->currentText()+"' AND type='"+ui->comboBox_3->currentText()+"'");

    while (query.next()) {
        ui->comboBox_4->addItem(query.value(0).toString());
    }
}

QString addMoldToListDialog::getItem() const {
    return " " + ui->comboBox_2->currentText() + ", " + ui->comboBox_3->currentText() + ", " + ui->comboBox_4->currentText();
}

int addMoldToListDialog::getQuantity() const {
    return ui->comboBox->currentText().toInt();
}

int addMoldToListDialog::getPrice() const {
    int price;
    QSqlQuery query;

    query.exec("SELECT price FROM item_price WHERE category='ПОГОНАЖ' AND collection='"+ui->comboBox_2->currentText()+"' AND type='"+ui->comboBox_3->currentText()+"' AND item='"+ui->comboBox_4->currentText()+"'");

    while (query.next()) {
        price = query.value(0).toInt();
    }

    return price;
}