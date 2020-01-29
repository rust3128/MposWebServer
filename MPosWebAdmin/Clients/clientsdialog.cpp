#include "clientsdialog.h"
#include "ui_clientsdialog.h"
#include "LoggingCategories/loggingcategories.h"

ClientsDialog::ClientsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsDialog)
{
    ui->setupUi(this);
    createModel();
    createUI();
}

ClientsDialog::~ClientsDialog()
{
    delete ui;
}

void ClientsDialog::changeEvent(QEvent *e)
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

void ClientsDialog::createModel()
{
    modelClients = new QSqlTableModel(this);
    modelClients->setTable("CLIENTS");
    modelClients->select();
}

void ClientsDialog::createUI()
{
    ui->listViewClients->setModel(modelClients);
    ui->listViewClients->setModelColumn(1);

}
