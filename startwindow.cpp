#include "startwindow.h"
#include "ui_startwindow.h"
#include"gamewindow1.h"
startWindow::startWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::startWindow)
{
    ui->setupUi(this);
    setWindowTitle("开始");
    ui->label->setText(QString("金币数目: ")+QString::number(gold));
    QPalette pe;
    pe.setColor(QPalette::Window,Qt::white);//设置白底红字
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->label->setPalette(pe);
    connect(ui->button1, &QPushButton::clicked, [=]()
    {
        gamewindow1* gamewindow=new gamewindow1(nullptr,0,this);
        gamewindow->show();
    });
    connect(ui->button2, &QPushButton::clicked, [=]()
    {
        gamewindow1* gamewindow=new gamewindow1(nullptr,1,this);
        gamewindow->show();
    });
    connect(ui->button3,&QPushButton::clicked,[=](){
        if(gold>=50){
            gold-=50;
            extrahealth+=5,extraspeed+=3;
        }
        update();
    });
    connect(ui->button4,&QPushButton::clicked,[=](){
        if(gold>=50){
            gold-=50;
            extraattack+=5;
        }
        update();
    });
    connect(ui->button5,&QPushButton::clicked,[=](){
        if(gold>=20){
            gold-=20;
            gold_rate+=0.1;
        }
        update();
    });
    connect(ui->button6,&QPushButton::clicked,[=](){
        if(gold>=100){
            gold-=100;
            life++;
        }
        update();
    });
    connect(ui->button7,&QPushButton::clicked,[=](){
        QString filepath=QFileDialog::getSaveFileName(this,"save file","",tr("TXT(*.txt)"));
        if(filepath.isEmpty()) return;
        QFile file(filepath);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        if(file.isOpen()){
            QTextStream out(&file);
            out<<gold<<" "<<life<<" "<<gold_rate<<" "<<extrahealth<<" "<<extraspeed<<" "<<extraattack;
            file.close();
        }
    });
    connect(ui->button8,&QPushButton::clicked,[=](){
        QString filepath=QFileDialog::getOpenFileName(this,"open file","",tr("TXT(*.txt)"));
        if(filepath.isEmpty()) return;
        QFile file(filepath);
        file.open(QIODevice::ReadOnly|QIODevice::Text);
        if(file.isOpen()){
            QTextStream in(&file);
            in>>gold>>life>>gold_rate>>extrahealth>>extraspeed>>extraattack;
            file.close();
        }
        update();
    });
    //qDebug()<<ui->button1->width()<<ui->button2->width();
    //qDebug()<<gold<<life<<gold_rate<<extrahealth<<extraspeed<<extraattack;
}

startWindow::~startWindow()
{
    delete ui;
}
void startWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QString path(":/images/background1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),path);
    ui->label->setText(QString("金币数目: ")+QString::number(gold));
}
