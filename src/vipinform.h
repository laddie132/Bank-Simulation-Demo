#ifndef VIPINFORM_H
#define VIPINFORM_H

#include <QDialog>
#include "vipadd.h"
#include "vipdelete.h"
#include "vipupdate.h"

namespace Ui {
class vipinform;
}

class vipinform : public QDialog
{
    Q_OBJECT

public:
    explicit vipinform(QWidget *parent = 0);
    ~vipinform();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::vipinform *ui;
    vipadd* vipadd1;
    vipdelete* vipdelete1;
    vipupdate* vipupdate1;
};

#endif // VIPINFORM_H
