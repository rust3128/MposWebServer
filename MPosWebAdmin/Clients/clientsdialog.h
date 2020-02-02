#ifndef CLIENTSDIALOG_H
#define CLIENTSDIALOG_H

#include "modelusers.h"
#include "modelobjects.h"
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QItemSelection>

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

private slots:
    void slotClientSelect(const QItemSelection &, const QItemSelection &);
    void slotUserSelect(const QItemSelection &, const QItemSelection &);
    void slotObjectSelect(const QItemSelection &, const QItemSelection &);
    void on_toolButtonClientEdit_clicked();
    void on_toolButtonClientAdd_clicked();
    void on_toolButtonUserAdd_clicked();
    void on_toolButtonUserEdit_clicked();
    void on_toolButtonUserDel_clicked();
    void on_tableViewUsers_doubleClicked(const QModelIndex &index);
    void on_toolButtonAZSAdd_clicked();

private:
    void createModel();
    void createUI();
    void createConnections();
private:
    Ui::ClientsDialog *ui;
    QSqlTableModel *modelClients;
    ModelUsers *modelUsers;
    ModelObjects *modelObjects;
    uint clientID =0;
    uint userID = 0;
    uint objectID =0;
};

#endif // CLIENTSDIALOG_H
