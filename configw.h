#ifndef CONFIGW_H
#define CONFIGW_H

#include <QDialog>

namespace Ui {
class configw;
}

class configw : public QDialog
{
    Q_OBJECT

public:
    explicit configw(QWidget *parent = 0);
    ~configw();

private slots:
    void on_pushButton_2_clicked();
    void initialize();

private:
    Ui::configw *ui;

};

#endif // CONFIGW_H
