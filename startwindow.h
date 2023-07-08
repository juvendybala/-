#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include<QFileDialog>
#include<QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class startWindow; }
QT_END_NAMESPACE

class startWindow : public QMainWindow
{
    Q_OBJECT
public:
    int gold=0;//存储金币数
    int life=0;//可复活次数
    double gold_rate=1;//局内金币获取系数
    int extrahealth=0,extraspeed=0;//角色基础属性增强
    int extraattack=0;//武器属性增强
public:
    startWindow(QWidget *parent = nullptr);
    ~startWindow();
protected:
    void paintEvent(QPaintEvent*);
private:
    Ui::startWindow *ui;
};
#endif // STARTWINDOW_H
