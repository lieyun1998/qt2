#include "widget2.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget2 w;

   w.show();
    return a.exec();
}
