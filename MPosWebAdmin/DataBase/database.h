#ifndef DATABASE_H
#define DATABASE_H
#include <QString>
#include <QSettings>
#include <QSqlDatabase>

class DataBase
{
public:
    DataBase(const QSettings* settings);
    bool openDatabase();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
