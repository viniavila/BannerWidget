#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_normal_clicked();
    void on_info_clicked();
    void on_critical_clicked();
    void on_inverted_clicked();
    void on_warning_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
