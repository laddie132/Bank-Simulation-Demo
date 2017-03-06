#include "vipinform.h"
#include "ui_vipinform.h"
#include <qbuttongroup.h>

vipinform::vipinform(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipinform)
{
    ui->setupUi(this);
    vipadd1=new vipadd;
    vipdelete1=new vipdelete;
    vipupdate1=new vipupdate;
}

vipinform::~vipinform()
{
    delete ui;
}

void vipinform::on_pushButton_clicked()
{
    this->close();
}

void vipinform::on_pushButton_2_clicked()//当选择一个功能（增加、删除或更新）时进入不同对话框
{
    QButtonGroup button;
    button.addButton(ui->addvip,1);
    button.addButton(ui->delevip,2);
    button.addButton(ui->updatevip,3);
    int i=button.checkedId();
    if(i==1){
        vipadd1->show();
        this->close();
    }
    else if(i==2){
        vipdelete1->show();
        this->close();
    }
    else if(i==3){
        vipupdate1->show();
        this->close();
    }
}
