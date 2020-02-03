#include "objecteditdialog.h"
#include "ui_objecteditdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QIntValidator>
#include <QMessageBox>

ObjectEditDialog::ObjectEditDialog(uint clID, uint objID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectEditDialog),
    clientID(clID),
    objectID(objID)
{
    ui->setupUi(this);
    createUI();
}

ObjectEditDialog::~ObjectEditDialog()
{
    delete ui;
}

void ObjectEditDialog::createUI()
{
    ui->lineEditTerminalID->setValidator(new QIntValidator(1001,99999,this));

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
    ui->labelClientName->setText(clientName);
    if(objectID == 0) {
        this->setWindowTitle("Новая АЗС");
        ui->checkBoxIsActive->setCheckState(Qt::Checked);
    } else {
       this->setWindowTitle("Редактирование данных АЗС");
        q.prepare("SELECT o.terminal_id,o.name,o.address,o.phone,o.server,o.objdb,o.objdbuser,o.pass,o.isactive FROM objects o WHERE (o.object_id = :objectID)");
        q.bindValue(":objectID", objectID);
        q.exec();
        q.next();
        ui->lineEditTerminalID->setText(q.value(0).toString());
        ui->lineEditTerminalID->setReadOnly(true);
        ui->plainTextEditName->setPlainText(q.value(1).toString());
        ui->plainTextEditAddress->setPlainText(q.value(2).toString());
        ui->lineEditPhone->setText(q.value(3).toString());
        ui->lineEditServer->setText(q.value(4).toString());
        ui->lineEditDatabase->setText(q.value(5).toString());
        ui->lineEditUserDB->setText(q.value(6).toString());
        ui->lineEditPassDB->setText(q.value(7).toString());
        ui->checkBoxIsActive->setChecked(q.value(8).toBool());
        on_checkBoxIsActive_toggled(ui->checkBoxIsActive->isChecked());
    }
}



void ObjectEditDialog::on_checkBoxIsActive_toggled(bool checked)
{
    if(checked){
        ui->checkBoxIsActive->setText("АЗС обслуживается");
    } else {
        ui->checkBoxIsActive->setText("АЗС НЕ обслуживается");
    }
}

void ObjectEditDialog::on_buttonBox_rejected()
{
    this->reject();
}

void ObjectEditDialog::on_buttonBox_accepted()
{
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle( (objectID == 0) ? "Новый объект" : "Редактирование объекта");
    msgBox->setIcon(QMessageBox::Critical);
    uint terminalID = ui->lineEditTerminalID->text().toUInt();
    if(terminalID <= 1000 || terminalID >99999){
        msgBox->setText("Номер терминала должен быть в дипазоне 1001 ... 99999.");
        msgBox->exec();
        return;
    }
    if(objectID == 0){
        if(veryfyTerminalID(terminalID) ){
            msgBox->setText("У клиента <b>"+clientName+"</b> терминал с номером <b>"+ui->lineEditTerminalID->text().trimmed()+"</b> существует!");
            msgBox->exec();
            return;
        }
    }
    if(ui->plainTextEditName->toPlainText().trimmed().length() < 5){
        msgBox->setText("Не указано или слишком короткое наименование терминала.");
        msgBox->exec();
        return;
    }
    if(ui->lineEditServer->text().trimmed().isEmpty()){
        msgBox->setText("Не указан сервер базы данных объекта.");
        msgBox->exec();
        return;
    }
    if(ui->lineEditDatabase->text().trimmed().isEmpty()){
        msgBox->setText("Не указан файл или алиас базы данных объекта.");
        msgBox->exec();
        return;
    }
    if(ui->lineEditUserDB->text().trimmed().isEmpty()){
        msgBox->setText("Не указан пользователь базы данных объекта.");
        msgBox->exec();
        return;
    }
    if(ui->lineEditServer->text().trimmed().isEmpty()){
        msgBox->setText("Не указан пароль для подключения к базе данных объекта.");
        msgBox->exec();
        return;
    }
    QSqlQuery q;
    if(objectID == 0){
        q.prepare("INSERT INTO OBJECTS (CLIENT_ID, TERMINAL_ID, NAME, ADDRESS, PHONE, SERVER, OBJDB, OBJDBUSER, PASS) "
                               "VALUES (:clientID, :terminalID, :name, :address, :phone, :serDB, :db, :user, :pass)");
    } else {
        q.prepare("UPDATE OBJECTS SET CLIENT_ID = :clientID, TERMINAL_ID = :terminalID, NAME = :name, ADDRESS = :address, PHONE = :phone, "
                  "SERVER = :serDB, OBJDB = :db, OBJDBUSER = :user, PASS = :pass, ISACTIVE = :isActive WHERE (OBJECT_ID = :objectID)");
    }
    q.bindValue(":clientID", clientID);
    q.bindValue(":terminalID", terminalID);
    q.bindValue(":name", ui->plainTextEditName->toPlainText().trimmed());
    q.bindValue(":address", ui->plainTextEditAddress->toPlainText().trimmed());
    q.bindValue(":phone", ui->lineEditPhone->text().trimmed());
    q.bindValue(":serDB",ui->lineEditServer->text().trimmed());
    q.bindValue(":db",ui->lineEditDatabase->text().trimmed());
    q.bindValue(":user",ui->lineEditUserDB->text().trimmed());
    q.bindValue(":pass",ui->lineEditPassDB->text().trimmed());
    q.bindValue(":isActive",ui->checkBoxIsActive->isChecked());
    q.bindValue(":objectID", objectID);
    if(!q.exec()) {
        qCritical(logCritical()) << "Ошибка изменения таблицы объектов." << q.lastError().text();
        msgBox->setText("Ошибка приложения. Не удалось изменить справочник объектов.");
        msgBox->setInformativeText(tr("Ошибка при работе с базой данных."));
        msgBox->setDetailedText(q.lastError().text());
        msgBox->exec();
        return;
    }
    qInfo(logInfo()) << "Справочник объектов успешно обновлен.";
    this->accept();

}

bool ObjectEditDialog::veryfyTerminalID(uint termID)
{
    QSqlQuery q;
    q.prepare("SELECT COUNT(terminal_ID) FROM objects WHERE (CLIENT_ID = :clientID) AND (terminal_id = :terminalID)");
    q.bindValue(":clientID", clientID);
    q.bindValue(":terminalID", termID);
    if(!q.exec()){
        qInfo(logInfo()) << "Ошибка получения списка терминалов" << q.lastError().text();
        return true;
    }
    q.next();
    return (q.value(0).toInt() != 0) ? true : false;
}

void ObjectEditDialog::on_lineEditTerminalID_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    terminalIDChanged =true;
}
