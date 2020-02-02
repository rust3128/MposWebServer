#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class UserEditDialog;
}

class UserEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserEditDialog(uint clID, uint usID, QWidget *parent = nullptr);
    ~UserEditDialog();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_checkBoxIsActive_toggled(bool checked);

private:
    void createUI();
    bool verifyLogin(QString login);
private:
    Ui::UserEditDialog *ui;
    uint clientID;
    uint userID;
    QString clientName;
};

#endif // USEREDITDIALOG_H
