#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "httprequesthandler.h"

using namespace stefanfrings;
class LoginController : public HttpRequestHandler
{
    Q_OBJECT
public:
    LoginController(QObject *parent=nullptr);

    // HttpRequestHandler interface
public:
    void service(HttpRequest &request, HttpResponse &response);
private:
    void createLoginForm();
private:
    QString loginForm;
};

#endif // LOGINCONTROLLER_H
