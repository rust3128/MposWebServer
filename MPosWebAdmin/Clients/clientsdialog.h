#ifndef CLIENTSDIALOG_H
#define CLIENTSDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>

namespace Ui {
class ClientsDialog;
}

class ClientsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientsDialog(QWidget *parent = nullptr);
    ~ClientsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    void createModel();
    void createUI();
private:
    Ui::ClientsDialog *ui;
    QSqlTableModel *modelClients;
};

#endif // CLIENTSDIALOG_H
