#include "logincontroller.h"

LoginController::LoginController(QObject *parent) :
    HttpRequestHandler(parent)
{
    createLoginForm();
}


void LoginController::service(HttpRequest &request, HttpResponse &response)
{
    QByteArray username=request.getParameter("username");
    QByteArray password=request.getParameter("password");


    qDebug("username=%s",username.constData());
    qDebug("password=%s",password.constData());

    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.write("<html><body>");


    if (username=="test" and password=="hello") {

        response.write("Yes, correct");
    } else {
          response.write(loginForm.toUtf8());
    }
    response.write("</body></html>",true);
}

void LoginController::createLoginForm()
{
    loginForm = "<html><head>"
                "<title>MPosWebReport</title>"
                "<meta name='viewport' content='width=device-width'>"
                "<meta http-equiv='Content-Type' content='text/html;charset=UTF-8'>"
                "<style type='text/css'> *{"
                "-ms-box-sizing: border-box;"
                "-moz-box-sizing: border-box;"
                "-webkit-box-sizing: border-box;"
                "box-sizing: border-box;"
                "margin: 0;"
                "padding: 0;"
                "border: 0;}"
                "html, body{"
                "width: 100%;"
                "height: 100%;"
                "font-family: 'Open Sans', sans-serif;"
                "font-weight: 200;}"
                "form{"
                "position: relative;"
                "top: 50%;"
                "width: 20%;"
                "display: table;"
                "margin: -100px auto 0 auto;}"

                "legend{"
                "position: relative;"
                "width: 100%;"
                "display: block;"
                "background: #527070;"
                "padding: 5px;"
                "color: #fff;"
                "font-size: 28px;"
                "border-radius: 5px;}"

                "input{"
                "width: 100%;"
                "padding: 5px 5px 5px 5px;"
                "display: block;"
                "border: 1px solid #EDEDED;"
                "border-radius: 5px;"
                "transition: 0.2s ease-out;"
                "color: darken(#EDEDED, 30%);"
                "&:focus{"
                "padding: 10px 5px 10px 10px;"
                "outline: 0;"
                "border-color: #FF7052;}}"
                "</style>"
                "</head>"
                "<body>"
                "<form class='login' action='/objects' method='post'>"
                "<fieldset>"
                "<legend class='legend' align='center'>Просмотр отчетов МПос</legend>"
                "<input type='text' name='username' placeholder='Имя' required>"
                "<input type='password' name='password' placeholder='Пароль' required>"
                "<input type='hidden' name='userid' value=></p>"
                "<input type='submit' value='Вход'>"
                "</fieldset>"
                "</form>";
}
