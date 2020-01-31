#include "usereditdialog.h"
#include "ui_usereditdialog.h"

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
    QSqlQuery q;
    q.prepare("select c.clientname from clients c where c.client_id = :clientID");
    q.bindValue(":clientID", clientID);
    q.exec();
    q.next();
    ui->labelClient->setText(q.value(0).toString().trimmed());
    if(userID == 0) {
        this->setWindowTitle("Новый пользователь");
        ui->labelLogin->setText("Введите логин...");
        ui->labelPass->setText("Пароль не может быть пустым.");
        ui->labelConfPass->setText("Пароль не может быть пустым.");

    } else {
        this->setWindowTitle("Редактирование пользователя");
    }
}

