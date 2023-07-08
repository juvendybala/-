#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<QWidget>
#include<QPaintEvent>
#include<QPainter>

class Gamewindow: public QWidget
{
public:
    Gamewindow();
protected:
    void paintEvent(QPaintEvent*);
};

#endif // GAMEWINDOW_H
