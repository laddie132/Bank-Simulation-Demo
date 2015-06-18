#include "vipadd.h"
#include "ui_vipadd.h"
#include <qmessagebox.h>
#include "bank.h"

vipadd::vipadd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipadd)
{
    ui->setupUi(this);
}

vipadd::~vipadd()
{
    delete ui;
}

void vipadd::on_pushButton_clicked()
{
    this->close();
}

void vipadd::on_pushButton_2_clicked()//增加一个vip客户
{
    FILE *fptr;
    if((fptr=fopen("vip.dat","r+b"))==NULL){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开vip客户资料！"),QMessageBox::Yes);
    }
    else{
        customer a;
        QByteArray temp;
        char* tempstr;
        temp=ui->name->text().toLatin1();
        tempstr=temp.data();
        strcpy(a.name,tempstr);
        temp=ui->id->text().toLatin1();
        tempstr=temp.data();
        strcpy(a.ID,tempstr);
        a.account=ui->account->text().toInt();
        fseek(fptr,0L,SEEK_END);
        fwrite(&a,sizeof(customer),1,fptr);
        fclose(fptr);
        this->close();
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("VIP客户增加成功！"),QMessageBox::Yes);
    }
}
