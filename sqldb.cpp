#include "sqldb.h"

SQLdb::SQLdb() {
}

SQLdb::~SQLdb() {
    closeDB();
}

void SQLdb::openDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("practice.db");
    db.open();
}

void SQLdb::closeDB() {
    db.close();
}
