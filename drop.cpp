#include "drop.h"

drop::drop()
{
    x=0,y=0;
    rec=new QRect(QPoint(x,y),QSize(SQUARE_WIDTH/2,SQUARE_HEIGHT/2));
    picturepath="";
    isexist=false;
}
drop::~drop()
{
    delete rec;
    rec=nullptr;
}
drop1::drop1()
{
    picturepath=":/images/life.png";
}
drop2::drop2()
{
    picturepath=":/images/point.png";
}
drop3::drop3()
{
    picturepath=":/images/gold.png";
}
