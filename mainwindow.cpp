#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <QTime>
#include "bank.h"
#include <time.h>

extern int iswait,isclose,maxnumber,counts,vmaxnumber,vcounts,current,vcurrent,tactic,iswork;
extern time_t rest[8];
extern char vipid[20];
extern  int vis[8],cur[8],printselect[2];
int filetimes=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_4->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_5->setAttribute(Qt::WA_TranslucentBackground);
    ui->window->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->label_6->setAttribute(Qt::WA_TranslucentBackground);
    ui->window->setColumnWidth(0,90);
    ui->window->setColumnWidth(1,90);
    ui->window->setColumnWidth(2,85);
    ui->window->setColumnWidth(3,85);
    ui->window->setColumnWidth(4,85);
    ui->window->setColumnWidth(5,85);
    ui->window->setColumnWidth(6,85);
    ui->window->setColumnWidth(7,86);
    for(int i=0;i<8;i++)
    {
        ui->window->setRowHeight(i,40);
    }
    vipinform1=new vipinform;
    configw1=new configw;
    configw1->setWindowTitle(QString::fromLocal8Bit("配置"));
    configw1->exec();
    timeUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    this->close();
}

void MainWindow::on_action_4_triggered()
{
    QMessageBox::about(this,QString::fromLocal8Bit("关于"),
          QString::fromLocal8Bit(" <font color='red'>Virtual Bank System 2.5.0 (opensource)</font>"
                                " <br><br>Based on v 1.1.0 (32 bit)"

                                 "<br><br>Built on June 16 2015 at 21:47:12"

                                " <br><br>来自修订版本 2.4.0"
                                 "<br><br>项目主页：https://github.com/laddie132/Virtual-Bank-System-2.0"

                                 " <br><br>作者：L.Laddie团队  主页：http://laddie132.pe.hu/"

                               "  <br><br>Copyright 2015-2015 The Qt Company Ltd. All rights reserved." ));
}

void MainWindow::on_action_2_triggered()
{
    configw1->exec();//从配置文件中导入参数
}

void MainWindow::on_outbank_clicked()//发出下班信号
{
    iswait=1;
    QMessageBox::information(this,QString::fromLocal8Bit("下班"),QString::fromLocal8Bit("银行进入等待下班状态！"),QMessageBox::Yes);
}

void MainWindow::on_pausepush_clicked()//发出窗口暂停信号
{

    bool ok;
    int valueint=QInputDialog::getInt(this,QString::fromLocal8Bit("窗口暂停"),QString::fromLocal8Bit("请输入申请暂停的窗口编号"),1,1,8,1,&ok);
    if(ok){
      if(pause(valueint)) QMessageBox::information(this,QString::fromLocal8Bit("窗口暂停"),
            QString::number(valueint)+QString::fromLocal8Bit("号窗口将会暂停")+QString::number(rest[valueint-1])+QString("s"),QMessageBox::Yes);
      else QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("当前营业窗口数量过少，请稍后再申请暂停！"),QMessageBox::Yes);
    }
}

void MainWindow::timeUpdate()//定时器每一秒触发一次
{
    timer = new QTimer();
    ui->systime->setDigitCount(9);
    ui->systime->setSegmentStyle(QLCDNumber::Flat);
    ui->systime->display(QDateTime::currentDateTime().toString("hh:mm:ss"));
    connect(timer,SIGNAL(timeout()),this,SLOT(chTime()));
    timer->start(1000);
}

void MainWindow::chTime()
{
    ui->systime->display(QDateTime::currentDateTime().toString("hh:mm:ss"));//屏幕输出当前时间
    if(!isclose)
    {
        filetimes++;//每过一秒计时一次
        if(iswork)
        {
            work();
            if(filetimes>=10){//每10秒文件输出一次
                fileprint();
                filetimes=0;
            }
        }
        print();//每秒更新屏幕信息
    }
    else {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("营业厅已经下班，即将进入数据统计系统！"),QMessageBox::Yes);
        this->close();
        staticesw staticesw1;
        staticesw1.exec();
    }
}

