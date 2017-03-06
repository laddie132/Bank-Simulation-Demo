#ifndef VIPUPDATE_H
#define VIPUPDATE_H

#include <QDialog>

namespace Ui {
class vipupdate;
}

class vipupdate : public QDialog
{
    Q_OBJECT

public:
    explicit vipupdate(QWidget *parent = 0);
    ~vipupdate();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::vipupdate *ui;
};

#endif // VIPUPDATE_H
