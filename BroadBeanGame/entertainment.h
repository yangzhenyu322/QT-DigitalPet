#ifndef ENTERTAINMENT_H
#define ENTERTAINMENT_H

#include <QLabel>
#include <QPaintEvent>
#include<QPaintEvent>
#include <QPushButton>
#include <QWidget>
#include<pet.h>
#include<mydialog.h>
#include<define.h>
#include <QPropertyAnimation>
#include<QSound>
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>


class entertainment : public QWidget
{
    Q_OBJECT
public:
    explicit entertainment(QWidget *parent = 0,Pet* pet=nullptr);
    //bgm+音效
    QSound* sounds[3];

protected:
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void mouseMoveEvent(QMouseEvent* event);

signals:
    void backToPlay();//返回主界面

public slots:
    void playRule();//宠物玩耍机制

private:
    //宠物的数值显示
    QLabel *moodLabel,*healthLabel,*hungerLabel,*activeLabel;
    //界面操作
    QPushButton *backBt,*playBt;
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
   bool playing=true;
   bool upMove=false;
   bool downMove=false;
   bool leftMove=false;
   bool rightMove=false;
   bool playMove=false;
   QString appearance="Yangpa";
   //加载
   QTimer* upLoadTimer;
    //玩耍
   bool isPlaying=false;
    Mydialog*  mydialog;  //玩耍窗口
};

#endif // ENTERTAINMENT_H
