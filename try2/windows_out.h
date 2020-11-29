#ifndef WINDOWS_OUT_H
#define WINDOWS_OUT_H

#include <QDialog>
#include <QTimer>

class Widget2;

namespace Ui {
class Windows_out;
}

class Windows_out : public QDialog
{
    Q_OBJECT

public:
    explicit Windows_out(QWidget *parent = nullptr);
    ~Windows_out();

private slots:
    void on_pushButton_clicked();
    void judge_interllegence();
    void win_init();
    void move_on();


    void on_pushButton_2_clicked();

private:
    Ui::Windows_out *ui;
    QTimer *_pTimerUpdate;
};

#endif // WINDOWS_OUT_H
