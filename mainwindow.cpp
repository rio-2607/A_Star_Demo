#include "mainwindow.h"
#include <QPainter>
#include <QDebug>
#include "astar.h"


#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    point_number_x = 35;
    point_number_y = 55;
    point_size = 15;
    setWindowTitle("A*Demo");

    //初始化data数据
    for(int i = 0;i < point_number_x;++i)
        for(int j = 0;j < point_number_y;++j)
            data[i][j] = 0;

    resize(point_number_y * point_size + 10,
           point_number_x * point_size + 10);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    //根据不同的角色，绘制不同的颜色
    for(int i = 0;i < point_number_x;++i)
    {
        for(int j = 0;j < point_number_y;++j)
        {
            QRect rect = __get_rect(j,i);
            if(2 == data[i][j])//如果为2，则表示该点为计算出来的路径的一部分，用红色表示
                painter.fillRect(rect,Qt::red);
            else if(1 == data[i][j])//如果是1，则表示是障碍物，禁止通过,用蓝色来表示
                painter.fillRect(rect,Qt::blue);
            else if(3 == data[i][j])//如果是3，则表示是起点或者终点,用灰色来表示
                painter.fillRect(rect,Qt::green);
            else //否则就是可以通过的点
                painter.fillRect(rect,Qt::lightGray);
        }
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint index = __get_point(event->pos());
    if(Qt::LeftButton == event->button())
        data[index.y()][index.x()] = 1;//点击左键绘制障碍物
    else if(Qt::RightButton == event->button())//点击右键取消障碍物
        data[index.y()][index.x()] = 0;
    update();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPoint index = __get_point(event->pos());
    if(Qt::LeftButton == event->button())
    {
        data[index.y()][index.x()] = 3;//双击左键绘起点和终点
        point.push_back(index.x());
        point.push_back(index.y());
    }
    update();
}

/*
 * 根据当前的点的坐标获取当前点所在矩形区域的x,y的索引
 */
QPoint MainWindow::__get_point(const QPoint &point)
{
    int x = point_number_x-1;
    int y = point_number_y-1;
    for(int i = 0;i <= point_number_y;++i)
    {
        if(i * point_size > point.x())
        {
            x  = i - 1;
            break;
        }
    }
    for(int i = 0;i <= point_number_x;++i)
    {
        if(i * point_size > point.y())
        {
            y  = i - 1;
            break;
        }
    }

    return QPoint(x,y);
}


QRect MainWindow::__get_rect(int x,int y)
{
    return QRect(x * point_size,y * point_size,point_size-2,point_size-2);
}



void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key_Space == event->key())
    {
        AStar a(point[0],point[1],point[2],point[3],
                data,point_number_x,point_number_y);
        list<Coordinate> r = a.start();
        list<Coordinate>::const_iterator iter = r.begin();
        while(iter != r.end())
        {
            Coordinate c = *iter;
            data[c.y][c.x] = 2;
            ++iter;
        }

        update();
    }
}
