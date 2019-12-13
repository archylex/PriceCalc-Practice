#ifndef SQLDB_H
#define SQLDB_H

#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QSqlError>

class SQLdb {
public:
    SQLdb();
    ~SQLdb();
    QSqlDatabase db;
    void openDB();
    void closeDB();
};

#endif // SQLDB_H
