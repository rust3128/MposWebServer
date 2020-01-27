#include "datbasesettingsdialog.h"
#include "ui_datbasesettingsdialog.h"

DatbaseSettingsDialog::DatbaseSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatbaseSettingsDialog)
{
    ui->setupUi(this);
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
