#include "widget2.h"
#include "ui_widget2.h"
#include <QDebug>
#include <QDateTime>
#include <QPlainTextEdit>
#include "dialog.h"
#include "windows_out.h"

float  data_1,data_2;
int data_3;
Widget2::Widget2(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget2)
{

    ui->setupUi(this);
    windows_init();
    serialport = new QSerialPort;
    setWindowTitle(tr("upper_computer"));

}

// 界面初始化
void Widget2::windows_init()
{
//控件初始化
    ui->close_serialport->setEnabled(false);


// lcd 初始化
    ui->lcdNumber->setDigitCount(4);    //显示位数
    ui->lcdNumber->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);       //显示方式

    ui->lcdNumber_2->setDigitCount(4);    //显示位数
    ui->lcdNumber_2->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);       //显示方式

    ui->lcdNumber_3->setDigitCount(4);    //显示位数
    ui->lcdNumber_3->setMode(QLCDNumber::Dec);    //十进制
    ui->lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);       //显示方式
// 表格初始化
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setAlternatingRowColors(true);     //设置隔行变颜色
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //选中整行


    //设置表头
    QStringList header;
    header<<tr("压力")<<tr("阻抗值")<<tr("结果");
    ui->tableWidget->setHorizontalHeaderLabels(header);

//设置弹出框的大小尺寸
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,70);
    ui->tableWidget->setColumnWidth(2,70);
   // ui->textBrowser->setStyleSheet("background:transparent;border-width:0;border-style:outset");

//    setAutoFillBackground(true);
//    QPalette palette;
//    QPixmap pixmap("F:/QT_PROJECT/try2/ background.png");
//    palette.setBrush(backgroundRole(),QBrush(pixmap));
//    this->setPalette(palette); // 图片尺寸要和widget等大小 如果图片尺寸小  就会重复排列


}
Widget2::~Widget2()
{
    delete ui,serialport;
}

//关闭
void Widget2::on_cancel_clicked()
{
    this->close();
}

//发送按钮
void Widget2::on_put_in_clicked()
{
//    QString data=ui->line_put->text();
//    int celerlate=data.toInt();
//    QString password=ui->line_pass->text();
//    int diatance = password.toInt();
//    if ((celerlate>0)&&(diatance>=0))
//    {
//     //添加发送指令
//     qDebug()<<"发送成功"<<endl;


//    }
//    else
//    {

//    qDebug()<<"发送失败"<<endl;
//    }
    //发送位移
    if(this->ui->up_dir->isChecked())
    {
        //00为上向标志位
        serialport->write(QString_toHex("0a"));
        int decInput = this->ui->line_pass->text().toInt();
        QString hexStr = Int_toHexStr(decInput);
        serialport->write(QString_toHex(formatInput(hexStr)));
    }
    else
    {
        //03为向下标志位
        serialport->write(QString_toHex("0d"));
        int decInput = this->ui->line_pass->text().toInt();
        QString hexStr = Int_toHexStr(decInput);
        serialport->write(QString_toHex(formatInput(hexStr)));


    }
    //发送速度
    serialport->write(QString_toHex("cf"));
    int decInput_1 = this->ui->line_put->text().toInt();
    QString hexStr_1 = Int_toHexStr(decInput_1);
    serialport->write(QString_toHex(formatInput(hexStr_1)));

}

//保存文件
void Widget2::on_save_date_clicked()
{
    // 获取文件目录
    QString filename = QFileDialog::getExistingDirectory(this,tr("file dialog"),"C:");
   //文件名
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString date = time.toString("MM.dd.hh.mm.ss"); //设置显示格式
    filename += date;
    filename += ".txt";
    //文件对象
    QFile file(filename);
    //只写方式打开
    if(!file.open(QFile::WriteOnly | QFile::Text))      //只写方式
    {
        QMessageBox::warning(this,tr("double file edit"),tr("no write ").arg(filename).arg(file.errorString()));
        return ;
    }
    //文件流对象
    QTextStream out(&file);

    //遍历数据
    int romcount = ui->tableWidget->rowCount();     //获取总行数
    for(int i = 0; i < romcount; i++)
    {
        QString rowstring;
        for(int j = 0; j < 3; j++)
        {
            rowstring += ui->tableWidget->item(i,j)->text();
            rowstring += "  ";
        }
        rowstring += "\n";
        out << rowstring;
    }

    file.close();
}


//端口号
void Widget2::on_com_activated(const QString &arg1)
{

}



