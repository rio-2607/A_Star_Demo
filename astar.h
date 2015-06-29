/*
 * Author:rio
 * Time:2015-6-27-22-54
 * Description:A Star Algorithm implemented by C++
 */
#ifndef ASTAR_H
#define ASTAR_H
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Point {
    int x;
    int y;
    int f;//f=g+h
    int g;//从起点到自己的代价
    int h;//从自己到终点的代价
    struct Point *parent;//指向父亲的指针
    struct Point *self;//记录自己的地址

    //重载等号操作符
    bool operator==(const Point &point)
    {
        return this->x == point.x &&
               this->y == point.y;
    }

    //重载<操作符
    bool operator<(const Point &point)
    {
        return this->f < point.f;
    }

    friend ostream& operator<<(ostream &os,const Point &point)
    {
        os << "Point(x=" << point.x << ",y=" << point.y << ",f=" << point.f
           << ",g=" << point.g << ",h=" << point.g
           << ",parent=" << point.parent << ",self="
           << point.self << ")" << endl;
        return os;
    }
};

struct Coordinate{
    int x;
    int y;
};

class AStar
{
public:
    AStar();
    ~AStar();
    AStar(int start_x,int start_y,int end_x,int end_y,
          int (*data)[55],int x_number,int y_number);
    list<Coordinate> start();//开始A*算法,返回路径经过的所有点
private:
    list<Point> _opened_list;//开启列表
    list<Point> _closed_list;//关闭列表
    int _start_x;//起点的横坐标
    int _start_y;//起点纵坐标
    int _end_x;//终点横坐标
    int _end_y;//终点纵坐标
    int (*_data)[55];
    int _x_number;//横向点的个数
    int _y_number;//纵向点的个数

    vector<Point*> malloc_space;//存储new出来的空间

    ofstream _log;

    list<Coordinate> _a_star();
    //计算两个点之间的距离,采用的是曼哈顿距离
    int _get_distance(int start_x, int start_y, int end_x, int end_y);

    bool _is_shorter(const Point &point1,const Point &point2);//比较两个Point的大小，用在排序中

    void _print(const list<Point> &point);
};

#endif // ASTAR_H
