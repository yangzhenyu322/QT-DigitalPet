#include "bedroom.h"
#include<QDebug>
#include <QPainter>
#include <QTimer>

Bedroom::Bedroom(QWidget *parent,Pet*  pet) : QWidget(parent)
{
    this->pet=pet;
    //*********布局*************//
    backBt=new QPushButton(this);
    bedBt=new QPushButton(this);
    moodLabel=new QLabel(this);
    moodLabel->setText("心情：");
    healthLabel=new QLabel(this);
    healthLabel->setText("健康：");
    hungerLabel=new QLabel(this);
    hungerLabel->setText("能量：");
    activeLabel=new QLabel(this);
    activeLabel->setText("活力：");
    //bgm+音效
    sounds[0]=new QSound("../BroadBean/sounds/bgm/bedroom.wav",this);
    sounds[0]->setLoops(-1);
    sounds[1]=new QSound("../BroadBean/sounds/button/button6.wav",this);
    sounds[2]=new QSound("../BroadBean/sounds/voice/sleeping.wav",this);
    sounds[3]=new QSound("../BroadBean/sounds/walk/走路.wav",this);

    //********样式*********//
    setWindowTitle("小暖窝");
    setFixedSize(1135,640);
    //设置为不按下鼠标键触发moveEvent
    this->setMouseTracking(true);
    //按钮样式
    backBt->move(50,550);
    backBt->setStyleSheet({"border-image:url(:/new/prefix6/bedroom/back.png)"});
    backBt->setAutoFillBackground(true);
    backBt->setFixedSize(80,60);
    bedBt->move(164,520);
    bedBt->setStyleSheet({"border-image:url(:/new/prefix6/bedroom/bedBt.png)"});
    bedBt->setAutoFillBackground(true);
    bedBt->setFixedSize(100,120);
    //宠物的属性值
    moodLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:rgb(65,165,238);font-weight:bold");
    healthLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:rgb(65,165,238);font-weight:bold");
    hungerLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:rgb(65,165,238);font-weight:bold");
    activeLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:rgb(65,165,238);font-weight:bold");
    moodLabel->setFixedSize(225,40);
    healthLabel->setFixedSize(225,40);
    hungerLabel->setFixedSize(225,40);
    activeLabel->setFixedSize(225,40);
    moodLabel->move(48,10);
    healthLabel->move(48+270,10);
    hungerLabel->move(48+270*2,10);
    activeLabel->move(45+270*3,10);

    //*************信号与槽**********//
    //返回主界面
    connect(backBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        if(!sleepMove){
            emit backToPlay();
        }
    });
    //睡觉
    connect(bedBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        static int count=0;
        count++;
        if(count%2==1){
            sleepMove=true;
            sounds[2]->play();
            sounds[2]->setLoops(-1);
        }else{
            sleepMove=false;
            sounds[2]->stop();
        }

        update();
    });
    //宠物动作变换计时器
    QTimer* petTimer=new QTimer(this);  //palyTime
    petTimer->start(PETSPEED);
    connect(petTimer,&QTimer::timeout,[=](){
        playAction++;
        upAction--;
        downAction--;
        leftAction++;
        rightAction++; 
        sickOrHungerAction++;
        update();
    });
    //睡觉动作变换计时器
    QTimer* petSleepTimer=new QTimer(this);
    petSleepTimer->start(PETSLEEPSPEED);
    connect(petSleepTimer,&QTimer::timeout,[=](){
        sleepAction++;
    });
    //睡觉活力恢复机制：每小时活力值+1
    QTimer* sleepTimer= new QTimer(this);
    sleepTimer->start(TIMESPEED);
    connect(sleepTimer,&QTimer::timeout,this,&Bedroom::sleepRule);
}


