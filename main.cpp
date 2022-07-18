#include "HotPlot.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    HotPlot w1;
//    w1.resize(500, 400);
//    w1.show();
    return a.exec();
}
