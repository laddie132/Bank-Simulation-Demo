#include "staticesw.h"
#include "ui_staticesw.h"
#include "bank.h"

extern int maxnumber,vmaxnumber;
extern tongji sta[8];

staticesw::staticesw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staticesw)
{
    ui->setupUi(this);
    statices();//输出统计结果文件
    int i;
    ui->tableWidget->setRowHeight(7,34);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    for(i=0;i<8;i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(sta[i].renshu)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(sta[i].shichang)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(sta[i].renshu==0?0:((float)sta[i].shichang/sta[i].renshu))));
    }
    ui->normalnum->setDigitCount(3);
    ui->vipnumber->setDigitCount(3);
    ui->normalnum->display(maxnumber+1);
    ui->vipnumber->display(vmaxnumber+1);
}

staticesw::~staticesw()
{
    delete ui;
}

void staticesw::on_pushButton_clicked()
{
    this->close();
}
