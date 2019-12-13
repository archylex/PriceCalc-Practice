#include "addtopricedialog.h"
#include "ui_addtopricedialog.h"

addToPriceDialog::addToPriceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addToPriceDialog) {
    ui->setupUi(this);
}

addToPriceDialog::~addToPriceDialog() {
    delete ui;
}

QString addToPriceDialog::getCollection() const {
    return ui->lineEdit->text();
}


QString addToPriceDialog::getModel() const {
    return ui->lineEdit_2->text();
}

QString addToPriceDialog::getType() const {
    return ui->lineEdit_3->text();
}

QString addToPriceDialog::getPattern() const {
    return ui->lineEdit_4->text();
}

int addToPriceDialog::getPrice() const {
    return ui->lineEdit_5->text().toInt();
}

void addToPriceDialog::on_pushButton_2_clicked() {
    accept();
}

void addToPriceDialog::on_pushButton_clicked() {
    reject();
}

void addToPriceDialog::setFieldTitleD(QString text) {
    ui->label_4->setText(text);
}

void addToPriceDialog::setFieldTitleA(QString text) {
    ui->label->setText(text);
}

void addToPriceDialog::hideFieldB() {
    ui->label_2->hide();
    ui->lineEdit_2->hide();
    ui->label->setGeometry(10, 10, 161, 20);
    ui->lineEdit->setGeometry(10, 40, 161, 20);
}

void addToPriceDialog::showFieldB() {
    ui->label_2->show();
    ui->lineEdit_2->show();
    ui->label->setGeometry(10, 10, 91, 20);
    ui->lineEdit->setGeometry(10, 40, 91, 20);
}