#include "database.h"
#include "LoggingCategories/loggingcategories.h"
#include "datbasesettingsdialog.h"
#include <QSqlError>
#include <QMessageBox>

DataBase::DataBase(QSettings *settings, QObject *parent)
    : QObject(parent),
      dbSet(settings)
{

    db = QSqlDatabase::addDatabase("QIBASE");
    db.setHostName(dbSet->value("Server").toString());
//    db.setPort(dbSet->value("Port").toInt());
    db.setDatabaseName(dbSet->value("Database").toString());
    db.setUserName(dbSet->value("User").toString());
    db.setPassword(dbSet->value("Password").toString());

}


bool DataBase::openDatabase()
{
    qInfo(logInfo()) << "DB Name" << db.databaseName();
    if(db.open()){
        qInfo(logInfo()) << QObject::tr("База данных успешно открыта!");
        return true;
    } else {
        qCritical(logCritical()) << QObject::tr("Не удалось открыть базу данных");
        QMessageBox msgBox;
        msgBox.setText("Ошибка приложения. Не удалось открыть базу данных.");
        msgBox.setInformativeText(tr("Проверить настройки подключения к базе данных?"));
        msgBox.setDetailedText(db.lastError().text());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes){
            DatbaseSettingsDialog *dbSetDlg = new DatbaseSettingsDialog(dbSet);
            dbSetDlg->exec();
        }
        return false;
    }

}