void Widget2::on_open_serialport_clicked()
{
    find_serialport();

    if(ui->com->count() != 0)   //不为空时
        //初始化串口
            serialport->setPortName(ui->com->currentText());        //设置串口名
            if(serialport->open(QIODevice::ReadWrite))              //打开串口成功
            {
//               serialport->setBaudRate(115200);       //设置波特率
//               serialport->setDataBits(QSerialPort::Data8);
//               serialport->setParity(QSerialPort::NoParity);
//               serialport->setStopBits(QSerialPort::OneStop);
               //serialport->setStopBits(QSerialPort::TwoStop);
               serialport->setFlowControl(QSerialPort::NoFlowControl);     //设置流控制
               /*--------baud rate-----------------------------*/
               switch (ui->cmb_baud_rate->currentIndex()) {
               case 0:
                    serialport->setBaudRate(QSerialPort::Baud115200);
                   break;
               case 1:
                    serialport->setBaudRate(QSerialPort::Baud57600);
                   break;
               case 2:
                    serialport->setBaudRate(QSerialPort::Baud38400);
                   break;
               case 3:
                    serialport->setBaudRate(QSerialPort::Baud19200);
                   break;
               case 4:
                    serialport->setBaudRate(QSerialPort::Baud9600);
                   break;
               case 5:
                    serialport->setBaudRate(QSerialPort::Baud4800);
                   break;
               case 6:
                    serialport->setBaudRate(QSerialPort::Baud2400);
                   break;
               default:
                   serialport->setBaudRate(QSerialPort::Baud1200);
                   break;
               }

               //设置数据位
               switch(ui->data_bit->currentIndex())
               {
                   case 0:
                       serialport->setDataBits(QSerialPort::Data8);
                       break;
                   case 1:
                       serialport->setDataBits(QSerialPort::Data7);
                       break;
                   case 2:
                       serialport->setDataBits(QSerialPort::Data6);
                       break;
                   case 3:
                       serialport->setDataBits(QSerialPort::Data5);
                       break;
                   default:
                       break;
               }

               //设置校验位
               switch(this->ui->check_bit->currentIndex())
               {
                   case 0:
                       serialport->setParity(QSerialPort::NoParity);
                       break;
                   case 1:
                       serialport->setParity(QSerialPort::OddParity);
                       break;
                   case 2:
                       serialport->setParity(QSerialPort::EvenParity);
                   default:
                       break;
               }

               //设置停止位
               switch(this->ui->stop_bit->currentIndex())
               {
                   case 0:
                       serialport->setStopBits(QSerialPort::OneStop);
                       break;
                   case 1:
                       serialport->setStopBits(QSerialPort::OneAndHalfStop);
                   case 2:
                       break;
                       serialport->setStopBits(QSerialPort::TwoStop);
                       break;
                   default:
                       break;
               }
               QObject::connect(serialport, &QSerialPort::readyRead, this, &Widget2::read_serialport);    //读数据

              //QObject::connect(serialport,SIGNAL(readyRead()),this,SLOT(read_serialport()));
                //控件可见设置
               ui->put_in->setEnabled(true);
               ui->close_serialport->setEnabled(true);
               ui->open_serialport->setEnabled(false);
               ui->label_state->setText(tr("串口打开成功"));

            }

            else    //打开失败提示
            {
                QMessageBox::information(this,tr("Erro"),tr("Open the failure"),QMessageBox::Ok);
                ui->label_state->setText(tr("串口未打开"));
            }


}

 //读串口数据
//数据格式：01 十一位数据 oa
void Widget2::read_serialport()
{
    static int r=0,point=0,point1=0,lcd;

    unsigned char yaw1[4],x1[5],y1[4];
    float yaw,x_1;
    bool ok0;
    QByteArray buf;
    QString measure_late[11] ;
    QString save_data[2];
   //转换成hex的同时，加入“，”，以便进行数据分开处理
    buf = serialport->readAll().toHex(',');
    QString rt=tr(buf);//转换
    //以逗号为分格符，将数据进行拆开处理
    //放入list中，下一步进行遍历读包，区别帧头帧尾
    QStringList list= rt.split(',');
     //qDebug()<<x1[4];
    for(int i = 0; i< list.size();++i)
    {
        QString tmp = list.at(i);

        if (tmp=="01")
        {
           point=1;
           r=0;

        }
        if (point==1)
        {
            if (r==11)
            {

                point=0;
                r=0;

            }
            else{
            measure_late[r++]=  list.at(i);//得到十六进制字符
            }
            if (measure_late[10]=="0a")
            {
            point1=1;
             }
            else
            {

             point1=0;
            }



        }

    }
    if (point1==1)
    {

     //float为32为，将4个八位数据 unsigned char复制，就可得出float原始数据
     yaw1[0]=measure_late[1].toInt(&ok0,16);
     yaw1[1]=measure_late[2].toInt(&ok0,16);
     yaw1[2]=measure_late[3].toInt(&ok0,16);
     yaw1[3]=measure_late[4].toInt(&ok0,16);

     x1[0]=measure_late[5].toInt(&ok0,16);
     x1[1]=measure_late[6].toInt(&ok0,16);
     x1[2]=measure_late[7].toInt(&ok0,16);
     x1[3]=measure_late[8].toInt(&ok0,16);


     x1[4] = measure_late[9].toInt(&ok0,16);//结果传递
   //qDebug()<<measure_late[9];

     data_3=x1[4];

     memcpy_s(&yaw , sizeof(float) , yaw1 , 4);
     memcpy_s(&x_1 , sizeof(float) , x1 , 4);

     QString yaw_text,x12,y12;

     yaw_text = QString("%1").arg(yaw);

     x12= QString("%1").arg(x_1);

     //全局变量用于示波器的使用
     data_1=yaw;//压力
     data_2=x_1;//阻抗


     y12= QString("%1").arg(x1[4] );
     insert_table(yaw_text,x12,y12);//显示数据窗口数据更新
    // qDebug()<<data_2;
    // lcd= int (data_2);
   // ui->lcdNumber_2->display(x1);
    ui->lcdNumber_3->display(data_2);
    ui->lcdNumber->display(data_1);
    ui->lcdNumber_2->display(data_3);
   // qDebug()<<data_2;
    }



}


