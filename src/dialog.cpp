#include "dialog.h"
#include "ui_dialog.h"
#include "qmessagebox.h"
#include "qstring.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    if(this->ui->loginname->text().trimmed()== tr("admin") &&
      this->ui->loginpassword->text().trimmed()==tr("admin"))
      {
          this->close();
          accept();
      }
      else
      {
          QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Yes);
          this->ui->loginname->clear();
          this->ui->loginpassword->clear();
          this->ui->loginname->setFocus();
      }
}

void Dialog::on_pushButton_clicked()
{
    this->close();
    reject();
    exit(0);
}
