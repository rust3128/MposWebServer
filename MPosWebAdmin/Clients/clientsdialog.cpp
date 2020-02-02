#include "clientsdialog.h"
#include "ui_clientsdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include "Clients/clienteditdialog.h"
#include "Clients/usereditdialog.h"
#include "objecteditdialog.h"
#include <QMessageBox>
#include <QIcon>

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

    modelUsers = new ModelUsers(this);
    modelUsers->setTable("CLIENTUSERS");
    modelUsers->setHeaderData(2,Qt::Horizontal,"Логин");
    modelUsers->setHeaderData(3,Qt::Horizontal,"Пароль");
    modelUsers->setHeaderData(4,Qt::Horizontal,"ФИО");
    modelUsers->setHeaderData(5,Qt::Horizontal,"Телефон");
    modelUsers->setHeaderData(6,Qt::Horizontal,"E-Mail");
    modelUsers->setHeaderData(7,Qt::Horizontal,"Доступ");
    modelUsers->select();
    modelUsers->setFilter("client_id = 0");

    modelObjects = new ModelObjects(this);
    modelObjects->setTable("OBJETS");
    modelObjects->setHeaderData(2,Qt::Horizontal,"Терминал");
    modelObjects->setHeaderData(3,Qt::Horizontal,"Нименование");
    modelObjects->setHeaderData(4,Qt::Horizontal,"Адрес");
    modelObjects->setHeaderData(5,Qt::Horizontal,"Телефон");
    modelObjects->setHeaderData(6,Qt::Horizontal,"Сервер");
    modelObjects->setHeaderData(7,Qt::Horizontal,"База данных");
    modelObjects->setHeaderData(8,Qt::Horizontal,"Пользователь");
    modelObjects->setHeaderData(9,Qt::Horizontal,"Пароль");
    modelObjects->setHeaderData(10,Qt::Horizontal,"Бослуживаем");
    modelUsers->select();



}

void ClientsDialog::createUI()
{
    ui->toolButtonClientEdit->setEnabled(false);
    ui->groupBoxUsers->setEnabled(false);
    ui->splitterMain->setStretchFactor(0,0);
    ui->splitterMain->setStretchFactor(1,1);
    ui->toolButtonUserEdit->setEnabled(false);
    ui->toolButtonUserDel->setEnabled(false);
    ui->toolButtonAZSEdit->setEnabled(false);
    ui->toolButtonAZSDel->setEnabled(false);

    ui->listViewClients->setModel(modelClients);
    ui->listViewClients->setModelColumn(1);

    ui->tableViewUsers->setModel(modelUsers);
    ui->tableViewUsers->verticalHeader()->hide();
    ui->tableViewUsers->horizontalHeader()->hide();
    ui->tableViewUsers->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: darkgrey}");
    ui->tableViewUsers->hideColumn(0);
    ui->tableViewUsers->hideColumn(1);

    ui->tableViewAZS->setModel(modelObjects);
    ui->tableViewAZS->verticalHeader()->hide();
    ui->tableViewAZS->horizontalHeader()->hide();
    ui->tableViewAZS->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: darkgrey}");
    ui->tableViewAZS->hideColumn(0);
    ui->tableViewAZS->hideColumn(1);


}

void ClientsDialog::createConnections()
{
    connect(ui->listViewClients->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotClientSelect);
    connect(ui->tableViewUsers->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotUserSelect);
    connect(ui->tableViewAZS->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotObjectSelect);
}


