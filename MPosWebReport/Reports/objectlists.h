#ifndef OBJECTLISTS_H
#define OBJECTLISTS_H
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>
#include "DataBase/database.h"
#include "httprequesthandler.h"


using namespace stefanfrings;

class ObjectLists : public HttpRequestHandler
{
    Q_OBJECT
public:
   explicit ObjectLists(uint id, QObject *parent = nullptr);

private:
   void createModels();
   void getClientData();
private:
    uint userID;
    QSqlQueryModel *modelObjects;
    QString clientName;
    DataBase *db;
    int azsCount;
    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // OBJECTLISTS_H
