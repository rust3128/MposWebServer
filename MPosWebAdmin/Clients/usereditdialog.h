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

private:
    void createUI();
private:
    Ui::UserEditDialog *ui;
    uint clientID;
    uint userID;
};

#endif // USEREDITDIALOG_H
