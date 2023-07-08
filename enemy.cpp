#include "enemy.h"

enemy::enemy(int health,int attack,int speed)
{
    this->health=health,this->attack=attack,this->speed=speed;
    this->curhealth=health;
    islive=false;
    x=0,y=0;
    rec=new QRect(QPoint(x,y),QSize(SQUARE_WIDTH,SQUARE_HEIGHT));
    picturepath="";
}
enemy1::enemy1():enemy(60,5,5)
{
    picturepath=":/images/enemy_3.png";
}
void enemy1::updateposition(character* player,block1** blocks1)//todo:更合理的寻路算法
{
    if(!islive) return;
    if(this->rec->intersects(*player->rec)){
        return;
    }
    int dx[5]={0,-speed,speed,0,0};
    int dy[5]={0,0,0,-speed,speed};
    int dis=(x-player->x)*(x-player->x)+(y-player->y)*(y-player->y);
    int d=0;
    for(int i=0;i<5;i++){
        int tempx=x+dx[i],tempy=y+dy[i];
        if(tempx<0||tempx+SQUARE_WIDTH>GAME_WIDTH||tempy<0||tempy+SQUARE_HEIGHT>GAME_HEIGHT){
            continue;
        }
        rec->moveTo(tempx,tempy);
        int flag=1;
        for(int j=0;j<BLOCKNUMBER;j++){
            if(rec->intersects(*blocks1[j]->rec)){
                flag=0;
                //qDebug()<<"2";
            }
        }
        if(flag==0) continue;
        int tempd=(tempx-player->x)*(tempx-player->x)+(tempy-player->y)*(tempy-player->y);
        if(dis>tempd) dis=tempd,d=i;
    }
    x+=dx[d],y+=dy[d];
    rec->moveTo(x,y);
}
enemy2::enemy2():enemy(40,5,10)
{
    type=0;
    weaponnum=30;
    mweapon3=new weapon3[weaponnum];
    interval=100,recorder=0;
    movestate=0;
    picturepath=":/images/enemy_4.png";
}
enemy2::~enemy2()
{
    delete []mweapon3;
    mweapon3=nullptr;
}
void enemy2::updateposition()
{
    if(type==0||type==2){
        if(movestate==0){
            y+=speed;
            if(y+SQUARE_HEIGHT>GAME_HEIGHT){
                y=GAME_HEIGHT-SQUARE_HEIGHT;
                movestate=1;
            }
        }
        else if(movestate==1){
            y-=speed;
            if(y<0){
                y=0;
                movestate=0;
            }
        }
    }
    else if(type==1||type==3){
        if(movestate==0){
            x+=speed;
            if(x+SQUARE_WIDTH>GAME_WIDTH){
                x=GAME_WIDTH-SQUARE_WIDTH;
                movestate=1;
            }
        }
        else if(movestate==1){
            x-=speed;
            if(x<0){
                x=0;
                movestate=0;
            }
        }
    }
    rec->moveTo(x,y);
}
void enemy2::setweapon()
{
    if(type==0){
        for(int i=0;i<weaponnum;i++){
            mweapon3[i].type=2;
        }
    }
    else if(type==1){
        for(int i=0;i<weaponnum;i++){
            mweapon3[i].type=3;
        }
    }
    else if(type==2){
        for(int i=0;i<weaponnum;i++){
            mweapon3[i].type=0;
        }
    }
    else if(type==3){
        for(int i=0;i<weaponnum;i++){
            mweapon3[i].type=1;
        }
    }
}
void enemy2::shoot()
{
    recorder++;
    if(recorder<interval) {return;}
    recorder=0;
    for(int i=0;i<weaponnum;i++){
        if(mweapon3[i].isfree){
            if(mweapon3[i].type==0){
                mweapon3[i].isfree=false;
                mweapon3[i].x=this->x-SQUARE_WIDTH/2+mweapon3[i].speed;
                mweapon3[i].y=this->y+SQUARE_HEIGHT/4;
            }
            else if(mweapon3[i].type==1){
                mweapon3[i].isfree=false;
                mweapon3[i].x=this->x+SQUARE_WIDTH/4;
                mweapon3[i].y=this->y+SQUARE_HEIGHT/2+mweapon3[i].speed;
            }
            else if(mweapon3[i].type==2){
                mweapon3[i].isfree=false;
                mweapon3[i].x=this->x+SQUARE_WIDTH-mweapon3[i].speed;
                mweapon3[i].y=this->y+SQUARE_HEIGHT/4;
            }
            else if(mweapon3[i].type==3){
                mweapon3[i].isfree=false;
                mweapon3[i].x=this->x+SQUARE_WIDTH/4;
                mweapon3[i].y=this->y+SQUARE_HEIGHT-mweapon3[i].speed;
            }
            break;
        }
    }
}
void enemy2::bulletupdate()
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon3[i].isfree){
            mweapon3[i].updateposition();
        }
    }
}
void enemy2::bulletcollisioncheck(character* player,block1** blocks)
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon3[i].isfree&&mweapon3[i].rec->intersects(*player->rec)){
            player->health-=this->attack;
            mweapon3[i].isfree=true;
        }
    }
    for(int i=0;i<weaponnum;i++){
        for(int j=0;j<BLOCKNUMBER;j++){
        if(!mweapon3[i].isfree&&mweapon3[i].rec->intersects(*blocks[j]->rec)){
            mweapon3[i].isfree=true;
            //qDebug()<<"1";
        }
        }
    }
}
void enemy2::bulletprint(QPainter& painter)
{
    for(int i=0;i<weaponnum;i++){
        if(!mweapon3[i].isfree){
            painter.drawPixmap(mweapon3[i].x,mweapon3[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,mweapon3[i].picturepath);
        }
    }
}
