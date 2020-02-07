#include <QCoreApplication>
#include <QDir>
#include <QFile>

#include "httplistener.h"
#include "httprequesthandler.h"
#include "requestmapper.h"

#include "DataBase/database.h"
#include "global.h"

using namespace stefanfrings;




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("MPosWebServer");
    a.setOrganizationName("RustSoft");

    // Ищем конфигурационный файл
    QString configFileName=searchConfigFile();

    // Configure logging
    QSettings* logSettings=new QSettings(configFileName,QSettings::IniFormat,&a);
    logSettings->beginGroup("logging");
    logger=new FileLogger(logSettings,10000,&a);
    logger->installMsgHandler();
    // Log the library version
    qDebug("QtWebApp has version %s",getQtWebAppLibVersion());

    // Configure template cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,&a);
    templateSettings->beginGroup("templates");
    templateCache=new TemplateCache(templateSettings,&a);

    // Получаем настройки базы данных
    QSettings *databaseSettings = new QSettings(configFileName,QSettings::IniFormat,&a);
    databaseSettings->beginGroup("Database");
    DataBase *db = new DataBase(databaseSettings,&a);
    if(!db->openDatabase()){
        qFatal("Не могу открвыть базу даных! Ааварийное завершение работы.");
        return 1;
    }
    // Читаем настройки сервера
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &a);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&a),&a);

    return a.exec();
}
