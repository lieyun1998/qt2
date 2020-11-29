#ifndef WIDGET2_H
#define WIDGET2_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QtCore/qglobal.h>
#include <QFileDialog>

#include <QTableWidget>
#include "dialog.h"
#include "windows_out.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget2; }
QT_END_NAMESPACE
extern float  data_1,data_2;
extern int data_3;
class Dialog;
class Windows_out;

class Widget2 : public QWidget
{
    Q_OBJECT

    QTabWidget m_tabWidget;
public:
    Widget2(QWidget *parent = nullptr);
    ~Widget2();
    void serialport_init();
    void read_serialport();     //读串口数据
    void find_serialport();     //查找串口
    void insert_table(QString x1, QString x2, QString x3);

    QString Int_toHexStr(int dec);
    QByteArray QString_toHex(QString hexStr);
    QString formatInput(QString hexStr);
    char ConvertHexChar(char c);
private slots:
    void windows_init();
    void on_cancel_clicked();

    void on_put_in_clicked();

    void on_save_date_clicked();

    void on_com_activated(const QString &arg1);


    void on_open_serialport_clicked();

    void on_close_serialport_clicked();
    //double temperature;
   //  void read_serialport();



    void on_clear_date_clicked();

    void on_pushButton_clicked();

    void on_pushButton_disigner_clicked();

    void on_pushButton_v_clicked();



    void on_judge_push_clicked();

private:
    Ui::Widget2 *ui;
    Dialog *we;
    Windows_out *she;
    Widget2 *them;
   // QTimer dataTimer;           //时间
    QSerialPort *serialport;    //串口类
    double date;         //温度

};
#endif // WIDGET2_H
