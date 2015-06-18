#ifndef STATICESW_H
#define STATICESW_H

#include <QDialog>

namespace Ui {
class staticesw;
}

class staticesw : public QDialog
{
    Q_OBJECT

public:
    explicit staticesw(QWidget *parent = 0);
    ~staticesw();

private slots:
    void on_pushButton_clicked();

private:
    Ui::staticesw *ui;
};

#endif // STATICESW_H
