#ifndef EXERCISEROOM_H
#define EXERCISEROOM_H

#include <QLabel>
#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>
#include<pet.h>
#include<QKeyEvent>
#include<define.h>
#include <QProgressBar>
#include<QSound>
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>

class ExerciseRoom : public QWidget
{
    Q_OBJECT
public:
    explicit ExerciseRoom(QWidget *parent = 0,Pet* pet=nullptr);
    QSound* sounds[3];

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void backToPlay();//返回主界面

public slots:
    void exerRule();//宠物睡觉机制

private:
    //宠物的数值显示
    QLabel *moodLabel,*healthLabel,*hungerLabel,*activeLabel;
    //界面操作
    QPushButton *backBt,*exerBt;
    //宠物
    Pet* pet;
   int petx=542;  //x坐标
   int pety=426;  //y坐标
   int playAction;  //原地动作
   int exerAction=56;  //锻炼动作
   int sickOrHungerAction=false;
   int upAction=24;   //向上移动
   int downAction=44;  //向下移动
   int leftAction=50;  //向左移动
   int rightAction=50;  //向右移动
   int sleepAction=60; //睡觉
   bool playMove=true;
   bool upMove=false;
   bool downMove=false;
   bool leftMove=false;
   bool rightMove=false;
   QString file="child";
   QString appearance="Yangpa";
   //锻炼
   int isExercising=false;
   QProgressBar *pProgressBar;

};

#endif // EXERCISEROOM_H