void Widget2::find_serialport()
{
    //查找可用的串口
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);   //设置串口
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->com->addItem(serial.portName());        //显示串口name
            serial.close();
        }
    }
}

void Widget2::on_close_serialport_clicked()
{
    //关闭串口
    serialport->clear();        //清空缓存区
    serialport->close();        //关闭串口

    ui->put_in->setEnabled(false);


    ui->open_serialport->setEnabled(true);
    ui->close_serialport->setEnabled(false);
    ui->label_state->setText(tr("串口 关闭"));




}

// 插入数据
void Widget2::insert_table(QString x1, QString x2, QString x3)
{
    update();
    int row_count = ui->tableWidget->rowCount();   //获取总行数
    ui->tableWidget->insertRow(row_count);         //插入行
    QTableWidgetItem *item0 = new QTableWidgetItem();
    QTableWidgetItem *item1 = new QTableWidgetItem();
    QTableWidgetItem *item2 = new QTableWidgetItem();

    item0->setText(x1);
    item1->setText(x2);
    item2->setText(x3);


    ui->tableWidget->setItem(row_count,0,item0);
    ui->tableWidget->setItem(row_count,1,item1);
    ui->tableWidget->setItem(row_count,2,item2);

}

void Widget2::on_clear_date_clicked()
{

    while(ui->tableWidget->rowCount())
    {
        ui->tableWidget->removeRow(0);
    }

}

void Widget2::on_pushButton_clicked()
{

    we=new Dialog;//示波器窗口
    we->show();


}

//作者查看
void Widget2::on_pushButton_disigner_clicked()
{

    QMessageBox::about(this, "disigner", "yu li");

}
//版本号
void Widget2::on_pushButton_v_clicked()
{
    QMessageBox::question(this, "版本号", "v1.1", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}


//功能函数
//将十进制int转换为十六进制字符串
QString Widget2::Int_toHexStr(int dec)
{
    //保证数据在两帧范围内
    if(dec > 65535)
    {
        QMessageBox::information(this, "警告", "输入超出规定范围（input < 65535）");
        return "0";
    }
    QString hexStr;
    int temp = dec / 16;
    int left = dec % 16;
    if(temp > 0)
        hexStr += Int_toHexStr(temp);
    if(left < 10)
        hexStr += (left + '0');
    else
        hexStr += ('A' + left - 10);
    return hexStr;
}

//将输入格式化，补满四位：0XFFFF
QString Widget2::formatInput(QString hexStr)
{
    int strlen = hexStr.length();
    switch(strlen)
    {
        case 0:
            hexStr = "0000";
            break;
        case 1:
            hexStr = "000" + hexStr;
            break;
        case 2:
            hexStr = "00" + hexStr;
            break;
        case 3:
            hexStr = "0" + hexStr;
            break;
        case 4:
            hexStr = hexStr;
            break;
        default:
            break;
    }
    return hexStr;
}

//字符串转Hex(QByteArray)类型
QByteArray Widget2::QString_toHex(QString hexStr)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = hexStr.length();
    senddata.resize(len/2);
    char lstr, hstr;
    for(int i = 0; i < len; )
    {
        //将第一个不为' '的字符赋给hstr;
        hstr = hexStr[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        //当i >= len时，跳出循环
        if(i >= len)
            break;
        //当i < len时，将下一个字符赋值给lstr;
        lstr = hexStr[i].toLatin1();
        //将hstr和lstr转换为0-15的对应数值
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        //
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata * 16 + lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}

//将单个字符串转换为hex
//0-F -> 0-15
char Widget2::ConvertHexChar(char c)
{
    if((c >= '0') && (c <= '9'))
        return c - 0x30;
    else if((c >= 'A') && (c <= 'F'))
        return c - 'A' + 10;//'A' = 65;
    else if((c >= 'a') && (c <= 'f'))
        return c - 'a' + 10;
    else
        return -1;
}

void Widget2::on_judge_push_clicked()
{

    she= new Windows_out;//示波器窗口
    she->show();

}
