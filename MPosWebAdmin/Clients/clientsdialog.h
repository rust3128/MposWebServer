#ifndef CLIENTSDIALOG_H
#define CLIENTSDIALOG_H

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

    void on_toolButtonClientEdit_clicked();

private:
    void createModel();
    void createUI();
    void createConnections();
private:
    Ui::ClientsDialog *ui;
    QSqlTableModel *modelClients;
    uint clientID;
};

#endif // CLIENTSDIALOG_H
