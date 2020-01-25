#include "requestmapper.h"
#include "global.h"

RequestMapper::RequestMapper(QObject *parent) :
    HttpRequestHandler(parent)
{

}


void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
    if (path=="/" || path=="/login") {
        loginPage.service(request, response);
    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}
