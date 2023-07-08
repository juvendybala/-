#ifndef DROP_H
#define DROP_H
#include<QRect>
#include<QString>
#include"config.h"
class drop
{
public:

    int x,y;
    QRect *rec;//判断碰撞
    QString picturepath;
    bool isexist;//判断是否存在
public:
    drop();
    ~drop();
};
class drop1:public drop
{
public:
    drop1();
};
class drop2:public drop
{
public:
    drop2();
};
class drop3:public drop
{
public:
    drop3();
};
#endif // DROP_H