void ClientsDialog::slotClientSelect(const QItemSelection &, const QItemSelection &)
{
    ui->toolButtonClientEdit->setEnabled(true);
    ui->groupBoxUsers->setEnabled(true);
    QModelIndexList selectionClient = ui->listViewClients->selectionModel()->selectedIndexes();
    clientID = modelClients->data(modelClients->index(selectionClient.at(0).row(),0)).toUInt();
    ui->textEditComment->setText(modelClients->data(modelClients->index(selectionClient.at(0).row(),2)).toString().trimmed());

    modelUsers->setFilter(QString("client_id = %1").arg(clientID));
    if(modelUsers->rowCount()>0){
        ui->tableViewUsers->horizontalHeader()->show();
        ui->tableViewUsers->resizeColumnsToContents();
        ui->tableViewUsers->verticalHeader()->setDefaultSectionSize(ui->tableViewUsers->verticalHeader()->minimumSectionSize());
    } else {
        ui->tableViewUsers->horizontalHeader()->hide();
    }

    modelObjects->setFilter(QString("client_id = %1").arg(clientID));
    if(modelObjects->rowCount()>0){
        ui->tableViewAZS->horizontalHeader()->show();
        ui->tableViewAZS->resizeColumnsToContents();
        ui->tableViewAZS->verticalHeader()->setDefaultSectionSize(ui->tableViewAZS->verticalHeader()->minimumSectionSize());
    } else {
        ui->tableViewAZS->horizontalHeader()->hide();
    }

}

void ClientsDialog::slotUserSelect(const QItemSelection &, const QItemSelection &)
{
    ui->toolButtonUserDel->setEnabled(true);
    ui->toolButtonUserEdit->setEnabled(true);
    QModelIndexList selectionUser = ui->tableViewUsers->selectionModel()->selectedIndexes();
    userID = modelUsers->data(modelUsers->index(selectionUser.at(0).row(),0),Qt::DisplayRole).toUInt();
}

void ClientsDialog::slotObjectSelect(const QItemSelection &, const QItemSelection &)
{
    ui->toolButtonAZSDel->setEnabled(true);
    ui->toolButtonAZSEdit->setEnabled(true);
    QModelIndexList selectionObject = ui->tableViewAZS->selectionModel()->selectedIndexes();
    objectID = modelObjects->data(modelObjects->index(selectionObject.at(0).row(),0),Qt::DisplayRole).toUInt();
}

void ClientsDialog::on_toolButtonClientEdit_clicked()
{
    ClientEditDialog *clEdDlg = new ClientEditDialog(clientID,this);
    clEdDlg->setWindowTitle("Редактирование");
    if(clEdDlg->exec() == QDialog::Accepted){
        modelClients->select();
    }
}

void ClientsDialog::on_toolButtonClientAdd_clicked()
{
    ClientEditDialog *clEdDlg = new ClientEditDialog(0,this);
    clEdDlg->setWindowTitle("Новый клиент");
    if(clEdDlg->exec() == QDialog::Accepted){
        modelClients->select();
    }
}

void ClientsDialog::on_toolButtonUserAdd_clicked()
{
    UserEditDialog *userDlg = new UserEditDialog(clientID, 0, this);
    if(userDlg->exec() == QDialog::Accepted) {
        modelUsers->select();
    }
}

void ClientsDialog::on_toolButtonUserEdit_clicked()
{
    UserEditDialog *userDlg = new UserEditDialog(clientID, userID, this);
    if(userDlg->exec() == QDialog::Accepted) {
        modelUsers->select();
    }
}

void ClientsDialog::on_toolButtonUserDel_clicked()
{
    QModelIndex idx = ui->tableViewUsers->currentIndex();
    QMessageBox msgBox;
    msgBox.setWindowTitle("Удаление пользователя");
    msgBox.setText("Вы действительно безвозвратно хотите удалить пользоватля <b>"
                              +modelUsers->data(modelUsers->index(idx.row(),4),Qt::DisplayRole).toString()+"</b>?");
    msgBox.setInformativeText("Восстановление пользователя будет не возможно.");
    msgBox.setIconPixmap(QPixmap(":/Images/delete.png"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes) {
        QSqlQuery q;
        q.prepare("DELETE FROM clientusers WHERE user_id = :userID");
        q.bindValue(":userID", userID);
        q.exec();
        modelUsers->select();
    }

}

void ClientsDialog::on_tableViewUsers_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    UserEditDialog *userDlg = new UserEditDialog(clientID, userID, this);
    if(userDlg->exec() == QDialog::Accepted) {
        modelUsers->select();
    }
}

void ClientsDialog::on_toolButtonAZSAdd_clicked()
{
    ObjectEditDialog * objDlg = new ObjectEditDialog(clientID,0,this);
    objDlg->exec();

}
