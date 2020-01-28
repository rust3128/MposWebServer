#ifndef DATBASESETTINGSDIALOG_H
#define DATBASESETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class DatbaseSettingsDialog;
}

class DatbaseSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatbaseSettingsDialog(QSettings *set, QWidget *parent = nullptr);
    ~DatbaseSettingsDialog();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::DatbaseSettingsDialog *ui;
    QSettings *dbSettings;
};

#endif // DATBASESETTINGSDIALOG_H
