#ifndef ENEMY_H
#define ENEMY_H
#include<QRect>
#include<QString>
#include<QDebug>
#include"config.h"
#include"character.h"
#include"block.h"
#include<ctime>
class enemy
{
public:
    int health;//记录原有生命值
    int curhealth;//记录当前生命值
    int attack;
    int speed;
    bool islive;//判断是否死亡
    QString picturepath;
    int x,y;
    QRect *rec;
public:
    enemy(int,int,int);
};
class enemy1:public enemy
{
public:
    enemy1();
    void updateposition(character*,block1**);
};
//todo:远程敌人:可以在边界移动并发射子弹
class enemy2:public enemy
{
public:
    int type;//判断远程敌人发射子弹的方式
    int movestate;//判断此时的移动方向
    weapon3* mweapon3;
    int weaponnum;
    int interval,recorder;
public:
    enemy2();
    ~enemy2();
    void updateposition();
    void setweapon();//根据刷新出来的位置确定武器发射方向
    void shoot();
    void bulletupdate();
    void bulletcollisioncheck(character*,block1**);
    void bulletprint(QPainter&);
};
#endif // ENEMY_H
