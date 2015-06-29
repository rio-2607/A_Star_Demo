/*
 * Author:rio
 * Time:2015-6-27-21-34
 * Description:A little programe wroten by Qt and C++ to demo A* Algorithm
 */
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
