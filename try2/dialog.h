#ifndef DIALOG_H
#define DIALOG_H


#include <QDialog>
#include "qcustomplot.h"
#include <QMouseEvent>
//#include <widget2.h>
class Widget2;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


private slots:
    void onMouseMove(QMouseEvent* event);
    void on_pushButton_clicked();
    void customsplot_slot();
    void windows_init();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void checkbox_change();
private:
    Ui::Dialog *ui;
     QTimer *_pTimerUpdate;
     QCustomPlot *m_CustomPlot ;
     Dialog *we;
     Widget2 *them;

};



#endif // DIALOG_H
