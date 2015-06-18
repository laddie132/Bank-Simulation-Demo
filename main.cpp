#include <time.h>
#include <QTime>
#include <qdir.h>
#include <qlabel.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qmovie.h>
#include <windows.h>
#include <QApplication>
#include "bank.h"
#include "dialog.h"
#include "mainwindow.h"

char ch,vipid[20];
tongji sta[8];//保存每个窗口统计结果
time_t cstart,start[8],end[8],rest[8],rstart[8];//end[8]保存每个客户服务时长
int MaxSeqLen=0,MinSec=0,MaxSec=0,MinRestSec=0,MaxRestSec=0,VIPSERVLen=0;
int vis[]={1,0,1,1,1,0,0,0}; //保存当前窗口"上班"或“关闭”状态或“休息”状态
int cur[]={-1,-1,-1,-1,-1,-1,-1,-1};//保存当前窗口服务客户编号
int printselect[2];//保存当前服务的是vip客户还是普通客户
int maxnumber=-1,counts=0,vmaxnumber=-1,vcounts=0,current=-1,vcurrent=-1,iswait=0,isclose=0,flag=1,tactic=0,iswork=0;

int main(int argc, char **argv)
{
    srand((int)time(NULL));
    memset(sta,0,sizeof(sta));
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("./image/bank.ico"));
    QMovie *movie;
    movie = new QMovie(":/image/start.gif");//设置启动动画
    QLabel *label=new QLabel ("", 0);
    label->setGeometry( 450, 150, 400, 300 );
    label->setWindowFlags(Qt::FramelessWindowHint);
    label->setMovie(movie);
    label->setScaledContents(true);
    movie->start();
    label->show();
    QTime t;
    t.start();
    while(t.elapsed()<5000)
    {
        QApplication::processEvents();
    }
    label->close();
    Dialog login;//设置登陆界面
    login.setWindowFlags(Qt::FramelessWindowHint);
    login.show();
    if(login.exec()==QDialog::Accepted){
        MainWindow w;//设置主界面
        w.setWindowTitle(QString::fromLocal8Bit("模拟银行系统"));
        w.show();
        return a.exec();
    }
    else if(login.exec()==QDialog::Rejected) exit(0);
    return a.exec();
}