//*****绘图*******//
void Bedroom::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font;
    font.setPointSize(10);
    p.setFont(font);
    p.setPen(QColor(25,202,173));
    //背景
   p.drawPixmap(rect(),QPixmap(":/new/prefix6/bedroom/bedroom.jpg"));
   p.drawPixmap(360,240,450,400,QPixmap(":/new/prefix6/bedroom/bed.png"));
   p.drawPixmap(928,132,110,110,QPixmap(":/new/prefix6/bedroom/leimu.png"));

    //显示心情值
    int mood=pet->getMood();
    for(int i=0;i<mood;i++){
        p.drawPixmap(117+i*32,15,30,38,QPixmap(":/new/prefix2/playroom/mood.png"));
    }
    //显示健康(生命)值
    int health=pet->getHealth();
    for(int i=0;i<health;i++){
        p.drawPixmap(383+i*32,15,30,38,QPixmap(":/new/prefix2/playroom/health.png"));
    }
    //显示饥饿值
    int hunger=pet->getHunger();
    for(int i=0;i<hunger;i++){
        p.drawPixmap(655+i*32,15,30,38,QPixmap(":/new/prefix2/playroom/hunger.png"));
    }
    //显示活力值
    int active=pet->getActive();
    for(int i=0;i<active;i++){
        p.drawPixmap(928+i*32,15,30,38,QPixmap(":/new/prefix2/playroom/active.png"));
    }

    //显示昵称
    if(!sleepMove)   p.drawText(petx+pet->getWidth()/2-24,pety-10,pet->getName());
    //显示宠物
    if(!sleepMove){
        if(playing){
            if(pet->getHealth()>2&&pet->getHunger()>2){
                if(playAction>39) playAction=0;
                p.drawPixmap(petx,pety,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/%1_%2 副本.png").arg(appearance).arg(playAction)));
            }else{
                if(sickOrHungerAction>96) sickOrHungerAction=88;
                p.drawPixmap(petx,pety,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/sick/%1_%2 副本.png").arg(appearance).arg(sickOrHungerAction)));
            }
        }else if(upMove){
            if(upAction<19) upAction=24;
            p.drawPixmap(petx,pety,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/upAction/%1_%2 副本.png").arg(appearance).arg(upAction)));
        }else if(downMove){
            if(downAction<=39) downAction=44;
            p.drawPixmap(petx,pety,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/donwAction/%1_%2 副本.png").arg(appearance).arg(downAction)));
        }else if(leftMove){
            if(leftAction>54) leftAction=50;
            p.drawPixmap(petx,pety+6,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/leftAction/%1_%2 副本.png").arg(appearance).arg(leftAction)));
        }else if(rightMove){
            if(rightAction>54) rightAction=50;
            p.drawPixmap(petx,pety+6,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix2/playroom/rightAction/%1_%2 副本.png").arg(appearance).arg(rightAction)));
        }
    }else{
            if(sleepAction>63) sleepAction=60;
            p.drawPixmap(642-pet->getWidth(),458-pet->getHeight(),pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix6/bedroom/sleepAction/%1_%2 副本.png").arg(appearance).arg(sleepAction)));
            p.drawPixmap(642,458-pet->getHeight()-40,QPixmap(":/new/prefix6/bedroom/zzz.png"));
    }

}


//*****睡觉恢复机制********//
void Bedroom::sleepRule(){
    static int count=0;
    if(sleepMove) count++;
    if(count>=HOUR){  //睡觉时活力值每小时+1
        count=0;
        if(pet->getActive()<5){
            pet->setActive(pet->getActive()+1);
        }
    }
    //皮肤
    if(pet->getAge()<10){
      appearance="Yangpa";
    } else  if(pet->getAge()<20){
        appearance="Pasery";
        pet->setWidth(90);
        pet->setHeight(100);
    }else{
        appearance="Doobu";
        pet->setWidth(100);
        pet->setHeight(120);
    }
}

//*******控制宠物移动********//
void Bedroom::keyPressEvent(QKeyEvent *e){
          if(!e->isAutoRepeat()){
              sounds[3]->play();
          }
          playing=false;
          if(e->key()==Qt::Key_W){  //向上走
                upMove=true;
                if(pety>=430&&pety<=height()-pet->getHeight()){

                    pety-=MOVESPEED;
                    if(pety<430){
                        pety=430;
                    }
                }
          }else if(e->key()==Qt::Key_S){ //向下走
              downMove=true;
              if(pety>=430&&pety<=height()-100){
                  pety+=MOVESPEED;
                  if(pety>height()-pet->getHeight()){
                      pety=height()-pet->getHeight();
                  }
              }
               qDebug()<<"Down";
          }else if(e->key()==Qt::Key_D){  //向右走
                   rightMove=true;
                  if(petx>=0&&petx<=width()-pet->getWidth()){
                      petx+=MOVESPEED;
                      if(petx>width()-pet->getWidth()){
                         petx=width()-pet->getWidth();
                      }
                   }
          }else if(e->key()==Qt::Key_A){  //向左走
              leftMove=true;
              if(petx>=0&&petx<=width()-pet->getWidth()){
                  petx-=MOVESPEED;
                  if(petx<0){
                      petx=0;
                  }
              }
          }else{
              playAction=0;
              playing=true;
              upMove=false;
              downMove=false;
              rightMove=false;
              leftMove=false;
          }
          //重绘
          update();//不要放在绘图事件中，不然会很卡
}

//******键盘释放事件********//
void Bedroom::keyReleaseEvent(QKeyEvent* e){
    if(!e->isAutoRepeat()){
        sounds[3]->stop();
        playAction=0;
        playing=true;
        upMove=false;
        downMove=false;
        rightMove=false;
        leftMove=false;
    }
}

//*********更换鼠标图案********//
void Bedroom::mouseMoveEvent(QMouseEvent* event)
{
//    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
    QPoint mousepos = event->pos();

    //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
    if(mousepos.x() > 0 && mousepos.x() < width() && mousepos.y() > 0 && mousepos.y() < height())
    {
        //-1,-1表示热点位于图片中心
        //0,0表示热点位与图片原点
        QCursor *myCursor=new QCursor(QPixmap(":/new/prefix1/backImage/mouse.png"),0,0);
        this->setCursor(*myCursor);
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
    }
}

