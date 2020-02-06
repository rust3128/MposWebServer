#include "objectlists.h"

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
    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.write("<html><body>");
    response.write(QString("Выбран пользователь с ID = %1").arg(userID).toUtf8());
    response.write("</body></html>",true);
}
