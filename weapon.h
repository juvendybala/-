#ifndef WEAPON_H
#define WEAPON_H
#include"config.h"
#include<QString>
#include<QRect>
class weapon
{
public:
    int x,y;
    QString picturepath;
    int speed;
    bool isfree;//true表示还未发射，false表示已发射
    QRect *rec;
    int type;//表示子弹射出方向，0为向左，1为向上，2为向右，3为向下
public:
    weapon();
    ~weapon();
    void updateposition();//每一帧更新坐标
};
class weapon1:public weapon
{
public:
    weapon1();
};
class weapon2:public weapon
{
  public:
    weapon2();
};
class weapon3:public weapon2
{
public:
    weapon3();
};
#endif // WEAPON_H
