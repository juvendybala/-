#include "weapon.h"

weapon::weapon()
{
    x=0,y=0;
    picturepath="";
    speed=15;
    isfree=true;
    type=0;
    rec=new QRect(QPoint(x,y),QSize(SQUARE_WIDTH/2,SQUARE_HEIGHT/2));
}
weapon::~weapon()
{
    delete rec;
}
void weapon::updateposition()
{
    if(isfree){
        return;
    }
    if(type==0){
        x-=speed;
        rec->moveTo(x,y);
        if(x<-SQUARE_WIDTH/2) isfree=true;
    }
    else if(type==1){
        y-=speed;
        rec->moveTo(x,y);
        if(y<-SQUARE_HEIGHT/2) isfree=true;
    }
    else if(type==2){
        x+=speed;
        rec->moveTo(x,y);
        if(x>GAME_WIDTH) isfree=true;
    }
    else if(type==3){
        y+=speed;
        rec->moveTo(x,y);
        if(y>GAME_HEIGHT) isfree=true;
    }
}
weapon1::weapon1()
{
    picturepath=":/images/bullet_1.png";
}
weapon2::weapon2()
{
    picturepath=":/images/bullet_3.png";
}
weapon3::weapon3()
{
    picturepath=":/images/bullet_4.png";
}
