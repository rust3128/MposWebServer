#include "objecteditdialog.h"
#include "ui_objecteditdialog.h"
#include <QIntValidator>

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
//        q.prepare("SELECT username, userpass, fio, phone, email, isactive FROM clientusers WHERE (user_id = :userID)");
//        q.bindValue(":userID", userID);
//        q.exec();
//        q.next();
//        ui->lineEditLogin->setText(q.value(0).toString());
//        ui->lineEditPass->setText(q.value(1).toString());
//        ui->lineEditConfPass->setText(q.value(1).toString());
//        ui->lineEditFIO->setText(q.value(2).toString());
//        ui->lineEditPhone->setText(q.value(3).toString());
//        ui->lineEditEMail->setText(q.value(4).toString());
//        ui->checkBoxIsActive->setChecked(q.value(5).toBool());
//        on_checkBoxIsActive_toggled(ui->checkBoxIsActive->isChecked());
    }
}

void ObjectEditDialog::on_checkBoxIsActive_toggled(bool checked)
{
    if(checked){
        ui->checkBoxIsActive->setText("Доступ разрешен");
    } else {
        ui->checkBoxIsActive->setText("Доступ запрещен");
    }
}
