#ifndef BEDROOM_H
#define BEDROOM_H

#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include<pet.h>
#include<define.h>
#include"QSound"
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>


class Bedroom : public QWidget
{
    Q_OBJECT
public:
    explicit Bedroom(QWidget *parent = 0,Pet* pet=nullptr);
    //bgm+音效
    QSound* sounds[4];

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void backToPlay();//返回主界面

public slots:
    void sleepRule();//宠物睡觉机制

private:
    //宠物的数值显示
    QLabel *moodLabel,*healthLabel,*hungerLabel,*activeLabel;
    //界面操作
    QPushButton *backBt,*bedBt;
    //宠物
    Pet* pet;
   int petx=700;  //x坐标
   int pety=500;  //y坐标
   int playAction;  //原地动作
   int sickOrHungerAction=false;
   int upAction=24;   //向上移动
   int downAction=44;  //向下移动
   int leftAction=50;  //向左移动
   int rightAction=50;  //向右移动
   int sleepAction=60; //睡觉
   bool playing=true;
   bool upMove=false;
   bool downMove=false;
   bool leftMove=false;
   bool rightMove=false;
   bool sleepMove=false;
   QString appearance="Yangpa";

};

#endif // BEDROOM_H
