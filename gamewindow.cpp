#include<gamewindow.h>

Gamewindow::Gamewindow()
{
    this->resize(1200,800);
}

void Gamewindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QString path(":/images/background2.png");
    painter.drawPixmap(0,0,this->width(),this->height(),path);
}
