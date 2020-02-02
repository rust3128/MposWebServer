#include "usereditdialog.h"
#include "ui_usereditdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QMessageBox>

UserEditDialog::UserEditDialog(uint clID, uint usID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserEditDialog),
    clientID(clID),
    userID(usID)
{
    ui->setupUi(this);
    createUI();
}

UserEditDialog::~UserEditDialog()
{
    delete ui;
}

void UserEditDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void UserEditDialog::createUI()
{
    ui->checkBoxIsActive->setStyleSheet(
                      "QCheckBox::indicator:unchecked {image: url(:/Images/check_box_unchek.png);}"
                      "QCheckBox::indicator:checked {image: url(:/Images/check_box.png);}"
                      "QCheckBox::unchecked {color: red; }"
                      "QCheckBox::checked {color: green;}"
                      );

    QSqlQuery q;
    q.prepare("select c.clientname from clients c where c.client_id = :clientID");
    q.bindValue(":clientID", clientID);
    q.exec();
    q.next();
    clientName = q.value(0).toString().trimmed();
    ui->labelClient->setText(clientName);
    if(userID == 0) {
        this->setWindowTitle("Новый пользователь");
        ui->checkBoxIsActive->setCheckState(Qt::Checked);
    } else {
        this->setWindowTitle("Редактирование пользователя");
        q.prepare("SELECT username, userpass, fio, phone, email, isactive FROM clientusers WHERE (user_id = :userID)");
        q.bindValue(":userID", userID);
        q.exec();
        q.next();
        ui->lineEditLogin->setText(q.value(0).toString());
        ui->lineEditPass->setText(q.value(1).toString());
        ui->lineEditConfPass->setText(q.value(1).toString());
        ui->lineEditFIO->setText(q.value(2).toString());
        ui->lineEditPhone->setText(q.value(3).toString());
        ui->lineEditEMail->setText(q.value(4).toString());
        ui->checkBoxIsActive->setChecked(q.value(5).toBool());
        on_checkBoxIsActive_toggled(ui->checkBoxIsActive->isChecked());
    }
}


void UserEditDialog::on_buttonBox_rejected()
{
    this->reject();
}

void UserEditDialog::on_buttonBox_accepted()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Добавление пользователя");
    msgBox->setIcon(QMessageBox::Critical);
    if(ui->lineEditLogin->text().length()<4){
        msgBox->setInformativeText("Не верный логин!");
        msgBox->setText("Логин должен состоять з более 3-х символов.");
        msgBox->exec();
        return;
    }
    if(userID == 0 && verifyLogin(ui->lineEditLogin->text().trimmed())){
        msgBox->setInformativeText("Не верный логин!");
        msgBox->setText("У клиента <b>"+clientName+"</b> пользователь <b>"+ui->lineEditLogin->text().trimmed()+"</b> существует!");
        msgBox->exec();
        return;
    }
    if(ui->lineEditPass->text().length()<7){
        msgBox->setInformativeText("Не верный пароль!");
        msgBox->setText("Пароль должен состоять из более 6-ти символов.");
        msgBox->exec();
        return;
    }
    if(ui->lineEditPass->text().trimmed() != ui->lineEditConfPass->text().trimmed()){
        msgBox->setText("Пароли не совпадают!");
        msgBox->exec();
        return;
    }
    QSqlQuery q;
    if(userID == 0) {
        q.prepare("INSERT INTO CLIENTUSERS (CLIENT_ID, USERNAME, USERPASS, FIO, PHONE, EMAIL) "
                  "VALUES (:clientID, :userName, :userPass, :fio, :phone, :email)");
    } else {
        q.prepare("UPDATE CLIENTUSERS SET USERNAME=:userName, USERPASS=:userPass, FIO=:fio, PHONE=:phone, EMAIL=:email, ISACTIVE=:isactive WHERE (USER_ID=:userID)");
    }

    q.bindValue(":clientID", clientID);
    q.bindValue(":userID", userID);
    q.bindValue(":userName",ui->lineEditLogin->text().trimmed());
    q.bindValue(":userPass", ui->lineEditPass->text().trimmed());
    q.bindValue(":fio", ui->lineEditFIO->text().trimmed());
    q.bindValue(":phone", ui->lineEditPhone->text().trimmed());
    q.bindValue(":email", ui->lineEditEMail->text().trimmed());
    q.bindValue(":isactive", ui->checkBoxIsActive->isChecked());
    if(!q.exec()) {
        qInfo(logInfo()) << "Ошибка добавления пользователя." << q.lastError().text();
        msgBox->setText("Ошибка приложения. Не удалось изменить справочник пользователя.");
        msgBox->setInformativeText(tr("Ошибка при работе с базой данных."));
        msgBox->setDetailedText(q.lastError().text());
        msgBox->exec();
        return;
    }
    this->accept();
}

bool UserEditDialog::verifyLogin(QString login)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(username) FROM clientusers WHERE (CLIENT_ID = :clientID) AND (UPPER(USERNAME) = UPPER(:userName))");
    q.bindValue(":clientID", clientID);
    q.bindValue(":userName", login);
    if(!q.exec()) qInfo(logInfo()) << "Ошибка получения списка пользователей" << q.lastError().text();
    q.next();
    return (q.value(0).toInt() != 0) ? true : false;
}

void UserEditDialog::on_checkBoxIsActive_toggled(bool checked)
{
    if(checked){
        ui->checkBoxIsActive->setText("Доступ разрешен");
    } else {
        ui->checkBoxIsActive->setText("Доступ запрещен");
    }
}
