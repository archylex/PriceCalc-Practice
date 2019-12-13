#include "pricedialog.h"
#include "ui_pricedialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>



PriceDialog::PriceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceDialog) {
    ui->setupUi(this);

    QStringList column_title;

    ui->tableWidget->setColumnCount(7);
    column_title << "id" << "категория" << "коллекция" << "модель" << "тип" << "наименование" << "цена";
    ui->tableWidget->setHorizontalHeaderLabels(column_title);
    QHeaderView *verticalHeader = ui->tableWidget->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(16);
    QHeaderView *horizontalHeader = ui->tableWidget->horizontalHeader();
    horizontalHeader->setSectionResizeMode(0, QHeaderView::Fixed);
    horizontalHeader->setDefaultSectionSize(50);
    horizontalHeader->setSectionResizeMode(1, QHeaderView::Stretch);
    horizontalHeader->setSectionResizeMode(2, QHeaderView::Stretch);
    horizontalHeader->setSectionResizeMode(3, QHeaderView::Fixed);
    horizontalHeader->setSectionResizeMode(4, QHeaderView::Stretch);
    horizontalHeader->setSectionResizeMode(5, QHeaderView::Stretch);
    horizontalHeader->setSectionResizeMode(6, QHeaderView::Fixed);
    horizontalHeader->setDefaultSectionSize(50);

    ui->comboBox->addItem("ДВЕРЬ");
    ui->comboBox->addItem("ОПЦИЯ");
    ui->comboBox->addItem("ПОГОНАЖ");

    database.openDB();
    QSqlQuery query;
    if (!query.exec("SELECT * FROM item_price")) {
        qDebug() << query.lastError().text();
        query.exec("create table item_price "
                  "(id integer primary key AUTOINCREMENT NOT NULL, "
                  "category varchar(255) NOT NULL, "
                  "collection varchar(255), "
                  "model varchar(20), "
                  "type varchar(255), "
                  "item varchar(255) NOT NULL, "
                  "price integer NOT NULL)");
    } else {       
        while (query.next())
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            for (int ix=0; ix<7; ix++) {
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, ix, new QTableWidgetItem(query.value(ix).toString()));
            }
        }
    }
}

PriceDialog::~PriceDialog() {
    database.closeDB();
    delete ui;
}

void PriceDialog::on_pushButton_2_clicked() {
    apd.setModal(true);
    apd.setWindowTitle("ДОБАВИТЬ В ПРАЙС");
    apd.setWindowIcon(QIcon(":/calc.png"));
    apd.setFixedSize(apd.width(), apd.height());

    switch (ui->comboBox->currentIndex()) {
		case 0:
			apd.setFieldTitleA("коллекция");
			apd.setFieldTitleD("паттерн");
			apd.showFieldB();
			break;
		case 2:
			apd.setFieldTitleA("погонаж");
			apd.setFieldTitleD("паттерн");
			apd.hideFieldB();
			break;
		case 1:
			apd.setFieldTitleA("коллекция");
			apd.setFieldTitleD("опция");
			apd.showFieldB();
			break;
		default:
			break;
    }

    int result = apd.exec();
    
	if (result == QDialog::Accepted) {
        QSqlQuery query;
    
		query.prepare("INSERT INTO item_price(category,collection,model,type,item,price)"
                         "VALUES(:category,:collection,:model,:type,:item,:price)");

        query.bindValue(":category",ui->comboBox->currentText());
        query.bindValue(":collection",apd.getCollection());
        query.bindValue(":model",apd.getModel());
        query.bindValue(":type",apd.getType());
        query.bindValue(":item",apd.getPattern());
        query.bindValue(":price",apd.getPrice());

        if( !query.exec() )
            qDebug() << query.lastError().text();
        else
            qDebug( "Inserted!" );

        ui->tableWidget->model()->removeRows(0, ui->tableWidget->rowCount());

        query.exec("SELECT * FROM item_price");
        
		while (query.next()) {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            for (int a=0; a<7; a++) {
                ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, a, new QTableWidgetItem(query.value(a).toString()));
            }
        }
        update();
    }
}

void PriceDialog::on_pushButton_3_clicked() {    
    QString ids;
    QSqlQuery query;
    QList<QTableWidgetItem*> selectionRangeList = ui->tableWidget->selectedItems();
    int rowIndex;
    QListIterator<QTableWidgetItem*> selectionRangeListIter(selectionRangeList);

	ui->pushButton_3->setEnabled(false);

    while(selectionRangeListIter.hasNext()) {
        rowIndex = ((int)((QTableWidgetItem*)selectionRangeListIter.next())->row());                
        ids += ui->tableWidget->item(rowIndex, 0)->text() + ",";
        ui->tableWidget->removeRow(rowIndex);
    }

    query.exec("DELETE FROM item_price WHERE id IN ("+ids.left(ids.length()-1)+")");

    update();
    
	ui->pushButton_3->setEnabled(true);
}