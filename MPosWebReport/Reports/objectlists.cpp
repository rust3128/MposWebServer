#include "objectlists.h"
#include "template.h"
#include "global.h"

ObjectLists::ObjectLists(uint id, QObject *parent) :
    HttpRequestHandler(parent),
    userID(id)
{
    createModels();
}



void ObjectLists::createModels()
{
    modelObjects = new QSqlQueryModel();
    QString strSQL = QString("SELECT o.terminal_id, o.name, o.address from objects o "
                             "INNER JOIN clientusers u ON u.client_id = o.client_id "
                             "WHERE u.user_id = %1").arg(userID);
    modelObjects->setQuery(strSQL);

}


void ObjectLists::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray language=request.getHeader("Accept-Language");
    qDebug("language=%s",qPrintable(language));

    response.setHeader("Content-Type", "text/html; charset=utf-8");
    Template t=templateCache->getTemplate("objectslist",language);
    t.setVariable("userID",QString::number(userID));
    response.write(t.toUtf8(),true);

//    response.write("<html><body>");
//    response.write(QString("Выбран пользователь с ID = %1").arg(userID).toUtf8());
//    response.write("</body></html>",true);
}
