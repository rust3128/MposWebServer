#include "requestmapper.h"
#include "global.h"

RequestMapper::RequestMapper(QObject *parent) :
    HttpRequestHandler(parent)
{
    userID = 0;
    modelUsers = new QSqlQueryModel(this);
    modelUsers->setQuery("SELECT c.user_id, c.username, c.userpass FROM clientusers c where c.isactive = 'true'");
    qDebug() << "Select ID usera" << modelUsers->lastError().text();
}


void RequestMapper::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray username=request.getParameter("username");
    QByteArray password=request.getParameter("password");
    QByteArray objectID=request.getParameter("objectID");

    if(username.length() !=0){
        userID=getUserID(QString(username), QString(password));
        qDebug() << "Current USER id =" << userID;
    }


    qDebug("Request in mapper username=%s",username.constData());
    qDebug("Recwest in mapper password=%s",password.constData());
    qDebug("Recwest in mapper ObjectID=%s",objectID.constData());

    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());
    if (path=="/"  ) {
        loginPage.service(request, response);
    } else if(path=="/objects"){
        if(userID >0){
            objectListPage = new ObjectLists(userID);
//            objectListPage->setUserID(userID);
            objectListPage->service(request,response);
        } else {
            loginPage.service(request, response);
        }
    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}

uint RequestMapper::getUserID(QString login, QString pass)
{
    uint userID = 0;
    const int rowCount = modelUsers->rowCount();
    for(int row=0; row<rowCount; ++row){
        if(modelUsers->data(modelUsers->index(row,1)).toString() == login){
            if(modelUsers->data(modelUsers->index(row,2)).toString() == pass){
                userID = modelUsers->data(modelUsers->index(row,0)).toUInt();
                break;
            }
        }
    }
    return userID;
}
