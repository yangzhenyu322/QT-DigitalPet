#include "kitchenroom.h"
#include<QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>

Kitchenroom::Kitchenroom(QWidget *parent,Pet* pet) : QWidget(parent)
{
    this->pet=pet;
    //*********布局***********//
    backBt=new QPushButton(this);
    playBt=new QPushButton(this);
    moodLabel=new QLabel(this);
    moodLabel->setText("心情：");
    healthLabel=new QLabel(this);
    healthLabel->setText("健康：");
    hungerLabel=new QLabel(this);
    hungerLabel->setText("能量：");
    activeLabel=new QLabel(this);
    activeLabel->setText("活力：");
    //食物
    for(int i=0;i<4;i++){
        foodBt[i]=new QPushButton(this);
    }
    //狗
    dogBt=new QPushButton(this);

    //**************样式***********//
    setWindowTitle("厨房");
    setFixedSize(1135,640);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
    //按钮样式
    backBt->move(50,550);
    backBt->setStyleSheet({"border-image:url(:/new/prefix6/bedroom/back.png)"});
    backBt->setAutoFillBackground(true);
    backBt->setFixedSize(80,60);
    playBt->move(164,530);
    playBt->setStyleSheet({"border-image:url(:/new/prefix8/kitchen/eat.png);background-color:rgb(160,204,215);border-radius:10"});
    playBt->setAutoFillBackground(true);
    playBt->setFixedSize(85,75);
    for(int i=0;i<4;i++){
        foodBt[i]->move(166+200*i,70);
        foodBt[i]->setAutoFillBackground(true);
//        foodBt[i]->setFixedSize(160,75);
        foodBt[i]->hide();
    }
    foodBt[0]->setStyleSheet(
                            "QPushButton{border-image:url(:/new/prefix8/kitchen/food1.png);background-color:#bbffcc;border-radius:10}"
                            "QPushButton:hover{background-color:rgb(255,205,66);}"
                             "QPushButton:pressed{background-color:rgb(220,76,63);}"
                             );
    foodBt[1]->setStyleSheet(
                            "QPushButton{border-image:url(:/new/prefix8/kitchen/food2.png);background-color:#bbffcc;border-radius:10}"
                            "QPushButton:hover{background-color:rgb(255,205,66);}"
                             "QPushButton:pressed{background-color:rgb(220,76,63);}"
                             );
    foodBt[2]->setStyleSheet(
                            "QPushButton{border-image:url(:/new/prefix8/kitchen/food3.png);background-color:#bbffcc;border-radius:10}"
                            "QPushButton:hover{background-color:rgb(255,205,66);}"
                             "QPushButton:pressed{background-color:rgb(220,76,63);}"
                             );
    foodBt[3]->setStyleSheet(
                            "QPushButton{border-image:url(:/new/prefix8/kitchen/food4.png);background-color:#bbffcc;border-radius:10}"
                            "QPushButton:hover{background-color:rgb(255,205,66);}"
                             "QPushButton:pressed{background-color:rgb(220,76,63);}"
                             );
    dogBt->move(860,415);
    dogBt->setStyleSheet({"border-image:url(:/new/prefix8/kitchen/dog .png)"});
    dogBt->setAutoFillBackground(true);
    dogBt->setFixedSize(230,180);
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
    //bgm+音效
    sounds[1]=new QSound("../BroadBean/sounds/button/button2.wav",this);
    sounds[2]=new QSound("../BroadBean/sounds/voice/dog.wav",this);
    sounds[3]=new QSound("../BroadBean/sounds/walk/走路.wav",this);
    sounds[4]=new QSound("../BroadBean/sounds/recover/恢复1.wav",this);

    //***********信号与槽************//
     //返回主界面
     connect(backBt,&QPushButton::clicked,[=](){
                sounds[1]->play();
                emit backToPlay();
        });
     //和狗的互动
     connect(dogBt,&QPushButton::clicked,[=](){
          sounds[1]->play();
           static int i=0;
           i++;
           switch (i) {
           case 1:
                    anger=true;
                    text=false;
               break;
           case 2:
                    sounds[2]->play();
                    anger=false;
                    text=true;
               break;
           default:
               i=0;
               anger=false;
               text=false;
               break;
           }
     });
     //吃饭
    connect(playBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        static int i=0;
        i++;
        if(i%2==1){
            for(int i=0;i<4;i++) {
                foodBt[i]->show();
                //scale:缩放效果
                pScaleAnimation[i] = new QPropertyAnimation(foodBt[i], "geometry");
                pScaleAnimation[i]->setDuration(1000);
                pScaleAnimation[i]->setStartValue(QRect(935, 213, 0, 0));
                pScaleAnimation[i]->setEndValue(QRect(166+200*i, 70, 160, 75));
                pScaleAnimation[i]->start();
            }
        }else{
            for(int i=0;i<4;i++) foodBt[i]->hide();
        }
    });
    for(int i=0;i<4;i++){
        connect(foodBt[i],&QPushButton::clicked,[=](){
            sounds[4]->play();
            if(pet->getHunger()<5){       
                pet->setHunger(pet->getHunger()+1);
            }
        });
    }

    //宠物动作变换
    QTimer* petTimer=new QTimer(this);  //palyTime
    petTimer->start(PETSPEED);
    connect(petTimer,&QTimer::timeout,[=](){
        playAction++;
        upAction--;
        downAction--;
        sickOrHungerAction++;
        leftAction++;
        rightAction++;
        update();
    });
    //玩耍机制：可将心情值每20分钟+1
    QTimer* playTimer= new QTimer(this);
    playTimer->start(TIMESPEED);
    connect(playTimer,&QTimer::timeout,this,&Kitchenroom::playRule);
}

//***********绘图**********//
void Kitchenroom::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font;
    font.setPointSize(10);
    p.setFont(font);
    p.setPen(QColor(25,202,173));
    //背景
   p.drawPixmap(rect(),QPixmap(":/new/prefix8/kitchen/kitchen.jpg"));

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
    p.drawText(petx+pet->getWidth()/2-24,pety-10,pet->getName());
    //显示宠物
        if(playMove){
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

      //dog生气
        p.setPen(QColor(28,28,29));
        if(anger) p.drawPixmap(860,415,QPixmap(tr(":/new/prefix8/kitchen/anger.png")));
        if(text) {
            p.drawPixmap(800,415,QPixmap(tr(":/new/prefix8/kitchen/angetText.png")));
            p.drawText(810,435,"莫挨劳资睡觉,");
            p.drawText(810,455,"一边凉快去");
        }
}

//**********键盘控制宠物移动事件***********//
void Kitchenroom::keyPressEvent(QKeyEvent *e){
          if(!e->isAutoRepeat()){
              sounds[3]->play();
              sounds[3]->setLoops(-1);
          }
          playMove=false;
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
              playMove=true;
              upMove=false;
              downMove=false;
              rightMove=false;
              leftMove=false;
          }
          //重绘
          update();//不要放在绘图事件中，不然会很卡
}

//*********键盘释放事件**********//
void Kitchenroom::keyReleaseEvent(QKeyEvent* e){
    if(!e->isAutoRepeat()){
        sounds[3]->stop();
        playMove=true;
        upMove=false;
        downMove=false;
        rightMove=false;
        leftMove=false;
    }
}

//**********吃饭回复机制***********//
void Kitchenroom::playRule(){
    static int count=0;
    count++;

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

//**********鼠标移动事件***********//
void Kitchenroom::mouseMoveEvent(QMouseEvent* event)
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
