#include "datbasesettingsdialog.h"
#include "ui_datbasesettingsdialog.h"
#include "LoggingCategories/loggingcategories.h"

DatbaseSettingsDialog::DatbaseSettingsDialog(QSettings *set, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatbaseSettingsDialog),
    dbSettings(set)
{
    ui->setupUi(this);
    createUI();
}

DatbaseSettingsDialog::~DatbaseSettingsDialog()
{
    delete ui;
}

void DatbaseSettingsDialog::changeEvent(QEvent *e)
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

void DatbaseSettingsDialog::createUI()
{
    ui->lineEditServer->setText(dbSettings->value("Server").toString());
    ui->spinBoxPort->setValue(dbSettings->value("Port").toInt());
    ui->lineEditDatabase->setText(dbSettings->value("Database").toString());
    ui->lineEditUser->setText(dbSettings->value("User").toString());
    ui->lineEditPassword->setText(dbSettings->value("Password").toString());

}

void DatbaseSettingsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void DatbaseSettingsDialog::on_buttonBox_accepted()
{
    qInfo(logInfo()) << "INI file CROUP" << dbSettings->group();
    dbSettings->setValue("Server",ui->lineEditServer->text().trimmed());
    dbSettings->setValue("Port",ui->spinBoxPort->value());
    dbSettings->setValue("Database",ui->lineEditDatabase->text().trimmed());
    dbSettings->setValue("User",ui->lineEditUser->text().trimmed());
    dbSettings->setValue("Password",ui->lineEditPassword->text().trimmed());

    this->accept();

}
