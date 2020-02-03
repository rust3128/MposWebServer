#ifndef OBJECTEDITDIALOG_H
#define OBJECTEDITDIALOG_H

#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class ObjectEditDialog;
}

class ObjectEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectEditDialog(uint clID, uint objID, QWidget *parent = nullptr);
    ~ObjectEditDialog();

private slots:
    void on_checkBoxIsActive_toggled(bool checked);
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_lineEditTerminalID_textChanged(const QString &arg1);

private:
    void createUI();
    bool veryfyTerminalID(uint termID);
private:
    Ui::ObjectEditDialog *ui;
    uint clientID = 0;
    uint objectID = 0;
    QString clientName;
    bool terminalIDChanged = false;
};

#endif // OBJECTEDITDIALOG_H
