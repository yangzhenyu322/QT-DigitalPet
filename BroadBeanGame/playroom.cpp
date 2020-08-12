#include "playroom.h"

#include <QPainter>
#include <QVBoxLayout>
#include<QImage>
#include <QDebug>
#include <QMovie>

Playroom::Playroom(QWidget *parent,Pet* pet) : QWidget(parent)
{\
    this->pet=pet;
    //其它窗口
     bedroom=new Bedroom(nullptr,pet);
     entertainmentroom=new entertainment(nullptr,pet);
     kitroom=new Kitchenroom(nullptr,pet);
     exerroom=new ExerciseRoom(nullptr,pet);
     //*********布局***********//
    //界面操作
    QVBoxLayout* layout=new QVBoxLayout(this);
    QHBoxLayout* layout1=new QHBoxLayout;
    QHBoxLayout* layout2=new QHBoxLayout;
    QVBoxLayout* layout3=new QVBoxLayout;
    QHBoxLayout* layout4=new QHBoxLayout;
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    //宠物的数值显示
     moodLabel=new QLabel("心情：");
     healthLabel=new QLabel("健康：");
     hungerLabel=new QLabel("能量：");
     activeLabel=new QLabel("活力：");
     layout1->addWidget(moodLabel);
     layout1->addWidget(healthLabel);
     layout1->addWidget(hungerLabel);
     layout1->addWidget(activeLabel);
    //时间
     timeLine=new QLineEdit("时间");
     QSpacerItem* spacer1=new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Minimum);
     layout2->addWidget(timeLine);
     layout2->addSpacerItem(new QSpacerItem(950, 20));//使用弹簧控制部件水平位置
     //宠物信息
     nameLabel=new QLabel ("名字："+pet->getName());
     stateLabel=new QLabel ("状态："+pet->getState());
     weightLabel=new QLabel (tr("体重：%1 kg").arg(pet->getWeight()));
     ageLabel=new QLabel(tr("年龄：%1 岁").arg(pet->getAge()));
     spaceLabel=new QLabel("    ");
     layout3->addWidget(nameLabel);
     layout3->addWidget(stateLabel);
     layout3->addWidget(weightLabel);
     layout3->addWidget(ageLabel);
     layout3->addWidget(spaceLabel);
     nameLabel->hide();
     stateLabel->hide();
     weightLabel->hide();
     ageLabel->hide();
    //界面操作
     messageBt=new QPushButton;
     bedBt=new QPushButton;
     amuseBt=new QPushButton;
     eatBt=new QPushButton;
     exciseBt=new QPushButton;
     cureBt=new QPushButton;
     backBt=new QPushButton;
     layout4->addWidget(messageBt);
     layout4->addWidget(bedBt);
     layout4->addWidget(amuseBt);
     layout4->addWidget(eatBt);
     layout4->addWidget(exciseBt);
     layout4->addWidget(cureBt);
     layout4->addWidget(backBt);
     //重新开始按钮
     restartBt=new QPushButton(this);
     //bgm+按钮
     sounds[0]=new QSound("../BroadBean/sounds/bgm/滑雪大冒险.wav",this);
     sounds[0]->setLoops(-1);
     sounds[1]=new QSound("../BroadBean/sounds/button/button3.wav",this);
     sounds[2]=new QSound("../BroadBean/sounds/recover/恢复5.wav",this);
     sounds[3]=new QSound("../BroadBean/sounds/walk/走路.wav",this);

    //********************样式********************//
     //主窗体
    setWindowTitle("娱乐室");
    // setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去除表框
    setFixedSize(1135,640);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
    //宠物的属性值
    moodLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:#D24D57;font-weight:bold");
    healthLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:#D24D57;font-weight:bold");
    hungerLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:#D24D57;font-weight:bold");
    activeLabel->setStyleSheet("font: 25px/1.5 '华文彩云',Helvetica,Arial,sans-serif;color:#D24D57;font-weight:bold");
    moodLabel->setFixedSize(225,40);
    healthLabel->setFixedSize(225,40);
    hungerLabel->setFixedSize(225,40);
    activeLabel->setFixedSize(225,40);
    //时间
    timeLine->setFixedSize(80,50);
    timeLine->setStyleSheet("border:5px double rgb(58,212,47);border-radius:20");
    timeLine->setReadOnly(true);
    timeLine->setAlignment(Qt::AlignCenter);
    //宠物信息
    nameLabel->setStyleSheet("font: 20px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold");
    stateLabel->setStyleSheet("font: 20px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold");
    weightLabel->setStyleSheet("font: 20px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold");
    ageLabel->setStyleSheet("font: 20px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold;");
    //界面操作
    messageBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/message.png)"});
    messageBt->setAutoFillBackground(true);
    messageBt->setFixedSize(80,60);
    bedBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/bedroom.png)"});
    bedBt->setAutoFillBackground(true);
    bedBt->setFixedSize(80,60);
    amuseBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/amuse.png)"});
    amuseBt->setAutoFillBackground(true);
    amuseBt->setFixedSize(80,60);
    eatBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/kitchen.png)"});
    eatBt->setAutoFillBackground(true);
    eatBt->setFixedSize(80,60);
    exciseBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/exciseroom.png)"});
    exciseBt->setAutoFillBackground(true);
    exciseBt->setFixedSize(80,60);
    cureBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/cure.png)"});
    cureBt->setAutoFillBackground(true);
    cureBt->setFixedSize(80,60);
    backBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/back.png)"});
    backBt->setAutoFillBackground(true);
    backBt->setFixedSize(80,60);
