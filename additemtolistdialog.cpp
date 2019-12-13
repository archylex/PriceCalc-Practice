#include "additemtolistdialog.h"
#include "ui_additemtolistdialog.h"
#include <QMessageBox>

addItemToListDialog::addItemToListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItemToListDialog) {
    ui->setupUi(this);

    setFixedHeight(new_height);
    setFixedWidth(751);

    ui->pushButton_3->setEnabled(true);

    for(int a = 1; a <= 20; a++) {
        ui->count->addItem(QString::number(a));
    }

    database.openDB();

    QSqlQuery query;
    
	query.exec("SELECT collection FROM item_price WHERE category='ДВЕРЬ' GROUP BY collection HAVING COUNT(*)>0");

    while (query.next())    {
        ui->collection->addItem(query.value(0).toString());
    }
}

addItemToListDialog::~addItemToListDialog() {
    database.closeDB();
    delete ui;
}

void addItemToListDialog::on_pushButton_clicked() {
    accept();
}

QString addItemToListDialog::getItem() const {
    QString txt;

    txt = " Дверь (" + ui->collection->currentText() + ", " + ui->model->currentText() + ", " + ui->type->currentText() + ", " + ui->pattern->currentText() + ")";

    for(int i = 0; i < ui->verticalLayout->count(); i++) {
        if (i == 0) txt += "; опции: ";
        QDynamicComboBox *combobox = qobject_cast<QDynamicComboBox*>(ui->verticalLayout->itemAt(i)->widget());
        QDynamicComboBox *cbItem = qobject_cast<QDynamicComboBox*>(ui->verticalLayout_2->itemAt(i)->widget());
        txt += " - " + combobox->currentText() + ": " + cbItem->currentText() + "; ";
    }

    return txt;
}

int addItemToListDialog::getQuantity() const {    
    return ui->count->currentText().toInt();
}

int addItemToListDialog::getPrice() const {
    int price;
    QSqlQuery query;

    query.exec("SELECT price FROM item_price WHERE category='ДВЕРЬ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' AND type='"+ui->type->currentText()+"' AND item='"+ui->pattern->currentText()+"'");

    while (query.next()) {
        price = query.value(0).toInt();
    }

    for(int i = 0; i < ui->verticalLayout->count(); i++) {
        QDynamicComboBox *cbOption = qobject_cast<QDynamicComboBox*>(ui->verticalLayout->itemAt(i)->widget());
        QDynamicComboBox *cbItem = qobject_cast<QDynamicComboBox*>(ui->verticalLayout_2->itemAt(i)->widget());

        query.exec("SELECT price FROM item_price WHERE category='ОПЦИЯ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' AND type='"+cbOption->currentText()+"' AND item='"+cbItem->currentText()+"'");

        while (query.next()) {
            price += query.value(0).toInt();
        }
    }

    return price;
}

void addItemToListDialog::on_collection_currentIndexChanged(const QString &arg1) {    
    deleteComboBox();

    ui->model->clear();

    QSqlQuery query;
    
	query.exec("SELECT model FROM item_price WHERE category='ДВЕРЬ' AND collection='"+ui->collection->currentText()+"' GROUP BY model HAVING COUNT(*)>0");

    while (query.next()) {
        ui->model->addItem(query.value(0).toString());
    }
}

void addItemToListDialog::on_model_currentIndexChanged(const QString &arg1) {
    deleteComboBox();

    ui->type->clear();

    QSqlQuery query;

    query.exec("SELECT type FROM item_price WHERE category='ДВЕРЬ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' GROUP BY type HAVING COUNT(*)>0");
	    
    while (query.next()) {
        ui->type->addItem(query.value(0).toString());
    }
}

void addItemToListDialog::on_type_currentIndexChanged(const QString &arg1) {
    deleteComboBox();

    ui->pattern->clear();

    QSqlQuery query;

    query.exec("SELECT item FROM item_price WHERE category='ДВЕРЬ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' AND type='"+ui->type->currentText()+"'");
	    
    while (query.next()) {
        ui->pattern->addItem(query.value(0).toString());
    }
}

