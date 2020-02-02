#include "clientsdialog.h"
#include "ui_clientsdialog.h"
#include "LoggingCategories/loggingcategories.h"

#include "Clients/clienteditdialog.h"
#include "Clients/usereditdialog.h"
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
//    modelUsers->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: red}");

    modelUsers->select();
    modelUsers->setFilter("client_id = 0");

}

void ClientsDialog::createUI()
{
    ui->toolButtonClientEdit->setEnabled(false);
    ui->groupBoxUsers->setEnabled(false);
    ui->splitter->setStretchFactor(0,0);
    ui->splitter->setStretchFactor(1,1);
    ui->toolButtonUserEdit->setEnabled(false);
    ui->toolButtonUserDel->setEnabled(false);

//    ui->checkBoxClientAll->setStyleSheet(
//                "QCheckBox::indicator:unchecked {image: url(:/Images/check_box_unchek.png);}"
//                "QCheckBox::indicator:checked {image: url(:/Images/check_box.png);}"
//                "QCheckBox::unchecked {color: darkRed;}"
//                "QCheckBox::checked {color: darkBlue;}"
//                );

    ui->splitter->setStyleSheet("QSplitter::handle{background: darkGreen}");
    ui->listViewClients->setModel(modelClients);
    ui->listViewClients->setModelColumn(1);

    ui->tableViewUsers->setModel(modelUsers);
    ui->tableViewUsers->verticalHeader()->hide();
    ui->tableViewUsers->horizontalHeader()->hide();
    ui->tableViewUsers->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: darkgrey}");
    ui->tableViewUsers->hideColumn(0);
    ui->tableViewUsers->hideColumn(1);
//    ui->tableViewUsers->hideColumn(7);




}

void ClientsDialog::createConnections()
{
    connect(ui->listViewClients->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotClientSelect);
    connect(ui->tableViewUsers->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsDialog::slotUserSelect);
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

}

void ClientsDialog::slotUserSelect(const QItemSelection &, const QItemSelection &)
{
    ui->toolButtonUserDel->setEnabled(true);
    ui->toolButtonUserEdit->setEnabled(true);
    QModelIndexList selectionUser = ui->tableViewUsers->selectionModel()->selectedIndexes();
    userID = modelUsers->data(modelUsers->index(selectionUser.at(0).row(),0),Qt::DisplayRole).toUInt();
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