//    uploadLabel->hide();
    //restart按钮
    restartBt->move(522,400);
    restartBt->setStyleSheet({"border-image:url(:/new/prefix2/playroom/startOver/newGame.png)"});
    restartBt->setAutoFillBackground(true);
    restartBt->setFixedSize(100,100);
    restartBt->hide();

    //************************信号与槽**********************//
    //信息
    connect(messageBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        QTimer::singleShot(300,this,[=](){
            static int show=0;
            if(show>1) show=0;
            if(show==0){
                nameLabel->show();
                stateLabel->show();
                weightLabel->show();
                ageLabel->show();
                spaceLabel->hide();
                showInfo=true;
            }else{
                nameLabel->hide();
                stateLabel->hide();
                weightLabel->hide();
                ageLabel->hide();
                spaceLabel->show();
                showInfo=false;
            }
            show++;
            update();
        });
    });
    //卧室
    connect(bedBt,&QPushButton::clicked,[=](){
        if(pet->getHealth()>0){
            sounds[1]->play();
            QTimer::singleShot(300,this,[=](){
                sounds[0]->stop();
                hide();
                bedroom->sounds[0]->play();
                bedroom->setGeometry(this->geometry());
                bedroom->show();
                update();
            });
        }
    });
    connect(bedroom,&Bedroom::backToPlay,[=](){
        bedroom->sounds[0]->stop();
        bedroom->hide();
        setGeometry(bedroom->geometry());
        show();
        sounds[0]->play();
        update();
    });
    //娱乐室
    connect(amuseBt,&QPushButton::clicked,[=](){
        if(pet->getHealth()>0){
            sounds[1]->play();
            QTimer::singleShot(300,this,[=](){
                hide();
                entertainmentroom->setGeometry(this->geometry());
                entertainmentroom->show();
                update();
             });
        }
    });
    connect(entertainmentroom,&entertainment::backToPlay,[=](){
        entertainmentroom->hide();
        setGeometry(entertainmentroom->geometry());
        show();
    });
    //用餐
    connect(eatBt,&QPushButton::clicked,[=](){
       if(pet->getHealth()>0){
           sounds[1]->play();
           QTimer::singleShot(300,this,[=](){
               hide();
               kitroom->setGeometry(this->geometry());
               kitroom->show();
               update();
           });
       }
    });
    connect(kitroom,&Kitchenroom::backToPlay,[=](){
        kitroom->hide();
        setGeometry(kitroom->geometry());
        show();
    });
    //锻炼
    connect(exciseBt,&QPushButton::clicked,[=](){
        if(pet->getHealth()>0){
            sounds[1]->play();
            QTimer::singleShot(300,this,[=](){
                hide();
                exerroom->setGeometry(this->geometry());
                exerroom->show();
                 update();
            });
        }
    });
    connect(exerroom,&ExerciseRoom::backToPlay,[=](){
        exerroom->hide();
        setGeometry(exerroom->geometry());
        show();
    });
    //治疗
    connect(cureBt,&QPushButton::clicked,[=](){
        if(pet->getHealth()){
            sounds[2]->play();
            QTimer::singleShot(1000,this,[=](){
                if(pet->getHealth()<5){
                    pet->setHealth(pet->getHealth()+1);
                }
                 update();
            });
        }
    });
    //返回开始界面
    connect(backBt,&QPushButton::clicked,[=](){
        clockTimer->stop();  //时间计时器停止
        petReduceTimer->stop();  //宠物机制计时器停止
        QTimer::singleShot(300,this,[=](){
            emit backToBegin();
        });
    });
    //显示时钟
    connect(clockTimer,&QTimer::timeout,this,&Playroom::clockShow);
    //宠物属性机制
    connect(petReduceTimer,&QTimer::timeout,this,&Playroom::reduceRule);
    //宠物动作变换
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
    //重新开始
    connect(restartBt,&QPushButton::clicked,[=](){
        emit restart();
        restartBt->hide();
        clock=CURRENTHOUE*3600+CURRENTMINUTE*60+CURRENTSECONDS;
    });
}

