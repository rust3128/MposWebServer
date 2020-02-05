#include "objectlists.h"

ObjectLists::ObjectLists(QObject *parent) :
    HttpRequestHandler(parent)
{

}

void ObjectLists::setUserID(uint ID)
{
    userID = ID;
}


void ObjectLists::service(HttpRequest &request, HttpResponse &response)
{
    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.write("<html><body>");
    response.write(QString("Выбран пользователь с ID = %1").arg(userID).toUtf8());
    response.write("</body></html>",true);
}
