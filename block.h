#ifndef BLOCK_H
#define BLOCK_H
#include<QRect>
#include<QString>
#include"config.h"
class block
{
public:
    block(int health,int x,int y,QString path);
    ~block();
    int health;
    int x,y;
    QRect* rec;
    QString picturepath;
};
class block1:public block
{
public:
    block1(int x,int y);
    ~block1();
};

#endif // BLOCK_H
