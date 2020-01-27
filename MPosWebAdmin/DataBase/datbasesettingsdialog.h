#ifndef DATBASESETTINGSDIALOG_H
#define DATBASESETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class DatbaseSettingsDialog;
}

class DatbaseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatbaseSettingsDialog(QWidget *parent = nullptr);
    ~DatbaseSettingsDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DatbaseSettingsDialog *ui;
};

#endif // DATBASESETTINGSDIALOG_H
