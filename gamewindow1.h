#ifndef GAMEWINDOW1_H
#define GAMEWINDOW1_H

#include <QWidget>
#include<QPaintEvent>
#include<QKeyEvent>
#include<QPainter>
#include<QPalette>
#include<QTimer>
#include<QPushButton>
#include<ctime>
#include<startwindow.h>
#include"character.h"
#include"block.h"
#include"enemy.h"
#include"drop.h"
namespace Ui {
class gamewindow1;
}

class gamewindow1 : public QWidget
{
    Q_OBJECT

public:
    explicit gamewindow1(QWidget *parent = nullptr,int type=0,startWindow *start=nullptr);
    ~gamewindow1();
    void enemyoccur();//定时刷新敌人
    void updateposition();//每一帧定时刷新场景内物体坐标
    void collisioncheck();//每一帧定时检测是否有碰撞产生
    void createobject(int type);//创造游戏里面的人物
    void createlabel();//创造标签显示
    void createbutton();//创造按钮
    void createtimer();//创造定时器
protected:
    void paintEvent(QPaintEvent*);//每一帧定时绘制图片
    void keyPressEvent(QKeyEvent* event);
private:
    Ui::gamewindow1 *ui;
    startWindow *start;
    character *player1;
    block1** blocks1;//障碍物数组
    enemy1* menemy1;//怪物一数组
    int enemy1number;//场上enemy1的数量最大值
    enemy2* menemy2;//怪物二数组
    int enemy2number;//场上enemy2的数量最大值
    drop1 *drops1;//三种掉落物数组
    drop2 *drops2;
    drop3 *drops3;
    QTimer *time1;//刷新屏幕时间间隔,时间帧
    QTimer *time2;//记录1s，用于判断总游戏时长
    int recorder2;//记录刷怪间隔
    int recorder3;//记录怪物位置刷新间隔
    int recorder4;//记录近战伤害刷新
    int gametime;//用整数来判断游戏时长
    int player_level;//玩家等级
    int point;//升级需要的点数
    int gameupgrade;//玩家此时能升级的次数
    QPushButton *btn1,*btn2,*btn3,*btn4,*btn5,*btn6;
};

#endif // GAMEWINDOW1_H
