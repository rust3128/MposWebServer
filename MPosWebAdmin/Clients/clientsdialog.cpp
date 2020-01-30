#include "clientsdialog.h"
#include "ui_clientsdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "Clients/clienteditdialog.h"

ClientsDialog::ClientsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsDialog)
{
    ui->setupUi(this);
    createModel();
    createUI();
    createConnections();
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
    modelClients->setSort(1,Qt::AscendingOrder);
    modelClients->select();

}

void ClientsDialog::createUI()
{
//    ui->checkBoxClientAll->setStyleSheet(
//                "QCheckBox::indicator:unchecked {image: url(:/Images/check_box_unchek.png);}"
//                "QCheckBox::indicator:checked {image: url(:/Images/check_box.png);}"
//                "QCheckBox::unchecked {color: darkRed;}"
//                "QCheckBox::checked {color: darkBlue;}"
//                );
    ui->listViewClients->setModel(modelClients);
    ui->listViewClients->setModelColumn(1);
    ui->toolButtonClientEdit->setEnabled(false);
    ui->toolButtonClientDel->setEnabled(false);


}

void ClientsDialog::createConnections()
{
    connect(ui->listViewClients->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotClientSelect);
}


void ClientsDialog::slotClientSelect(const QItemSelection &, const QItemSelection &)
{
    ui->toolButtonClientEdit->setEnabled(true);
    ui->toolButtonClientDel->setEnabled(true);
    QModelIndexList selectionClient = ui->listViewClients->selectionModel()->selectedIndexes();
    clientID = modelClients->data(modelClients->index(selectionClient.at(0).row(),0)).toUInt();
    ui->textEditComment->setText(modelClients->data(modelClients->index(selectionClient.at(0).row(),2)).toString().trimmed());

}

void ClientsDialog::on_toolButtonClientEdit_clicked()
{
    ClientEditDialog *clEdDlg = new ClientEditDialog(clientID,this);
    clEdDlg->exec();
    modelClients->select();
}

void ClientsDialog::on_toolButtonClientAdd_clicked()
{
    ClientEditDialog *clEdDlg = new ClientEditDialog(0,this);
    clEdDlg->exec();
    modelClients->select();
}
