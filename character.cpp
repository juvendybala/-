#include "character.h"
#include"enemy.h"
character::character(int health,int attack,int speed,int x,int y,QString path,startWindow *start)
{
    this->health=health+start->extrahealth,this->attack=attack+start->extraattack,this->speed=speed+start->extraspeed;
    full_health=this->health;
    this->x=x,this->y=y;
    rec=new QRect(QPoint(x,y),QSize(SQUARE_WIDTH,SQUARE_HEIGHT));
    pickrec=new QRect(QPoint(x+SQUARE_WIDTH/4,y+SQUARE_HEIGHT/4 ),QSize(SQUARE_WIDTH/2,SQUARE_HEIGHT/2));
    picturepath=path;
    point=0;
}
character::~character()
{
    delete rec;
    rec=nullptr;
    delete pickrec;
    pickrec=nullptr;
}
void character::setnewposition(int x,int y)
{
    rec->moveTo(x,y);
    pickrec->moveTo(x,y);
}
character1::character1(startWindow *start):character(100,15,20,GAME_WIDTH/2,GAME_HEIGHT/2,":/images/character1.png",start)//todo:初始化时加上基础属性和武器属性全局加成
{
    type=0;
    weaponnum=120;
    mweapon1=new weapon1[weaponnum];
    for(int i=0;i<weaponnum;i++){
        mweapon1[i].type=i/(weaponnum/4);
    }
    interval=30,recorder=0;
}
character1::~character1()
{
    delete []mweapon1;
    mweapon1=nullptr;
}
void character1::shoot()
{
    recorder++;
    if(recorder<interval){ return;}
    recorder=0;
    int i=0;
    for(;i<weaponnum/4;i++){
        if(mweapon1[i].isfree){
            mweapon1[i].isfree=false;
            mweapon1[i].x=this->x-SQUARE_WIDTH/2+mweapon1[i].speed;
            mweapon1[i].y=this->y+SQUARE_HEIGHT/4;
            break;
        }
    }
    i=weaponnum/4;
    for(;i<weaponnum/2;i++){
        if(mweapon1[i].isfree){
            mweapon1[i].isfree=false;
            mweapon1[i].x=this->x+SQUARE_WIDTH/4;
            mweapon1[i].y=this->y+SQUARE_HEIGHT/2+mweapon1[i].speed;
            break;
        }
    }
    i=weaponnum/2;
    for(;i<3*weaponnum/4;i++){
        if(mweapon1[i].isfree){
            mweapon1[i].isfree=false;
            mweapon1[i].x=this->x+SQUARE_WIDTH-mweapon1[i].speed;
            mweapon1[i].y=this->y+SQUARE_HEIGHT/4;
            break;
        }
    }
    i=3*weaponnum/4;
    for(;i<weaponnum;i++){
        if(mweapon1[i].isfree){
            mweapon1[i].isfree=false;
            mweapon1[i].x=this->x+SQUARE_WIDTH/4;
            mweapon1[i].y=this->y+SQUARE_HEIGHT-mweapon1[i].speed;
            break;
        }
    }
}
void character1::bulletupdate()
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon1[i].isfree){
            mweapon1[i].updateposition();
        }
    }
}
void character1::bulletcollisioncheck(block1 **blocks,enemy1* menemy1,int num1,enemy2* menemy2,int num2,drop1* drops1,drop2* drops2,drop3*drops3)
{
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<num1;j++){
            if(!mweapon1[i].isfree&&menemy1[j].islive&&mweapon1[i].rec->intersects(*menemy1[j].rec)){
                menemy1[j].curhealth-=this->attack;
                mweapon1[i].isfree=true;
                if(menemy1[j].curhealth<=0){
                    point+=10;
                    menemy1[j].islive=false;
                    menemy1[j].curhealth=menemy1[j].health;
                    int tmp=rand()%12;
                    if(tmp==0){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops1[k].isexist){
                                drops1[k].isexist=true;
                                drops1[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops1[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops1[k].rec->moveTo(drops1[k].x,drops1[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==1){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops2[k].isexist){
                                drops2[k].isexist=true;
                                drops2[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops2[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops2[k].rec->moveTo(drops2[k].x,drops2[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==2){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops3[k].isexist){
                                drops3[k].isexist=true;
                                drops3[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops3[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops3[k].rec->moveTo(drops3[k].x,drops3[k].y);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<num2;j++){
            if(!mweapon1[i].isfree&&menemy2[j].islive&&mweapon1[i].rec->intersects(*menemy2[j].rec)){
                menemy2[j].curhealth-=this->attack;
                mweapon1[i].isfree=true;
                if(menemy2[j].curhealth<=0){
                    point+=10;
                    menemy2[j].islive=false;
                    menemy2[j].curhealth=menemy2[j].health;
                    int tmp=rand()%12;
                    if(tmp==0){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops1[k].isexist){
                                drops1[k].isexist=true;
                                drops1[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops1[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops1[k].rec->moveTo(drops1[k].x,drops1[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==1){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops2[k].isexist){
                                drops2[k].isexist=true;
                                drops2[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops2[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops2[k].rec->moveTo(drops2[k].x,drops2[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==2){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops3[k].isexist){
                                drops3[k].isexist=true;
                                drops3[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops3[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops3[k].rec->moveTo(drops3[k].x,drops3[k].y);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<BLOCKNUMBER;j++){
        if(!mweapon1[i].isfree&&mweapon1[i].rec->intersects(*blocks[j]->rec)){
            mweapon1[i].isfree=true;
            //qDebug()<<"1";
        }
        }
    }
}
void character1::bulletprint(QPainter& painter)
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon1[i].isfree){
            painter.drawPixmap(mweapon1[i].x,mweapon1[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,mweapon1[i].picturepath);
        }
    }
}
character2::character2(startWindow *start):character(80,20,15,GAME_WIDTH/2,GAME_HEIGHT/2,":/images/character2.png",start)
{
    type=1;
    weaponnum=120;
    mweapon2=new weapon2[weaponnum];
    for(int i=0;i<weaponnum;i++){
        mweapon2[i].type=i/(weaponnum/4);
    }
    interval=50,recorder=0;
}
character2::~character2()
{
    delete []mweapon2;
    mweapon2=nullptr;
}
void character2::shoot()
{
    recorder++;
    if(recorder<interval){ return;}
    recorder=0;
    int i=0;
    for(;i<weaponnum/4;i++){
        if(mweapon2[i].isfree){
            mweapon2[i].isfree=false;
            mweapon2[i].x=this->x-SQUARE_WIDTH/2+mweapon2[i].speed;
            mweapon2[i].y=this->y+SQUARE_HEIGHT/4;
            break;
        }
    }
    i=weaponnum/4;
    for(;i<weaponnum/2;i++){
        if(mweapon2[i].isfree){
            mweapon2[i].isfree=false;
            mweapon2[i].x=this->x+SQUARE_WIDTH/4;
            mweapon2[i].y=this->y+SQUARE_HEIGHT/2+mweapon2[i].speed;
            break;
        }
    }
    i=weaponnum/2;
    for(;i<3*weaponnum/4;i++){
        if(mweapon2[i].isfree){
            mweapon2[i].isfree=false;
            mweapon2[i].x=this->x+SQUARE_WIDTH-mweapon2[i].speed;
            mweapon2[i].y=this->y+SQUARE_HEIGHT/4;
            break;
        }
    }
    i=3*weaponnum/4;
    for(;i<weaponnum;i++){
        if(mweapon2[i].isfree){
            mweapon2[i].isfree=false;
            mweapon2[i].x=this->x+SQUARE_WIDTH/4;
            mweapon2[i].y=this->y+SQUARE_HEIGHT-mweapon2[i].speed;
            break;
        }
    }
}
void character2::bulletupdate()
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon2[i].isfree){
            mweapon2[i].updateposition();
        }
    }
}
void character2::bulletcollisioncheck(block1 **blocks,enemy1* menemy1,int num1,enemy2* menemy2,int num2,drop1* drops1,drop2* drops2,drop3* drops3)
{
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<num1;j++){
            if(!mweapon2[i].isfree&&menemy1[j].islive&&mweapon2[i].rec->intersects(*menemy1[j].rec)){
                menemy1[j].curhealth-=this->attack;
                mweapon2[i].isfree=true;
                if(menemy1[j].curhealth<=0){
                    point+=10;
                    menemy1[j].islive=false;
                    menemy1[j].curhealth=menemy1[j].health;
                    int tmp=rand()%12;
                    if(tmp==0){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops1[k].isexist){
                                drops1[k].isexist=true;
                                drops1[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops1[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops1[k].rec->moveTo(drops1[k].x,drops1[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==1){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops2[k].isexist){
                                drops2[k].isexist=true;
                                drops2[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops2[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops2[k].rec->moveTo(drops2[k].x,drops2[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==2){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops3[k].isexist){
                                drops3[k].isexist=true;
                                drops3[k].x=menemy1[j].x+SQUARE_WIDTH/4;
                                drops3[k].y=menemy1[j].y+SQUARE_HEIGHT/4;
                                drops3[k].rec->moveTo(drops3[k].x,drops3[k].y);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<num2;j++){
            if(!mweapon2[i].isfree&&menemy2[j].islive&&mweapon2[i].rec->intersects(*menemy2[j].rec)){
                menemy2[j].curhealth-=this->attack;
                mweapon2[i].isfree=true;
                if(menemy2[j].curhealth<=0){
                    point+=10;
                    menemy2[j].islive=false;
                    menemy2[j].curhealth=menemy2[j].health;
                    int tmp=rand()%12;
                    if(tmp==0){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops1[k].isexist){
                                drops1[k].isexist=true;
                                drops1[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops1[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops1[k].rec->moveTo(drops1[k].x,drops1[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==1){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops2[k].isexist){
                                drops2[k].isexist=true;
                                drops2[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops2[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops2[k].rec->moveTo(drops2[k].x,drops2[k].y);
                                break;
                            }
                        }
                    }
                    if(tmp==2){
                        for(int k=0;k<DROPNUMBER;k++){
                            if(!drops3[k].isexist){
                                drops3[k].isexist=true;
                                drops3[k].x=menemy2[j].x+SQUARE_WIDTH/4;
                                drops3[k].y=menemy2[j].y+SQUARE_HEIGHT/4;
                                drops3[k].rec->moveTo(drops3[k].x,drops3[k].y);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<BLOCKNUMBER;j++){
        if(mweapon2[i].rec->intersects(*blocks[j]->rec)){
            mweapon2[i].isfree=true;
            //qDebug()<<"1";
        }
        }
    }
}
void character2::bulletprint(QPainter& painter)
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon2[i].isfree){
            painter.drawPixmap(mweapon2[i].x,mweapon2[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,mweapon2[i].picturepath);
        }
    }
}