void addItemToListDialog::on_pushButton_3_clicked() {
	QSqlQuery query;
    QDynamicComboBox *combobox = new QDynamicComboBox(this);

    combobox->setFixedWidth(181);
    
	ui->verticalLayout->addWidget(combobox);
    
    query.exec("SELECT type FROM item_price WHERE category='ОПЦИЯ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' GROUP BY type HAVING COUNT(*)>0");
    
	while (query.next()) {
        combobox->addItem(query.value(0).toString());
    }

    connect(combobox, SIGNAL(currentIndexChanged(QString)), this, SLOT(on_option_category_currentIndexChanged(QString)));

    QDynamicComboBox *combobox_child = new QDynamicComboBox(this);
    combobox_child->setFixedWidth(441);
    ui->verticalLayout_2->addWidget(combobox_child);
    
	query.exec("SELECT item FROM item_price WHERE category='ОПЦИЯ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' AND type='"+combobox->currentText()+"'");
    
	while (query.next()) {
        combobox_child->addItem(query.value(0).toString());
    }

    QDynamicButton *button_child = new QDynamicButton(this);
    button_child->setFixedWidth(71);
    button_child->setText("удалить");
    ui->verticalLayout_3->addWidget(button_child);

    connect(button_child, SIGNAL(clicked()), this, SLOT(deleteComboRow()));

    new_height += 30;
    setFixedHeight(new_height);

    ui->verticalLayout->setSizeConstraint(QLayout::SetFixedSize);
    ui->verticalLayout_2->setSizeConstraint(QLayout::SetFixedSize);
    ui->verticalLayout_3->setSizeConstraint(QLayout::SetFixedSize);

    ui->pushButton_2->setGeometry(250,new_height-43,120,23);
    ui->pushButton->setGeometry(390,new_height-43,120,23);
}

void addItemToListDialog::deleteComboBox() {
    for(int i = 0; i < ui->verticalLayout->count(); i++) {
        QDynamicComboBox *combobox = qobject_cast<QDynamicComboBox*>(ui->verticalLayout->itemAt(i)->widget());
        combobox->hide();
        delete combobox;
        --i;
    }

    for(int i = 0; i < ui->verticalLayout_2->count(); i++) {
        QDynamicComboBox *combobox = qobject_cast<QDynamicComboBox*>(ui->verticalLayout_2->itemAt(i)->widget());
        combobox->hide();
        delete combobox;
        --i;
    }

    for(int i = 0; i < ui->verticalLayout_3->count(); i++) {
        QDynamicButton *dbutton = qobject_cast<QDynamicButton*>(ui->verticalLayout_3->itemAt(i)->widget());
        dbutton->hide();
        delete dbutton;
        --i;
    }

    new_height = 133;
    
	setFixedHeight(new_height);

    ui->pushButton_2->setGeometry(250,new_height-43,120,23);
    
	ui->pushButton->setGeometry(390,new_height-43,120,23);

    ui->pushButton_3->setEnabled(false);
}

void addItemToListDialog::deleteComboRow() {
    QDynamicButton *button = (QDynamicButton*) sender();
    int i = ui->verticalLayout_3->indexOf(button);

    QDynamicComboBox *combobox = qobject_cast<QDynamicComboBox*>(ui->verticalLayout->itemAt(i)->widget());
    combobox->hide();
    delete combobox;

    QDynamicComboBox *combobox2 = qobject_cast<QDynamicComboBox*>(ui->verticalLayout_2->itemAt(i)->widget());
    combobox2->hide();
    delete combobox2;

    QDynamicButton *dbutton = qobject_cast<QDynamicButton*>(ui->verticalLayout_3->itemAt(i)->widget());
    dbutton->hide();
    delete dbutton;

    new_height -= 30;
    setFixedHeight(new_height);
    ui->pushButton_2->setGeometry(250,new_height-43,120,23);
    ui->pushButton->setGeometry(390,new_height-43,120,23);
}

void addItemToListDialog::on_pattern_currentIndexChanged(const QString &arg1) {
    deleteComboBox();

    QSqlQuery query;
    
	query.exec("SELECT type FROM item_price WHERE category='ОПЦИЯ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' GROUP BY type HAVING COUNT(*)>0");

    while (query.next()) {        
        ui->pushButton_3->setEnabled(true);
    }
}

void addItemToListDialog::on_pushButton_2_clicked() {
    reject();
}

void addItemToListDialog::on_option_category_currentIndexChanged(const QString &arg1) {
    QDynamicComboBox *combobox = (QDynamicComboBox*) sender();
    int i = ui->verticalLayout->indexOf(combobox);

    QDynamicComboBox *comboboxOptionItem = qobject_cast<QDynamicComboBox*>(ui->verticalLayout_2->itemAt(i)->widget());
    comboboxOptionItem->clear();

    QSqlQuery query;

    query.exec("SELECT item FROM item_price WHERE category='ОПЦИЯ' AND collection='"+ui->collection->currentText()+"' AND model='"+ui->model->currentText()+"' AND type='"+combobox->currentText()+"'");

    while (query.next()) {
        comboboxOptionItem->addItem(query.value(0).toString());
    }
}