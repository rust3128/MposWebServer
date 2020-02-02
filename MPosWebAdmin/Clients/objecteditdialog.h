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

private:
    void createUI();
private:
    Ui::ObjectEditDialog *ui;
    uint clientID = 0;
    uint objectID = 0;
    QString clientName;
};

#endif // OBJECTEDITDIALOG_H
