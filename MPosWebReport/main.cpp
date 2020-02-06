#include <QCoreApplication>
#include <QDir>
#include <QFile>

#include "httplistener.h"
#include "httprequesthandler.h"
#include "requestmapper.h"

#include "DataBase/database.h"
#include "global.h"

using namespace stefanfrings;

/** Функция поиска конфигурационного файла */
QString searchConfigFile()
{
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName(appName+".ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../../etc"); // for development without shadow build
    searchList.append(binDir+"/../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(binDir+"/../../../../../"+appName+"/etc"); // for development with shadow build
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");
    searchList.append("/home/rust/develop/MposWebServer/etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            // Файл нашли
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // не нашли
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return nullptr;
}


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
