#include "begin.h"

#include <QVBoxLayout>
#include <QPainter>
#include<QPixmap>
#include <QTimer>
#include <QMovie>
#include<QSound>
#include<QColor>

Begin::Begin(QWidget *parent,Pet* pet)
    : QMainWindow(parent)
{
    this->pet=pet;
    playroom=new Playroom(NULL,pet);
    //******暂时保存当前数据********/
    tempSaveData();

    //**********布局************//
    //标题
    titileLabel=new QLabel(this);
    //控件
    QWidget* centralWidget=new QWidget;
    QWidget* allLayout=new QWidget(centralWidget);
    QVBoxLayout* layout=new QVBoxLayout(allLayout);
    button1=new QPushButton("载入游戏");
    button2=new QPushButton("新游戏");
    button3=new QPushButton("返回登陆界面");
    button4=new QPushButton("退出游戏");
    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);
    layout->addWidget(button4);
    //宠物动图
    label1=new QLabel(this);
    QMovie* moive1=new QMovie(":/new/prefix4/gif/pet4.gif");
    label1->setMovie(moive1);
    moive1->start();
    label1->setScaledContents(true);
    label1->setFixedSize(80,110);
    label1->move(300,400);
    label2=new QLabel(this);
    QMovie* moive2=new QMovie(":/new/prefix4/gif/pet1.gif");
    label2->setMovie(moive2);
    moive2->start();
    label2->setScaledContents(true);
    label2->setFixedSize(80,110);
    label2->move(737,400);
    label3=new QLabel(this);
    QMovie* moive3=new QMovie(":/new/prefix4/gif/pet2.gif");
    label3->setMovie(moive3);
    moive3->start();
    label3->setScaledContents(true);
    label3->setFixedSize(120,100);
    label3->move(430,400);
    //音效
    QSound* sounds=new QSound("../BroadBean/sounds/button/button1.wav",this);


    //**********样式***********//
    //设置主界面样式
    setWindowTitle("开始界面");
    setCentralWidget(centralWidget);
    setFixedSize(1135,640);
    //设置为不按下鼠标键触发moveEvent
    this->setMouseTracking(true);
    //主题样式
    titileLabel->setStyleSheet({"border-image:url(:/new/prefix1/backImage/title.png)"});
    titileLabel->setAutoFillBackground(true);
    titileLabel->setFixedSize(100,100);
    titileLabel->move(516,34);
    titileLabel->show();
    //设置中心窗口样式
    button1->setStyleSheet("background-color:rgb(119,119,119);border-radius:10");
    button1->setFixedSize(350,50);
    button2->setStyleSheet("background-color:rgb(119,119,119);border-radius:10");
    button2->setFixedSize(350,50);
    button3->setStyleSheet("background-color:rgb(119,119,119);border-radius:10");
    button3->setFixedSize(350,50);
    button4->setStyleSheet("background-color:rgb(119,119,119);border-radius:10");
    button4->setFixedSize(350,50);
    //设置allLayout样式
    allLayout->resize(574,331);
    allLayout->move(370,110);

    //*********信号与槽*********//
    //载入游戏
    animation=new QPropertyAnimation(playroom, "windowOpacity");   //载入游戏时的动画
    animation->setDuration(2000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    connect(button1,&QPushButton::clicked,[=](){    //点击进入开始界面
        emit this->loadGame();
        playroom->sounds[0]->play();
        sounds->play();
        emit stopBGM();
        hide();
        animation->start();
        playroom->setGeometry(this->geometry());
        playroom->show();
        playroom->initDate(false);
        playroom->clockTimer->start(TIMESPEED);
        playroom->petReduceTimer->start(TIMESPEED);
     });
    //新游戏
    connect(button2,&QPushButton::clicked,[=](){  //点击开始新的游戏
        playroom->sounds[0]->play();
        sounds->play();
        emit stopBGM();
        hide();
        animation->start();
        playroom->setGeometry(this->geometry());
        playroom->show();
        playroom->initDate(true);
        playroom->setClock(CURRENTHOUE*3600+CURRENTMINUTE*60+CURRENTSECONDS);
        playroom->clockTimer->start(TIMESPEED);
        playroom->petReduceTimer->start(TIMESPEED);
    });
    //返回登陆界面
    connect(button3,&QPushButton::clicked,[=](){
        sounds->play();
        emit backToLogin();
    });
    //退出游戏
    connect(button4,&QPushButton::clicked,[=](){
        sounds->play();
        close();
    });
    //从家返回开始界面
    connect(playroom,&Playroom::backToBegin,[=](){
        playroom->hide();
        setGeometry(playroom->geometry());
        show();
        playroom->sounds[0]->stop();
        emit playBGM();
        emit saveData();
        //暂时保存当前数据
        tempSaveData();
    });
    //child-pet在开始页面动态显示的计时器
    QTimer* timer=new QTimer(this);
    timer->start(120);
    connect(timer,QTimer::timeout,[=](){
        count++;
        update();
    });
    //重新开始
    connect(playroom,&Playroom::restart,[=](){
        pet->setName(tempPet.getName());
        pet->setState(tempPet.getState());
        pet->setWeight(tempPet.getWeight());
        pet->setAge(tempPet.getAge());
        pet->setMood(tempPet.getMood());
        pet->setHealth(tempPet.getHealth());
        pet->setHunger(tempPet.getHunger());
        pet->setActive(tempPet.getActive());
        pet->setWidth(tempPet.getWidth());
        pet->setHeight(tempPet.getHeight());
    });
}

//**********绘图事件*********//
void Begin::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/backImage/begin.jpg"));
    if(count>104){
        count=0;
    }
    p.drawPixmap(630,429,QPixmap(tr(":/new/prefix3/petImages/child/Yangpa_%1 副本.png").arg(count)));
    QFont font("宋体",10,QFont::Bold,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    p.setFont(font);  //实用字体
    p.setPen(QPen(Qt::white)); //设置画笔颜色
    //当前版本
    p.drawText(880,600,"Version 1.0.1");
}

//***********鼠标移动事件********//
void Begin::mouseMoveEvent(QMouseEvent* event)
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

//********在开始界面暂时保存宠物当前数据（方便宠物的复活）***********//
void Begin::tempSaveData(){
    tempPet.setName(pet->getName());
    tempPet.setState(pet->getState());
    tempPet.setWeight(pet->getWeight());
    tempPet.setAge(pet->getAge());
    tempPet.setMood(pet->getMood());
    tempPet.setHealth(pet->getHealth());
    tempPet.setHunger(pet->getHunger());
    tempPet.setActive(pet->getActive());
    tempPet.setWidth(pet->getWidth());
    tempPet.setHeight(pet->getHeight());
}

Begin::~Begin()
{

}

