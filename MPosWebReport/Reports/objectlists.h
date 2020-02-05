#ifndef OBJECTLISTS_H
#define OBJECTLISTS_H
#include "httprequesthandler.h"

using namespace stefanfrings;

class ObjectLists : public HttpRequestHandler
{
    Q_OBJECT
public:
   explicit ObjectLists(QObject *parent = nullptr);
   void setUserID(uint ID);

private:
    uint userID;

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
};

#endif // OBJECTLISTS_H
