#ifndef PLAYROOM_H
#define PLAYROOM_H

#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>
#include<QSpacerItem>
#include<QTimer>
#include<define.h>
#include<define.h>
#include<QKeyEvent>
#include<pet.h>
#include<bedroom.h>
#include<entertainment.h>
#include<kitchenroom.h>
#include<exerciseroom.h>
#include <QPropertyAnimation>
#include"QSound"
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>

class Playroom : public QWidget
{
    Q_OBJECT
public:
    explicit Playroom(QWidget *parent = 0,Pet* pet=nullptr);
    void initDate(bool b);
    QTimer* clockTimer=new QTimer(this);  //时间计时器
     QTimer* petReduceTimer= new QTimer(this);  //宠物机制计时器
    QSound* sounds[4];  //音效
    void setClock(int time);  //更新时间

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* event);


signals:
    void backToBegin();
    void restart();

public slots:
    void clockShow();
    void reduceRule();\


private:
    //加载
    QPropertyAnimation* animation;
    //宠物的数值显示
    QLabel *moodLabel,*healthLabel,*hungerLabel,*activeLabel;
    //时间
    QLineEdit *timeLine;
    //宠物信息
    QLabel *nameLabel,*stateLabel,*weightLabel,*ageLabel,*spaceLabel;
    //界面操作
    QPushButton *messageBt,*bedBt,*amuseBt,*eatBt,*exciseBt,*cureBt,*backBt;
    //时钟
    int  clock=CURRENTHOUE*3600+CURRENTMINUTE*60+CURRENTSECONDS;
    //死亡后，重新开始按钮
    QPushButton* restartBt;
    //宠物的各数值增减机制
    //宠物
   Pet* pet;
   int petx=700;  //x坐标
   int pety=500;  //y坐标
   int playAction;  //原地动作
   int upAction=24;   //向上移动
   int downAction=44;  //向下移动
   int leftAction=50;  //向左移动
   int rightAction=50;  //向右移动
   int sickOrHungerAction=88; //虚弱状态
   bool playing=true;
   bool upMove=false;
   bool downMove=false;
   bool leftMove=false;
   bool rightMove=false;
   QString appearance="Yangpa";
   //其它房间
   Bedroom* bedroom;
   entertainment* entertainmentroom;
   Kitchenroom* kitroom;
   ExerciseRoom* exerroom;
   //和主人玩耍
   bool isEntertainment=false;
   //信息框
   bool showInfo=false;


};

#endif // PLAYROOM_H
