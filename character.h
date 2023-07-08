#ifndef CHARACTER_H
#define CHARACTER_H
#include<QString>
#include<QRect>
#include<QPainter>
#include"startwindow.h"
#include"config.h"
#include"weapon.h"
#include"block.h"
#include"drop.h"
class enemy1;
class enemy2;
class character
{
public:
    int health;
    int full_health;
    int attack;
    int speed;
    int x,y;//坐标位置，图片左上角为基准
    int point;//玩家当前经验值
    QRect* rec;//用于检测碰撞的矩形
    QRect* pickrec;//用于检测拾取功能
    QString picturepath;
public:
    character(int health,int attack,int speed,int x,int y,QString path,startWindow *start);
    virtual ~character();
    void setnewposition(int x,int y);
    virtual void shoot()=0;
    virtual void bulletupdate()=0;
    virtual void bulletcollisioncheck(block1**,enemy1*,int,enemy2*,int,drop1*,drop2*,drop3*)=0;
    virtual void bulletprint(QPainter&)=0;
};
class character1:public character
{
public:
    int type;
    weapon1 *mweapon1;
    int weaponnum;//记录弹夹数量
    int interval,recorder;//记录发射应有间隔和发射目前发射间隔
public:
    character1(startWindow *start);
    ~character1();
    void shoot();
    void bulletupdate();
    void bulletcollisioncheck(block1**,enemy1*,int,enemy2*,int,drop1*,drop2*,drop3*);
    void bulletprint(QPainter&);
};
class character2:public character
{
public:
    int type;
    weapon2 *mweapon2;
    int weaponnum;//记录弹夹数量
    int interval,recorder;//记录发射应有间隔和发射目前发射间隔
public:
    character2(startWindow *start);
    ~character2();
    void shoot();
    void bulletupdate();
    void bulletcollisioncheck(block1**,enemy1*,int,enemy2*,int,drop1*,drop2*,drop3*);
    void bulletprint(QPainter&);
};
#endif // CHARACTER_H
