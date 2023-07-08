#include "block.h"

block::block(int health,int x,int y,QString path)
{
    this->health=health;
    this->x=x,this->y=y;
    rec=new QRect(QPoint(x,y),QSize(SQUARE_WIDTH,SQUARE_HEIGHT));
    picturepath=path;
}
block::~block()
{
    delete rec;
    rec=nullptr;
}
block1::block1(int x,int y):block(-1,x,y,":/images/block_1.png")//-1表示不可摧毁
{

}
block1::~block1()
{

}
