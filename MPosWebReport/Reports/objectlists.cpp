#include "objectlists.h"
#include "template.h"
#include "global.h"


ObjectLists::ObjectLists(uint id, QObject *parent) :
    HttpRequestHandler(parent),
    userID(id)
{
    // Ищем конфигурационный файл
    QString configFileName=searchConfigFile();
    // Получаем настройки базы данных
    QSettings *databaseSettings = new QSettings(configFileName,QSettings::IniFormat);
    databaseSettings->beginGroup("Database");
    db = new DataBase(databaseSettings);
    db->openDatabase();
    createModels();
    getClientData();
}



void ObjectLists::createModels()
{

    modelObjects = new QSqlQueryModel();
    QString strSQL = QString("SELECT o.terminal_id, o.name, o.address, o.object_id from objects o "
                             "INNER JOIN clientusers u ON u.client_id = o.client_id "
                             "WHERE u.user_id = %1 "
                             "ORDER BY o.terminal_id").arg(userID);
    modelObjects->setQuery(strSQL);
    azsCount=modelObjects->rowCount();
    qDebug() << "Count AZS" << azsCount;

}

void ObjectLists::getClientData()
{
    QSqlQuery q;
    q.prepare("select c.clientname from clients c "
              "INNER JOIN clientusers u ON u.client_id = c.client_id "
              "where u.user_id=:userID");
    q.bindValue(":userID",userID);
    q.exec();
    q.next();
    clientName=q.value(0).toString().trimmed();
    qDebug() << "Client NAme = "<< clientName;
}


void ObjectLists::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray language=request.getHeader("Accept-Language");
    qDebug("language=%s",qPrintable(language));

    response.setHeader("Content-Type", "text/html; charset=utf-8");
    Template t=templateCache->getTemplate("objectslist");
    t.setVariable("clientName", clientName);
    t.loop("row",azsCount);
    for(int i=0;i<azsCount;++i){
        QString number = QString::number(i);
        QString numPp = QString::number(i+1);
        QString terminalID = modelObjects->data(modelObjects->index(i,0)).toString();
        QString name = modelObjects->data(modelObjects->index(i,1)).toString();
        QString address = modelObjects->data(modelObjects->index(i,2)).toString();
        QString objectID = modelObjects->data(modelObjects->index(i,3)).toString();
        t.setVariable("row"+number+".numPp",numPp);
        t.setVariable("row"+number+".terminalID",terminalID);
        t.setVariable("row"+number+".name",name);
        t.setVariable("row"+number+".address",address);
        t.setVariable("row"+number+".objectID",objectID);
    }
    response.write(t.toUtf8(),true);

//    response.write("<html><body>");
//    response.write(QString("Выбран пользователь с ID = %1").arg(userID).toUtf8());
//    response.write("</body></html>",true);
}
