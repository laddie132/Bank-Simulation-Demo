#ifndef VIPDELETE_H
#define VIPDELETE_H

#include <QDialog>

namespace Ui {
class vipdelete;
}

class vipdelete : public QDialog
{
    Q_OBJECT

public:
    explicit vipdelete(QWidget *parent = 0);
    ~vipdelete();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::vipdelete *ui;
};

#endif // VIPDELETE_H
