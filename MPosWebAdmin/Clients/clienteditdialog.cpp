#include "clienteditdialog.h"
#include "ui_clienteditdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>

#define MAX_CHAR 100


ClientEditDialog::ClientEditDialog(uint clientID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientEditDialog),
    clientID(clientID)
{
    ui->setupUi(this);
    createUI();
}

ClientEditDialog::~ClientEditDialog()
{
    delete ui;
}

void ClientEditDialog::changeEvent(QEvent *e)
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

void ClientEditDialog::createUI()
{
    if(clientID>0){
        QSqlQuery q;
        q.prepare("select c.clientname, c.comments, c.isactive from clients c where c.client_id = :clientID");
        q.bindValue(":clientID", clientID);
        q.exec();
        q.next();
        ui->lineEditName->setText(q.value(0).toString().trimmed());
        ui->plainTextEditComment->setPlainText(q.value(1).toString().trimmed());
        ui->checkBoxIsActive->setChecked(q.value(2).toBool());
    }
}

void ClientEditDialog::on_buttonBox_rejected()
{
    this->reject();
}

void ClientEditDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(clientID == 0){
        q.prepare("INSERT INTO CLIENTS (CLIENTNAME, COMMENTS) VALUES (:clientName, :clientComment)");
    } else {
        q.prepare("UPDATE CLIENTS SET CLIENTNAME = :clientName, COMMENTS = :clientComment, ISACTIVE = :isActive WHERE CLIENT_ID = :clientID");
    }
    q.bindValue(":clientName", ui->lineEditName->text().trimmed());
    q.bindValue(":clientComment", ui->plainTextEditComment->toPlainText().trimmed());
    q.bindValue(":isActive", ui->checkBoxIsActive->isChecked());
    q.bindValue(":clientID", clientID);
    if(!q.exec()) qCritical(logCritical()) << "ERROR UPDATE" << q.lastError().text();
    this->accept();
}
