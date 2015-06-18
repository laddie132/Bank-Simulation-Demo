#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "configw.h"
#include "vipinform.h"
#include "staticesw.h"

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
    void on_action_triggered();

    void on_action_4_triggered();

    void on_action_2_triggered();


    void on_outbank_clicked();

    void on_pausepush_clicked();

    void timeUpdate();
    void chTime();
    void print();

    void on_normalpush_clicked();

    void on_vippush_clicked();

    void on_towork_clicked();

    void on_action_3_triggered();



    void on_action_5_triggered();

    void on_action_6_triggered();

    void on_actionVIP_triggered();

private:
    Ui::MainWindow *ui;
    configw *configw1;
    QTimer *timer;
    vipinform* vipinform1;
};

#endif // MAINWINDOW_H
