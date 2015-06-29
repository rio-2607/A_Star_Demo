#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPoint>
#include <QRect>
#include <QKeyEvent>
#include <vector>
using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    int point_number_x;
    int point_number_y;
    int point_size;

    vector<int> point;

    int data[35][55];//用来保存每个坐标的数据

private:
    QPoint __get_point(const QPoint &point);//根据当前的点的坐标获取当前所在矩形区域的索引
    QRect __get_rect(int x,int y);//通过x,y的坐标获取改点所在的rect区域
};

#endif // MAINWINDOW_H
