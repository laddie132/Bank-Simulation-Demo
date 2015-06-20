//从config.ini配置文件中读入银行配置信息//

#include <stdio.h>
#include <stdlib.h>
#include "qstring.h"
#include "qmessagebox.h"
#include "configw.h"
#include "ui_configw.h"

extern int MaxSeqLen,MinSec,MaxSec,MinRestSec,MaxRestSec,VIPSERVLen,tactic;

configw::configw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::configw)
{
    ui->setupUi(this);

    configw::initialize();
    ui->maxrest->setAttribute(Qt::WA_TranslucentBackground);
    ui->minrest->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxsec->setAttribute(Qt::WA_TranslucentBackground);
    ui->maxseqlen->setAttribute(Qt::WA_TranslucentBackground);
    ui->minsec->setAttribute(Qt::WA_TranslucentBackground);
    ui->vipservlen->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_8->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_9->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_10->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_11->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_12->setAttribute(Qt::WA_TranslucentBackground);
}

configw::~configw()
{
    delete ui;
}

void configw::on_pushButton_2_clicked()
{
    FILE *fptr;
    if ((fptr=fopen("config.ini","w"))==NULL){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开文件config.ini"),QMessageBox::Yes);
        exit(0);
    }
    else{
        bool ok;
        QString maxseqlens=ui->maxseqlen_2->text();
        QString minrests=ui->minrest_2->text();
        QString maxrests=ui->maxrest_2->text();
        QString minsecs=ui->minsec_2->text();
        QString maxsecs=ui->maxsec_2->text();
        QString vipservlens=ui->vipservlen_2->text();
        MaxSeqLen=maxseqlens.toInt(&ok);
        MinRestSec=minrests.toInt(&ok);
        MaxRestSec=maxrests.toInt(&ok);
        MinSec=minsecs.toInt(&ok);
        MaxSec=maxsecs.toInt(&ok);
        VIPSERVLen=vipservlens.toInt(&ok);
        fprintf(fptr,"[MaxSeqLen]%d\n",MaxSeqLen);
        fprintf(fptr,"[MinSec]%d\n",MinSec);
        fprintf(fptr,"[MaxSec]%d\n",MaxSec);
        fprintf(fptr,"[MinRestSec]%d\n",MinRestSec);
        fprintf(fptr,"[MaxRestSec]%d\n",MaxRestSec);
        fprintf(fptr,"[VIPSERVLen]%d",VIPSERVLen);
        fclose(fptr);
    }
    int rows=ui->comboBox->currentIndex();
    if(rows==0) tactic=0;
    else tactic=1;
    this->close();
    return ;
}

void configw::initialize()
{
    int i,flag=1;
    FILE *fptr;
    char ch[20],ch2[20];
    if ((fptr=fopen("config.ini","r"))==NULL){
        QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开文件config.ini"),QMessageBox::Yes);
        reject();
    }
    else{
        while(!feof(fptr)){
            flag=1;
            fgets(ch,sizeof(ch),fptr);
            for(i=0;ch[i]!='\n'&&ch[i]!='\0';i++)
            {
                if(ch[i]!=']'&&flag==1){
                    ch2[i]=ch[i];
                    continue;
                }
                if(ch[i]==']'){
                    flag=0;
                    ch2[i]=0;
                    continue;
                }
                if(!strcmp(ch2,"[MaxSeqLen")) MaxSeqLen=MaxSeqLen*10+ch[i]-'0';
                else if(!strcmp(ch2,"[MinSec")) MinSec=MinSec*10+ch[i]-'0';
                else if(!strcmp(ch2,"[MaxSec")) MaxSec=MaxSec*10+ch[i]-'0';
                else if(!strcmp(ch2,"[MinRestSec")) MinRestSec=MinRestSec*10+ch[i]-'0';
                else if(!strcmp(ch2,"[MaxRestSec")) MaxRestSec=MaxRestSec*10+ch[i]-'0';
                else if(!strcmp(ch2,"[VIPSERVLen")) VIPSERVLen=VIPSERVLen*10+ch[i]-'0';
            }
        }
    }
    fclose(fptr);
    this->ui->maxrest_2->clear();
    this->ui->maxsec_2->clear();
    this->ui->maxseqlen_2->clear();
    this->ui->minrest_2->clear();
    this->ui->minsec_2->clear();
    this->ui->vipservlen_2->clear();
    this->ui->maxseqlen_2->setText( QString::number(MaxSeqLen, 10));
    this->ui->maxrest_2->setText( QString::number(MaxRestSec, 10));
    this->ui->maxsec_2->setText( QString::number(MaxSec, 10));
    this->ui->minrest_2->setText( QString::number(MinRestSec, 10));
    this->ui->minsec_2->setText( QString::number(MinSec, 10));
    this->ui->vipservlen_2->setText( QString::number(VIPSERVLen, 10));
    this->ui->maxseqlen_2->setFocus();
    return;
}

void configw::on_pushButton_4_clicked()
{
    this->close();
}
