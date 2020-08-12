#include "mydialog.h"
#include <QMovie>
#include<QPixmap>
#include <QTimer>

Mydialog::Mydialog(Pet* pet)
{
    this->pet=pet;
    //宠物图像
    QLabel* label=new QLabel(this);
    //宠物地面buff
    QLabel* uploadLabel=new QLabel(this);
    QMovie* movie=new QMovie(":/new/prefix7/entertainment/move.GIF");
    //永久置顶
    m_timer = new QTimer();
    //   m_timer->start(1000); //程序每隔1秒置顶一次,该计时器由entertainment窗口”开始游戏“按钮触发，并在退出时停止
    connect(m_timer, &QTimer::timeout, [=]{
    #ifdef Q_OS_WIN32
        SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
    #endif //要在windows上不获取焦点切置顶，必须用Windows API
    });

    //*********样式*********//
     setWindowFlags(Qt::FramelessWindowHint | windowFlags());
     setAttribute(Qt::WA_TranslucentBackground);//把窗口设置为透明
     //宠物Label
     label->setPixmap(QPixmap(tr(":/new/prefix2/playroom/%1_%2 副本.png").arg(appearance2).arg(playAction)));
     label->setScaledContents(true);
     label->setFixedSize(120,120);
     label->move(100,100);
     //buff
     uploadLabel->setMovie(movie);
     uploadLabel->setFixedSize(150,50);
     uploadLabel->move(100-pet->getWidth()/2+25,100+pet->getHeight()+5);
     uploadLabel->setScaledContents(true);
     movie->start();

     //*********信号与槽***********//
     //宠物动作变换
     QTimer* petTimer=new QTimer(this);  //palyTime
     petTimer->start(PETSPEED);
     connect(petTimer,&QTimer::timeout,[=](){
         //皮肤
         if(pet->getAge()<10){
           appearance1="child";
           appearance2="Yangpa";
         } else  if(pet->getAge()<20){
             appearance1="youth";
             appearance2="Pasery";
             pet->setWidth(90);
             pet->setHeight(100);
         }else{
             appearance1="adult";
             appearance2="Doobu";
             pet->setWidth(100);
             pet->setHeight(120);
         }
         playAction++;
         if(playAction>104) playAction=0;
          label->setPixmap(QPixmap(tr(":/new/prefix3/petImages/%1/%2_%3 副本.png").arg(appearance1).arg(appearance2).arg(playAction)));
          update();  //更新窗口
     });
      //心情恢复进度
     QTimer* moodTimer=new QTimer(this);
     moodTimer->start(TIMESPEED);
     connect(moodTimer,&QTimer::timeout,[=](){
         static int count=0;
         count++;
         if(count>=HOUR/2){
             count=0;
             if(pet->getActive()<5){
                 pet->setActive(pet->getActive()+1);
             }
         }
         update();  //更新窗口
     });
}

void Mydialog::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::RightButton){
        //如果是右键，关闭窗口
        m_timer->stop();
        emit backToPlay();
    }else if(e->button()==Qt::LeftButton){
        //如果是左键，移动
        //求坐标差值
        point=e->globalPos()-this->frameGeometry().topLeft();    
    }
}

//鼠标左键长按拖动宠物位置
void Mydialog::mouseMoveEvent(QMouseEvent* e){
     if(e->buttons() & Qt::LeftButton){
         move(e->globalPos()-point);
     }
}
