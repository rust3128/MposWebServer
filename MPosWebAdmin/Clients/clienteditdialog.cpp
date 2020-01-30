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



void ClientEditDialog::on_plainTextEditComment_textChanged()
{
    if(ui->plainTextEditComment->placeholderText().length() > MAX_CHAR){
        ui->plainTextEditComment->setPlainText(ui->plainTextEditComment->placeholderText().left(MAX_CHAR));
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
