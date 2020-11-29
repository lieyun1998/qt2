#include "windows_out.h"
#include "ui_windows_out.h"
#include "widget2.h"

Windows_out::Windows_out(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Windows_out)
{
    ui->setupUi(this);
    win_init();

    move_on();

}

Windows_out::~Windows_out()
{
    delete ui;
}

void Windows_out::win_init()
{
    ui->lcdNumber_3->setDigitCount(4);    //显示位数
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);       //显示方式


    ui->lcdNumber_4->setDigitCount(4);    //显示位数
    ui->lcdNumber_4->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_4->setSegmentStyle(QLCDNumber::Flat);       //显示方式



}


void Windows_out::move_on()
{

  _pTimerUpdate = new QTimer(this);

  connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(judge_interllegence()));



}


void Windows_out::on_pushButton_clicked()
{

    this->hide();//隐藏
   _pTimerUpdate->stop();
}


void Windows_out::judge_interllegence()//输入数组
{

 if (data_3 ==2)
 {
   ui->label_judge->setText(tr("癌变组织"));


 }
else if (data_3 == 0)
 {


     ui->label_judge->setText(tr("正常组织"));

 }
 else
 {

   ui->label_judge->setText(tr("未知组织"));

 }


 ui->lcdNumber_4->display(data_2);
 ui->lcdNumber_3->display(data_1);

}

void Windows_out::on_pushButton_2_clicked()
{
     _pTimerUpdate->start();
}
