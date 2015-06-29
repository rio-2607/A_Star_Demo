#include "astar.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;
AStar::AStar()
{

}

AStar::~AStar()
{
    _log.close();
    //避免内存泄露，释放分配的内存
    for(unsigned int i = 0;i < malloc_space.size();++i)
        delete(malloc_space[i]);
}

AStar::AStar(int start_x, int start_y, int end_x, int end_y,
             int (*data)[55], int x_number, int y_number)
{
    _start_x = start_x;
    _start_y = start_y;
    _end_x = end_x;
    _end_y = end_y;
    _data = data;
    _x_number = x_number;
    _y_number = y_number;

    _log.open("log.txt");
}


list<Coordinate> AStar::start()
{
    list<Coordinate> r = _a_star();
    return r;
}


list<Coordinate> AStar::_a_star()
{
    //g表示从起点到自己的代价，h表示从自己到终点的代价
    //把起始点放入到开启列表中
    Point *start_point = new Point();
    malloc_space.push_back(start_point);
    start_point->x = _start_x;
    start_point->y = _start_y;
    start_point->g = 0;
    start_point->h = _get_distance(_start_x,_start_y,_end_x,_end_y);
    start_point->f = start_point->h + start_point->g;
    start_point->parent = NULL;//起始点的父节点为空
    start_point->self = start_point;//自己的地址

    _opened_list.push_back(*start_point);//把起始点放进开启列表中

    while(0 != _opened_list.size())
    {
        _opened_list.sort();//把开启列表中的数据排序

        list<Point>::iterator first = _opened_list.begin();
        Point first_point = *first;//获取列表中的第一个数据


        _closed_list.push_back(first_point);//把这个数据放入关闭列表中
        _opened_list.erase(first);//删除这个元素

        if(first_point.x == _end_x && first_point.y == _end_y)//如果当前的数据是终点，则结束
            break;
        //把当前点的领域内的点全部放入开启列表中
        int top_left_x = first_point.x == 0 ? 0 : first_point.x - 1;
        int top_left_y = first_point.y == 0 ? 0 : first_point.y - 1;
        int bottom_right_x = first_point.x >= _x_number-1 ? first_point.x : first_point.x + 1;
        int bottom_right_y = first_point.y >= _y_number-1 ? first_point.y : first_point.y + 1;

        for(int i = top_left_x;i <= bottom_right_x;++i)
        {
            for(int j = top_left_y;j <= bottom_right_y;++j)
            {
                if(i != first_point.x ||  j != first_point.y)
                {
                    if(_data[j][i] != 1)//1表示该点是障碍物,如果不是障碍物
                    {
                        Point point;
                        point.x = i;
                        point.y = j;

                        list<Point>::iterator iter = find(_opened_list.begin(),_opened_list.end(),point);
                        if(iter != _opened_list.end())
                        {
                            //已经在开启列表中
                            Point pp = *iter;
                            int d1 = _get_distance(first_point.x,first_point.y,
                                                   _start_x,_start_y);
                            int d2 = _get_distance(first_point.x,first_point.y,i,j);
                            if(d1 + d2 < pp.g)
                            {
                                pp.parent = first_point.self;
                                pp.g = d1 + d2;
                            }
                            continue;
                        }

                        iter = find(_closed_list.begin(),_closed_list.end(),point);
                        if(iter != _closed_list.end())
                        {
                            //已经在关闭列表中
                            Point pp = *iter;
                            int d1 = _get_distance(first_point.x,first_point.y,
                                                   _start_x,_start_y);
                            int d2 = _get_distance(first_point.x,first_point.y,i,j);
                            if(d1 + d2 < pp.g)
                            {
                                pp.parent = first_point.self;
                                pp.g = d1 + d2;
                            }
                            continue;
                        }

                        //既不在开启列表中也不在关闭列表中
                        Point *p = new Point();
                        p->x = i;
                        p->y = j;
                        p->h = _get_distance(i,j,_end_x,_end_y);
                        p->g = _get_distance(_start_x,_start_y,i,j);
                        p->f = p->g + p->h;
                        p->parent = first_point.self;
                        p->self = p;
                        //放入到 开启列表 中去
                        _opened_list.push_back(*p);

                        malloc_space.push_back(p);
                    }
                }
            }
        }

    }
    list<Coordinate> result;
    list<Point>::const_iterator iter = --_closed_list.end();
    Point p = *iter;
    while(p.parent != NULL)
    {
        Coordinate c;
        c.x = p.x;
        c.y = p.y;
        result.push_front(c);
        p = *(p.parent);
    }
    return result;
}


/*
 * 计算两个点之前的距离，采用的是曼哈顿距离
 * distance = |start.x-end.x| + |start.y-end.y|
 */
int AStar::_get_distance(int start_x, int start_y, int end_x, int end_y)
{
    return abs(end_x-start_x) + abs(end_y-start_y);
}



bool AStar::_is_shorter(const Point &point1, const Point &point2)
{
    return point1.f < point2.f;
}



void AStar::_print(const list<Point> &point)
{
    list<Point>::const_iterator i = point.begin();
    while(i != point.end())
    {
        _log << *i;
        ++i;
    }
    _log << endl;
}

