#include "vipupdate.h"
#include "ui_vipupdate.h"
#include "bank.h"
#include <qmessagebox.h>

vipupdate::vipupdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipupdate)
{
    ui->setupUi(this);
}

vipupdate::~vipupdate()
{
    delete ui;
}

void vipupdate::on_pushButton_clicked()
{
    this->close();
}

void vipupdate::on_pushButton_2_clicked()//更新一个vip客户
{
    customer a,temp[10000],b;
    FILE *fptr;
    if((fptr=fopen("vip.dat","r+b"))==NULL){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开vip客户资料！"),QMessageBox::Yes);
    }
    else{
        QByteArray temps;
        char* tempstr;
        temps=ui->name->text().toLatin1();
        tempstr=temps.data();
        strcpy(a.name,tempstr);
        temps=ui->id->text().toLatin1();
        tempstr=temps.data();
        strcpy(a.ID,tempstr);
        a.account=ui->account->text().toInt();
        rewind(fptr);
        fread(&b,sizeof(customer),1,fptr);
        int i=0;
        while(!feof(fptr)){
            if(strcmp(b.name,a.name)){
                temp[i++]=b;
            }
            else{
                temp[i++]=a;
            }
            fread(&b,sizeof(customer),1,fptr);
        }
        fclose(fptr);
        if((fptr=fopen("vip.dat","w"))==NULL){
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开vip客户资料！"),QMessageBox::Yes);
        }
        else{
            fwrite(temp,sizeof(customer),i,fptr);
            fclose(fptr);
            this->close();
            QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("VIP客户更新成功！"),QMessageBox::Yes);
        }
    }
}