//*****************初始化*****************//
void Playroom::initDate(bool b){
    if(b){  //新游戏，宠物设置为默认值
        pet->setName("萌馋豆");  //昵称
        pet->setState("健康");   //状态
        pet->setWeight(WEIGHT);      //体重
        pet->setAge(AGE);          //年龄
        pet->setMood(MOOD);       //心情
        pet->setHealth(HEALTH);      //健康
        pet->setHunger(HUNGER);    //饥饿度
        pet->setActive(ACTIVE);      //活力值
        pet->setWidth(WIDTH);      //宠物宽度
        pet->setHeight(HEIGHT);    //宠物高度
    }else{  //宠物从数据库读取上次保存数据
    }
}

//*****************绘图*****************//
void Playroom::paintEvent(QPaintEvent *){
    QPainter p(this);
    QFont font;
    font.setPointSize(10);
    p.setFont(font);
    p.setPen(QColor(25,202,173));

    //显示早上还是晚上
    int hour=clock/3600;
    if(hour>=6&&hour<=17){  //早上
        p.drawPixmap(rect(),QPixmap(":/new/prefix1/backImage/playroom.png")); //早上背景
        p.drawPixmap(142,60,70,60,QPixmap(":/new/prefix2/playroom/sun.png"));  //太阳
    }else{
                QString pixmap_url = ":/new/prefix1/backImage/playroomNight.png";
                QImage image(pixmap_url);//定义QImage对象，读取图片
                if(image.isNull()){
                    qDebug()<<"读取图片错误";
                }
                else{
                    image.save(pixmap_url,"PNG");
                }
        p.drawPixmap(rect(),QPixmap(pixmap_url));
        p.drawPixmap(142,60,70,50,QPixmap(":/new/prefix2/playroom/moon.png"));  //晚上月亮
    }
    if(showInfo){    //信息框
        p.setBrush(QBrush(QColor(253,246,227,150)));
        p.drawRect(0,142,155,400);
    }
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
    if(pet->getHealth()>0){    //如果宠物活着
        restartBt->hide();
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
    }else{   //死亡
        //根据QColor中第四个参数设置透明度，此处position的取值范围是0～255
//            p1.fillRect(temp.rect(), QColor(0, 0, 0, position));
//        painter->setOpacity(0.4);//透明度设置
//                painter->drawPixmap(int(sceneRect().left()), int(sceneRect().top()), foreImg);
        p.setOpacity(0.5);
        p.drawPixmap(rect(),QPixmap(":/new/prefix2/playroom/startOver/gameover.png"));
        restartBt->show();
    }
}


