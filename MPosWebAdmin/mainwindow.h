#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QSettings *set, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionDataBase_triggered();

private:
    Ui::MainWindow *ui;
    QSettings *appSettings;
};
#endif // MAINWINDOW_H
