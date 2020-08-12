#ifndef KITCHENROOM_H
#define KITCHENROOM_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include<pet.h>
#include<define.h>
#include <QPropertyAnimation>
#include<QSound>
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>

class Kitchenroom : public QWidget
{
    Q_OBJECT
public:
    explicit Kitchenroom(QWidget *parent = 0,Pet* pet=nullptr);
    QSound* sounds[5];

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
    //缩放效果
    QPropertyAnimation *pScaleAnimation[4];
    //食物
    QPushButton*  foodBt[4];
    //狗
    QPushButton* dogBt;
    bool anger=false;
    bool text=false;
    //宠物
   Pet* pet;
   int petx=700;  //x坐标
   int pety=500;  //y坐标
   int playAction=0;  //原地动作
   int sickOrHungerAction=false;
   int upAction=24;   //向上移动
   int downAction=44;  //向下移动
   int leftAction=50;  //向左移动
   int rightAction=50;  //向右移动
   bool playMove=true;
   bool upMove=false;
   bool downMove=false;
   bool leftMove=false;
   bool rightMove=false;
   QString appearance="Yangpa";
};

#endif // KITCHENROOM_H
