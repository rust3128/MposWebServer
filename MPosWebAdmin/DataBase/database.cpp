#include "database.h"

DataBase::DataBase(const QSettings *settings)
{
    db = QSqlDatabase::addDatabase("QIBASE");
    db.setHostName(settings->value("Server").toString());
    db.setPort(settings->value("Port").toInt());
    db.setDatabaseName(settings->value("Database").toString());
    db.setUserName(settings->value("User").toString());
    db.setPassword(settings->value("Password").toString());

}


bool DataBase::openDatabase()
{
    db.open();
    return db.isOpen();
}
