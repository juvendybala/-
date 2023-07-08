#include "gamewindow1.h"
#include "ui_gamewindow1.h"
#include"config.h"
#include<QDebug>
gamewindow1::gamewindow1(QWidget *parent,int type,startWindow *start) :
    QWidget(parent),
    ui(new Ui::gamewindow1)
{
    ui->setupUi(this);
    srand(time(0));
    this->setWindowTitle("游戏");
    this->resize(1200,800);
    this->start=start;
    createobject(type);
    createlabel();
    createbutton();
    createtimer();
}
gamewindow1::~gamewindow1()
{
    if(blocks1){
        for(int i=0;i<BLOCKNUMBER;i++){
            delete []blocks1[i];
        }
        delete blocks1;
        blocks1=nullptr;
    }
    delete player1;
    player1=nullptr;
    delete []menemy1;
    menemy1=nullptr;
    delete []drops1,delete []drops2,delete []drops3;
    drops1=nullptr,drops2=nullptr,drops3=nullptr;
    delete start,start=nullptr;
    delete ui;
}
void gamewindow1::createobject(int type)
{
    if(type==0)player1=new character1(start);
    if(type==1)player1=new character2(start);
    blocks1=new block1*[BLOCKNUMBER];
    blocks1[0]=new block1(200,200),blocks1[1]=new block1(1000,300),blocks1[2]=new block1(400,400);
    blocks1[3]=new block1(1000,550),blocks1[4]=new block1(650,150);
    enemy1number=30;
    menemy1=new enemy1[enemy1number];
    enemy2number=15;
    menemy2=new enemy2[enemy2number];
    drops1=new drop1[DROPNUMBER];
    drops2=new drop2[DROPNUMBER];
    drops3=new drop3[DROPNUMBER];
    gametime=GAMETIME;
    player_level=1;
    point=100;
    gameupgrade=0;
}
void gamewindow1::createlabel()
{
    ui->label->setText(QString("时间: ")+QString::number(gametime)+QString(" 血量: ")+QString::number(player1->health));
    ui->label->setVisible(true);
    QPalette pe;
    pe.setColor(QPalette::Window,Qt::white);//设置白底红字
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pe);
}
void gamewindow1::createbutton()
{
    btn1=new QPushButton(this);
    btn1->setText("你赢了！");
    btn1->move(GAME_WIDTH/2,GAME_HEIGHT/2);
    btn1->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
    btn1->setVisible(false);
    btn2=new QPushButton(this);
    btn2->setText("你输了！");
    btn2->move(GAME_WIDTH/2,GAME_HEIGHT/2);
    btn2->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
    btn2->setVisible(false);
    connect(btn1,&QPushButton::clicked,[=](){
        start->gold+=(GAMETIME-gametime)*start->gold_rate;
        start->update();
        this->close();
    });
    connect(btn2,&QPushButton::clicked,[=](){
        start->gold+=(GAMETIME-gametime)*start->gold_rate;
        start->update();
        this->close();
    });
    btn3=new QPushButton(this);
    btn4=new QPushButton(this);
    btn5=new QPushButton(this);
    btn3->setText("血量"),btn4->setText("移速"),btn5->setText("攻击");
    btn3->move(0,0);
    btn3->setFixedSize(BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    btn3->setVisible(false);
    connect(btn3,&QPushButton::clicked,[&](){
       player1->health+=5;
       if(player1->health>player1->full_health) player1->health=player1->full_health;
       gameupgrade=0;
    });
    btn4->move(0,0);
    btn4->setFixedSize(BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    btn4->setVisible(false);
    connect(btn4,&QPushButton::clicked,[&](){
       player1->speed+=5;
       gameupgrade=0;
    });
    btn5->move(0,0);
    btn5->setFixedSize(BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    btn5->setVisible(false);
    connect(btn5,&QPushButton::clicked,[&](){
       player1->attack+=5;
       gameupgrade=0;
    });
    btn6=new QPushButton(this);
    btn6->setText("复活");
    btn6->move(GAME_WIDTH/2,GAME_HEIGHT/2);
    btn6->setFixedSize(BUTTON_WIDTH,BUTTON_HEIGHT);
    btn6->setVisible(false);
    connect(btn6,&QPushButton::clicked,[=](){
        player1->health=player1->full_health;
        start->life--;
        btn6->setVisible(false);
        time2->start();
        time1->start();
    });
}
void gamewindow1::createtimer()
{
    recorder2=recorder3=recorder4=0;
    time1=new QTimer();
    time1->setInterval(GAME_RATE);
    time1->start();
    connect(time1,&QTimer::timeout,[=](){
        time1->stop();
        if(gametime>0&&player1->health>0&&recorder2>=300){
            enemyoccur();
            recorder2=0;
        }
        else{
            recorder2++;
        }
        //if(start->life==0){ qDebug()<<menemy1[0].islive<<player1->health<<recorder4;}
        if(gametime>0&&player1->health>0&&recorder4>=50){
            for(int i=0;i<enemy1number;i++){
                if(menemy1[i].islive&&menemy1[i].rec->intersects(*player1->rec)){
                    player1->health-=menemy1[i].attack;//接触后扣血
                }
            }
            recorder4=0;
        }
        else{
            recorder4++;
        }
        if(player1->point>=point){
            player1->point=0;
            player_level++;
            gameupgrade++;
        }
        if(gametime>0&&player1->health>0){
            updateposition();
            collisioncheck();
        }
        update();
        time1->start();
    });
    time2=new QTimer();
    time2->setInterval(1000);
    time2->start();
    connect(time2,&QTimer::timeout,[&](){
        time2->stop();
        gametime--;
        if(gametime>0&&player1->health>0) time2->start();
    });
}
void gamewindow1::enemyoccur()
{
    for(int i=0;i<enemy1number;i++){
        if(!menemy1[i].islive){
            menemy1[i].islive=true;
            int type=rand()%4;
            if(type==0) menemy1[i].x=0,menemy1[i].y=rand()%(GAME_HEIGHT-SQUARE_HEIGHT);
            else if(type==1) menemy1[i].x=rand()%(GAME_WIDTH-SQUARE_WIDTH),menemy1[i].y=0;
            else if(type==2) menemy1[i].x=GAME_WIDTH-SQUARE_WIDTH,menemy1[i].y=rand()%(GAME_HEIGHT-SQUARE_HEIGHT);
            else if(type==3) menemy1[i].x=rand()%(GAME_WIDTH-SQUARE_WIDTH),menemy1[i].y=GAME_HEIGHT-SQUARE_HEIGHT;
            //qDebug()<<i;
            break;
        }
    }
    for(int i=0;i<enemy2number;i++){
        if(!menemy2[i].islive){
            menemy2[i].islive=true;
            int type=rand()%4;
            if(type==0) menemy2[i].x=0,menemy2[i].y=rand()%(GAME_HEIGHT-SQUARE_HEIGHT);
            else if(type==1) menemy2[i].x=rand()%(GAME_WIDTH-SQUARE_WIDTH),menemy2[i].y=0;
            else if(type==2) menemy2[i].x=GAME_WIDTH-SQUARE_WIDTH,menemy2[i].y=rand()%(GAME_HEIGHT-SQUARE_HEIGHT);
            else if(type==3) menemy2[i].x=rand()%(GAME_WIDTH-SQUARE_WIDTH),menemy2[i].y=GAME_HEIGHT-SQUARE_HEIGHT;
            menemy2[i].type=type;
            menemy2[i].setweapon();
            //qDebug()<<i;
            break;
        }
    }
}
void gamewindow1::updateposition()
{
    player1->shoot();
    player1->bulletupdate();
    if(recorder3>=4){
        for(int i=0;i<enemy1number;i++){
            if(menemy1[i].islive){
                menemy1[i].updateposition(player1,blocks1);
            }
        }
        for(int i=0;i<enemy2number;i++){
            if(menemy2[i].islive){
                menemy2[i].updateposition();
            }
        }
        recorder3=0;
    }
    else{
        recorder3++;
    }
    for(int i=0;i<enemy2number;i++){
        if(menemy2[i].islive){
            menemy2[i].shoot();
            menemy2[i].bulletupdate();
        }
    }
    if(gametime>0&&player1->health>0&&gameupgrade){
        btn3->setVisible(true),btn4->setVisible(true),btn5->setVisible(true);
        btn3->move(player1->x-60,player1->y+SQUARE_HEIGHT);
        btn4->move(player1->x+10,player1->y+SQUARE_HEIGHT);
        btn5->move(player1->x+SQUARE_WIDTH,player1->y+SQUARE_HEIGHT);
    }
    else{
        btn3->setVisible(false),btn4->setVisible(false),btn5->setVisible(false);
    }
}
void gamewindow1::collisioncheck()
{
    player1->bulletcollisioncheck(blocks1,menemy1,enemy1number,menemy2,enemy2number,drops1,drops2,drops3);
    for(int i=0;i<enemy2number;i++){
        if(menemy2[i].islive){
            menemy2[i].bulletcollisioncheck(player1,blocks1);
        }
    }
    for(int i=0;i<DROPNUMBER;i++){
        if(drops1[i].isexist){
            if(drops1[i].rec->intersects(*player1->pickrec)){
                player1->health+=5;
                if(player1->health>player1->full_health) player1->health=player1->full_health;
                drops1[i].isexist=false;
            }
        }
        if(drops2[i].isexist){
            if(drops2[i].rec->intersects(*player1->pickrec)){
                player1->point+=5;
                drops2[i].isexist=false;
            }
        }
        if(drops3[i].isexist){
            if(drops3[i].rec->intersects(*player1->pickrec)){
                start->gold+=20;
                drops3[i].isexist=false;
            }
        }
    }
}
void gamewindow1::paintEvent(QPaintEvent*)
{
    if(gametime==0) btn1->setVisible(true);
    else if(player1->health<=0&&start->life>0) btn6->setVisible(true);
    else if(player1->health<=0&&start->life==0) btn2->setVisible(true);
    QPainter painter(this);
    QPainter painter1(this);
    painter1.setBrush(Qt::red);
    QString path(":/images/background3.png");
    painter.drawPixmap(0,0,this->width(),this->height(),path);
    for(int i=0;i<enemy1number;i++){
        if(menemy1[i].islive){
            painter.drawPixmap(menemy1[i].x,menemy1[i].y,SQUARE_WIDTH,SQUARE_HEIGHT,menemy1[i].picturepath);
            //qDebug()<<"1";
            double rate=1.0*menemy1[i].curhealth/menemy1[i].health;
            painter1.drawRect(menemy1[i].x,menemy1[i].y,SQUARE_WIDTH*rate,SQUARE_HEIGHT*0.1);
        }
    }
    for(int i=0;i<enemy2number;i++){
        if(menemy2[i].islive){
            painter.drawPixmap(menemy2[i].x,menemy2[i].y,SQUARE_WIDTH,SQUARE_HEIGHT,menemy2[i].picturepath);
            double rate=1.0*menemy2[i].curhealth/menemy2[i].health;
            painter1.drawRect(menemy2[i].x,menemy2[i].y,SQUARE_WIDTH*rate,SQUARE_HEIGHT*0.1);
        }
    }
    for(int i=0;i<DROPNUMBER;i++){
        if(drops1[i].isexist){
            painter.drawPixmap(drops1[i].x,drops1[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,drops1[i].picturepath);
        }
        if(drops2[i].isexist){
            painter.drawPixmap(drops2[i].x,drops2[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,drops2[i].picturepath);
        }
        if(drops3[i].isexist){
            painter.drawPixmap(drops3[i].x,drops3[i].y,SQUARE_WIDTH/2,SQUARE_HEIGHT/2,drops3[i].picturepath);
        }
    }
    painter.drawPixmap(player1->x,player1->y,SQUARE_WIDTH,SQUARE_HEIGHT,player1->picturepath);
    double rate=1.0*player1->health/player1->full_health;
    if(player1->health<0) rate=0;
    painter1.drawRect(player1->x,player1->y,SQUARE_WIDTH*rate,SQUARE_HEIGHT*0.1);
    for(int i=0;i<BLOCKNUMBER;i++)
    {
        painter.drawPixmap(blocks1[i]->x,blocks1[i]->y,SQUARE_WIDTH,SQUARE_HEIGHT,blocks1[i]->picturepath);
    }
    if(player1->health>0&&gametime>0) {
        player1->bulletprint(painter);
        for(int i=0;i<enemy2number;i++){
            if(menemy2[i].islive){
                menemy2[i].bulletprint(painter);
            }
        }
    }
    ui->label->setText(QString("时间: ")+QString::number(gametime)+QString(" 血量: ")+QString::number(player1->health)\
    +QString("经验值：")+QString::number(player1->point)+QString("等级：")+QString::number(player_level)+QString("复活次数: ")+QString::number(start->life));
}
void gamewindow1::keyPressEvent(QKeyEvent* event)
{
    if(player1->health>0&&gametime>0){
        int tempx=player1->x;
        int tempy=player1->y;
        int& y=player1->y;
        int& x=player1->x;
        int temp=player1->speed;
        switch(event->key())
        {
            case Qt::Key_W:
                y-=temp;
                if(y<0) y=0;
            break;
            case Qt::Key_S:
                y+=temp;
                if((y+SQUARE_HEIGHT)>=GAME_HEIGHT) y=GAME_HEIGHT-SQUARE_HEIGHT;
            break;
            case Qt::Key_A:
                x-=temp;
                if(x<0) x=0;
            break;
            case Qt::Key_D:
                x+=temp;
                if((x+SQUARE_WIDTH)>=GAME_WIDTH) x=GAME_WIDTH-SQUARE_WIDTH;
            break;
        }
        player1->setnewposition(x,y);
        for(int i=0;i<BLOCKNUMBER;i++)
        {
            if(player1->rec->intersects(*(blocks1[i]->rec))){
                x=tempx,y=tempy;
                player1->setnewposition(x,y);
                break;
            }
        }
    //qDebug()<<y<<x;
    }
}
