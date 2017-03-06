#ifndef VIPADD_H
#define VIPADD_H

#include <QDialog>

namespace Ui {
class vipadd;
}

class vipadd : public QDialog
{
    Q_OBJECT

public:
    explicit vipadd(QWidget *parent = 0);
    ~vipadd();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::vipadd *ui;
};

#endif // VIPADD_H
