#include "requestmapper.h"
#include "global.h"

RequestMapper::RequestMapper(QObject *parent) :
    HttpRequestHandler(parent)
{

}


void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray username=request.getParameter("username");
    QByteArray password=request.getParameter("password");
    QByteArray userid = request.getParameter("userid");

    qDebug("Request username=%s",username.constData());
    qDebug("Recwest password=%s",password.constData());
    qDebug("User ID=%s",userid.constData());

    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
    if (path=="/"/* || path=="/login"*/) {
        loginPage.service(request, response);
    } else if(path=="/login"){
        response.write("Lofin ok");
    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}