void MainWindow::print()//更新屏幕信息
{

    for(int i=0;i<8;i++)
    {
        if(vis[i]==-1) ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("休息")));
        else if(cur[i]!=-1||vis[i]==1) ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("服务")));
        else ui->window->setItem(0,i,new QTableWidgetItem(QString::fromLocal8Bit("关闭")));
        if(cur[i]!=-1)
        {
            if(i<=1&&printselect[i]) ui->window->setItem(1,i,new QTableWidgetItem("V"+QString::number(cur[i]/10)+QString::number(cur[i]%10)));
            else ui->window->setItem(1,i,new QTableWidgetItem(QString::number(cur[i]/100)+QString::number((cur[i]%100)/10)+QString::number(cur[i]%10)));
        }
        else ui->window->setItem(1,i,new QTableWidgetItem(QString("")));
    }
    ui->maxnum->setDigitCount(3);
    ui->maxvnum->setDigitCount(3);
    ui->waitnum->setDigitCount(3);
    ui->waitvnum->setDigitCount(3);
    ui->maxnum->display(maxnumber==-1?0:QString::number(maxnumber/100)+QString::number((maxnumber%100)/10)+QString::number(maxnumber%10));
    ui->maxvnum->display(vmaxnumber==-1?0:QString::number(vmaxnumber/10)+QString::number(vmaxnumber%10));
    ui->waitnum->display(counts);
    ui->waitvnum->display(vcounts);
    if(!tactic) ui->tacticrec->setText(QString::fromLocal8Bit("VIP窗口顺便服务策略"));
    else ui->tacticrec->setText(QString::fromLocal8Bit("VIP窗口定向服务策略"));
    if(iswait){
        ui->isout->setText(QString::fromLocal8Bit("等待下班中。。。"));
        if(!counts&&!vcounts){
            int i,oks=1;
            for(i=0;i<8;i++)
            {
                if(cur[i]!=-1){
                    oks=0;
                    break;
                }
            }
            if(oks) isclose=1;
        }
    }
    else if(iswork) ui->isout->setText(QString::fromLocal8Bit("正常营业中。。。"));
    else ui->isout->setText(QString::fromLocal8Bit("等待上班中。。。"));
}

void MainWindow::on_normalpush_clicked()//普通客户到达抽号
{
    int oks=pnumber('G');
    if(oks==1) QMessageBox::information(this,QString::fromLocal8Bit("抽号"),
                         QString::fromLocal8Bit("您抽到的号码为")+QString::number(maxnumber/100)+QString::number((maxnumber%100)/10)+QString::number(maxnumber%10)+QString::fromLocal8Bit("，请排队等待叫号。"),QMessageBox::Yes);
    else if(oks==2) QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("营业厅正在下班，请明天再来！"),QMessageBox::Yes);
    else QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("到达队列最大等待长度，请稍后再来！"),QMessageBox::Yes);
}

void MainWindow::on_vippush_clicked()//vip客户到达抽号
{
    QString vipidstr=this->ui->vipidtext->text();
    QByteArray vipidstr2=vipidstr.toLatin1();
    char* vipids= vipidstr2.data();
    strcpy(vipid,vipids);
    int oks=pnumber('V');
    if(oks==0) QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("到达队列最大等待长度，请稍后再来！"),QMessageBox::Yes);
    else if(oks==-1) QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("请您输入正确的VIP客户ID！"),QMessageBox::Yes);
    else if(oks==1) QMessageBox::information(this,QString::fromLocal8Bit("抽号"),
                              QString::fromLocal8Bit("您抽到的号码为V")+QString::number(vmaxnumber/10)+QString::number(vmaxnumber%10)+QString::fromLocal8Bit("，请排队等待叫号。"),QMessageBox::Yes);
    else if(oks==-2) QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("无法打开vip客户资料！"),QMessageBox::Yes);
    else if(oks==2) QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("营业厅正在下班，请明天再来！"),QMessageBox::Yes);
}

void MainWindow::on_towork_clicked()//发出开始营业信号
{
    if(!iswork){
        iswork=1;
        QMessageBox::information(this,QString::fromLocal8Bit("营业"),QString::fromLocal8Bit("银行将开始营业！"),QMessageBox::Yes);
    }
    else QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("正在营业中，无法重复开启！"),QMessageBox::Yes);
}

void MainWindow::on_action_3_triggered()
{
    on_towork_clicked();
}



void MainWindow::on_action_5_triggered()
{
    on_pausepush_clicked();
}

void MainWindow::on_action_6_triggered()
{
    on_outbank_clicked();
}

void MainWindow::on_actionVIP_triggered()
{
    vipinform1->show();
}
