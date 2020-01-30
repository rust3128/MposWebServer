#ifndef CLIENTEDITDIALOG_H
#define CLIENTEDITDIALOG_H

#include <QDialog>

namespace Ui {
class ClientEditDialog;
}

class ClientEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientEditDialog(uint clientID = 0, QWidget *parent = nullptr);
    ~ClientEditDialog();

protected:
    void changeEvent(QEvent *e);

private slots:

    void on_plainTextEditComment_textChanged();

private:
    void createUI();
private:
    Ui::ClientEditDialog *ui;
    uint clientID;
};

#endif // CLIENTEDITDIALOG_H
