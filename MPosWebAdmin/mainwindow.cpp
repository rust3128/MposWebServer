#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DataBase/datbasesettingsdialog.h"
#include "Clients/clientsdialog.h"

MainWindow::MainWindow(QSettings *set, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , appSettings(set)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionDataBase_triggered()
{
    DatbaseSettingsDialog *dbDlg = new DatbaseSettingsDialog(appSettings,this);
    dbDlg->exec();

}

void MainWindow::on_actionClients_triggered()
{
    ClientsDialog *clnDlg = new ClientsDialog();
    this->setCentralWidget(clnDlg);
    clnDlg->exec();

}
