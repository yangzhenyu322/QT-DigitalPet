#include "exerciseroom.h"

#include <QPainter>
#include <QTimer>
#include<QDebug>

ExerciseRoom::ExerciseRoom(QWidget *parent,Pet* pet) : QWidget(parent)
{
    this->pet=pet;
    //************布局***********//
    backBt=new QPushButton(this);
    exerBt=new QPushButton(this);
    moodLabel=new QLabel(this);
    moodLabel->setText("心情：");
    healthLabel=new QLabel(this);
    healthLabel->setText("健康：");
    hungerLabel=new QLabel(this);
    hungerLabel->setText("能量：");
    activeLabel=new QLabel(this);
    activeLabel->setText("活力：");
    pProgressBar= new QProgressBar(this);
    //bgm+音效
    sounds[1]=new QSound("../BroadBean/sounds/button/button6.wav",this);
    sounds[2]=new QSound("../BroadBean/sounds/walk/走路.wav",this);

    //************样式***********//
    setWindowTitle("体育馆");
    setFixedSize(1135,640);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
    //按钮样式
    backBt->move(50,567);
    backBt->setStyleSheet({"border-image:url(:/new/prefix6/bedroom/back.png)"});
    backBt->setAutoFillBackground(true);
    backBt->setFixedSize(80,60);
    exerBt->move(164,568);
    exerBt->setStyleSheet({"border-image:url(:/new/prefix8/exerciseroom/play.png)"});
    exerBt->setAutoFillBackground(true);
    exerBt->setFixedSize(110,55);
    //锻炼进度
    pProgressBar->setOrientation(Qt::Horizontal);  // 水平方向
    pProgressBar->setMinimum(0);  // 最小值
    pProgressBar->setMaximum(100);  // 最大值
    pProgressBar->hide();
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

    //*********信号与槽**********//
    //返回主界面
    connect(backBt,&QPushButton::clicked,[=](){
            sounds[1]->play();
            if(!isExercising) emit backToPlay();
    });
    //锻炼
    connect(exerBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        static int i=0;
        i++;
        if(i%2==1){
            isExercising=true;
            pProgressBar->show();
        }
        else{
            isExercising=false;
            pProgressBar->hide();
        }
    });
    //宠物动作变换
    QTimer* petTimer=new QTimer(this);  //palyTime
    petTimer->start(PETSPEED);
    connect(petTimer,&QTimer::timeout,[=](){
        playAction++;
        upAction--;
        downAction--;
        leftAction++;
        rightAction++;
        sleepAction++;
        sickOrHungerAction++;
        exerAction++;
        update();
    });
    //锻炼一个小时将活力值+1状态
    QTimer* exerTimer= new QTimer(this);
    exerTimer->start(TIMESPEED);
    connect(exerTimer,&QTimer::timeout,this,&ExerciseRoom::exerRule);
}


   //*************绘图*************//
void ExerciseRoom::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font;
    font.setPointSize(10);
    p.setFont(font);
    p.setPen(QColor(25,202,173));
    //背景
   p.drawPixmap(rect(),QPixmap(":/new/prefix9/exerciseroom/exerciseRoom.png"));
    //锻炼进度条
   pProgressBar->move(petx-(78-pet->getWidth())/2,pety-28);
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
    if(!isExercising){
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
    }else{
        if(exerAction>87) exerAction=56;
        p.drawPixmap(petx,pety+6,pet->getWidth(),pet->getHeight(),QPixmap(tr(":/new/prefix3/petImages/%1/%2_%3 副本.png").arg(file).arg(appearance).arg(exerAction)));
    }
}

//***********锻炼恢复机制*********//
void ExerciseRoom::exerRule(){
    static int count=0;
    if(isExercising&&pet->getActive()<5) count++;
    if(count>=HOUR/2){
        count=0;
        if(pet->getActive()<5){
            pet->setActive(pet->getActive()+1);
        }
    }
    pProgressBar->setValue((count*1.0/HOUR)*2*100);  // 当前进度
    //皮肤
    if(pet->getAge()<10){
      appearance="Yangpa";
      file="child";
    } else  if(pet->getAge()<20){
        appearance="Pasery";
        file="youth";
        pet->setWidth(90);
        pet->setHeight(100);
    }else{
        file="adult";
        appearance="Doobu";
        pet->setWidth(100);
        pet->setHeight(120);
    }
}

//***********键盘控制宠物移动事件************//
void ExerciseRoom::keyPressEvent(QKeyEvent *e){
           if(!e->isAutoRepeat()){
               sounds[2]->play();
               sounds[2]->setLoops(-1);
           }
          playMove=false;
          if(e->key()==Qt::Key_W){  //向上走
                upMove=true;
                if(pety>=420-pet->getHeight()&&pety<=height()-pet->getHeight()-65){

                    pety-=MOVESPEED;
                    if(pety<420-pet->getHeight()){
                        pety=420-pet->getHeight();
                    }
                }
          }else if(e->key()==Qt::Key_S){ //向下走
              downMove=true;
              if(pety>=420-pet->getHeight()&&pety<=height()-pet->getHeight()-65){
                  pety+=MOVESPEED;
                  if(pety>height()-pet->getHeight()-65){
                      pety=height()-pet->getHeight()-65;
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

//**********键盘释放事件*************//
void ExerciseRoom::keyReleaseEvent(QKeyEvent* e){
    if(!e->isAutoRepeat()){
        sounds[2]->stop();
    }
    playAction=0;
    playMove=true;
    upMove=false;
    downMove=false;
    rightMove=false;
    leftMove=false;
}

//**********鼠标移动事件************//
void ExerciseRoom::mouseMoveEvent(QMouseEvent* event)
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