//****************键盘控制宠物移动事件******************//
void Playroom::keyPressEvent(QKeyEvent *e){
          //走路音效
            if(!e->isAutoRepeat()){
                sounds[3]->play();
                sounds[3]->setLoops(-1);
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

//*****************键盘释放事件*******************//
void Playroom::keyReleaseEvent(QKeyEvent* e){
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

//********************显示时钟******************//
void Playroom::clockShow(){
    clock++;
    if(clock>=86400) clock=0;
    int hour=clock/3600;
    int minute=(clock%3600)/60;
    int seconds=clock%60;
    QString str1=clock%2==0?" ":":";
    QString str2=hour<10?"0":"";
    QString str3=minute<10?"0":"";
    QString str4=seconds<10?"0":"";
    QString clockStr=str2+QString::number(hour)+str1+str3+QString::number(minute)+str1+str4+QString::number(seconds);
    timeLine->setText(clockStr);
}

//***************宠物属性机制********************//
void Playroom::reduceRule(){
        //属性减少机制
        //count数组前四个分别表示mood、health、hunger、active、
       static int count[8]={0};
       for(int i=0;i<4;i++){
           count[i]++;
       }
       if(pet->getHunger()==0){  //3.	饥饿度为0后，健康值每一天-1
           count[4]++;
       }
       if(pet->getHunger()==0){  //4.	饥饿度为0后，活力值每个小时-1
           count[5]++;
       }
       if(pet->getActive()==0){
           count[6]++;  // 5.	活力值为0后，心情每个小时-1
       }
       if(pet->getMood()==0){  //6.	心情为0后，健康每天-1
           count[7]++;
       }


       if(count[2]>=3*HOUR){   //1.	每三个小时饥饿度-1
           count[2]=0;
           if(pet->getHunger()>0){
               pet->setHunger(pet->getHunger()-1);
           }
       }
       if(count[0]>=12*HOUR){   //2.	心情值两个小时-1
           count[0]=0;
           if(pet->getMood()>0){
               pet->setMood(pet->getMood()-1);
           }
       }
       if(count[4]>=24*HOUR){ //3.	饥饿度为0后，健康值每一天-1
           count[4]=0;
           if(pet->getHealth()>0){
               pet->setHealth(pet->getHealth()-1);
           }
       }
       if(count[5]>=HOUR){  //4.	饥饿度为0后，活力值每个小时-1
           count[5]=0;
           if(pet->getActive()>0){
               pet->setActive(pet->getActive()-1);
           }
       }
       if(count[6]>=HOUR){  //5.	活力值为0后，心情两个小时-1
           count[6]=0;
           if(pet->getMood()>0){
               pet->setMood(pet->getMood()-1);
           }
       }
       if(count[7]>12*HOUR){  //6.	心情为0后，健康每天-1
           count[7]=0;
           if(pet->getHealth()>0){
               pet->setHealth(pet->getHealth()-1);
           }
       }
       //属性状态机制
       if(pet->getHunger()<=2){
           pet->setState("饥饿");
       }
       if(pet->getHealth()<=2&&pet->getHealth()>0){
           pet->setState("生病");
       }
       if(pet->getHealth()==0){
           pet->setState("死亡");
       }
       if(pet->getHealth()>2&&pet->getHunger()>2){
           pet->setState("健康");
       }
       //属性增加机制
       //年龄、体重
       static int ageCount=0;
       ageCount++;
       if(ageCount>=24*HOUR){
           ageCount=0;
           pet->setAge(pet->getAge()+1);
           pet->setHeight(pet->getHeight()+0.1);
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
       //更新宠物信息
       nameLabel->setText("名字："+pet->getName());
       stateLabel->setText("状态："+pet->getState());
       weightLabel->setText(tr("体重：%1 kg").arg(pet->getWeight()));
       ageLabel->setText(tr("年龄：%1 岁").arg(pet->getAge()));
}

//*********更新当前时间**********//
void Playroom::setClock(int time){
    clock=time;
}

//************更换鼠标图案********//
void Playroom::mouseMoveEvent(QMouseEvent* event)
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
