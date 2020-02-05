#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "logincontroller.h"
#include "Reports/objectlists.h"

#include <QSqlQueryModel>
#include <QSqlError>

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    RequestMapper(QObject *parent = nullptr);

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
private:
    uint getUserID(QString login, QString pass);
private:
    LoginController loginPage;
    ObjectLists objectListPage;
    QSqlQueryModel *modelUsers;
    uint userID;
};

#endif // REQUESTMAPPER_H
