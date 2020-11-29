#include "dialog.h"
#include "ui_dialog.h"
#include "widget2.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    windows_init();

    connect(ui->widget, &QCustomPlot::mouseMove, this, &Dialog::onMouseMove);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::onMouseMove(QMouseEvent *event)
{

        QCustomPlot* customPlot = qobject_cast<QCustomPlot*>(sender());
        double x = customPlot->xAxis->pixelToCoord(event->pos().x());
        double y = customPlot->yAxis->pixelToCoord(event->pos().y());
//        textItem->setText(QString("(%1, %2)").arg(x).arg(y));
//        textItem->position->setCoords(QPointF(x, y));
//        textItem->setFont(QFont(font().family(), 10));
        customPlot->replot();


}


void Dialog::windows_init()
{
   ui->widget->xAxis->setLabel("x");   //x轴的文字
   ui->widget->yAxis->setLabel("y");   //x轴的文字
  _pTimerUpdate = new QTimer(this);
  connect(_pTimerUpdate, SIGNAL(timeout()), this, SLOT(customsplot_slot()));

   m_CustomPlot = new QCustomPlot;


    ui->widget->xAxis->setRange(-11, 11);
    ui->widget->yAxis->setRange(-1, 1);

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);    //允许可缩放，移动
    QList < QCPAxis *>  xis;
    xis.append(ui->widget->xAxis);
    ui->widget->axisRect()->setRangeZoomAxes(xis);

}

void Dialog::on_pushButton_clicked()
{

    we=new Dialog;//示波器窗口
    this->hide();//隐藏

   // them=new Widget2;//主菜单切换回去
    _pTimerUpdate->stop();

    //them->show();

 }


void Dialog::customsplot_slot()
{
//    static QTime time(QTime::currentTime());        //获取当前时间
//    //计算新的数据点
//    double key = time.elapsed()/1000.0;

//     // 可变数组存放绘图的坐标的数据，分别存放x和y坐标的数据，101为数据长度

//    double i;
//    double y = sin(i);
//    qDebug()<<y;
    float save_data_x,save_data_y;

    ui->widget->addGraph();
    save_data_x=data_1;
    save_data_y=data_2;
    qDebug()<<save_data_x;
    ui->widget->graph(0)->setPen(QPen(Qt::red));
    ui->widget->graph(0)->addData(save_data_x,save_data_y);
    ui->widget->replot();       //画图重构
    ui->widget->xAxis->setRange(save_data_x, 100, Qt::AlignRight);        //设置x轴范围

   // qDebug()<<save_data_y;

    QList < QCPAxis *>  axis_x,axis_y,axis_xy;
    axis_x.append(ui->widget->xAxis);
    axis_y.append(ui->widget->yAxis);
    axis_xy.append(ui->widget->xAxis);
    axis_xy.append(ui->widget->yAxis);

    ui->widget->axisRect()->setRangeZoomAxes(axis_xy);

//    switch (ui->xcomboBox->currentIndex()) {
//    case 0:
//        save_data_x=data_2;
//        break;
//    case 1:
//        save_data_x=data_1;
//        break;
//    }

//    switch (ui->ycomboBox->currentIndex()) {
//    case 0:
//        save_data_y=data_1;
//        break;
//    case 1:
//        save_data_y=data_2;
//        break;
//    }

}


//画图开始
void Dialog::on_pushButton_2_clicked()
{
  _pTimerUpdate->start();

}



void Dialog::on_pushButton_3_clicked()
{
    _pTimerUpdate->stop();
}


void Dialog::checkbox_change()
{
    // 缩放轴
     QList < QCPAxis *>  axis_x,axis_y,axis_xy;
     axis_x.append(ui->widget->xAxis);
     axis_y.append(ui->widget->yAxis);
     axis_xy.append(ui->widget->xAxis);
     axis_xy.append(ui->widget->yAxis);


     ui->widget->axisRect()->setRangeZoomAxes(axis_xy);

}
