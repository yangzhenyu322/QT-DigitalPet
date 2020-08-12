#ifndef BEGIN_H
#define BEGIN_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPushButton>
#include<playroom.h>
#include<define.h>
#include <QPropertyAnimation>
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>
#include<pet.h>

class Begin : public QMainWindow
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent* event);
    void tempSaveData();

public:
    Begin(QWidget *parent = 0,Pet* pet=nullptr);
    ~Begin();
signals:
    void backToLogin();
    void stopBGM();   //暂停bgm
    void playBGM();  //播放bgm
    void saveData();  //保存数据
    void loadGame();//载入游戏

private:
    QPushButton *button1,*button2,*button3,*button4;
    //娱乐室
    Playroom* playroom;
    int count;
    //宠物动图
    QLabel *label1,*label2,*label3,*label4;
    //加载
    QPropertyAnimation* animation;
    //标题
    QLabel* titileLabel;
    //宠物
    Pet* pet;
    Pet tempPet;  //暂时保存当前数据
};

#endif // BEGIN_H
