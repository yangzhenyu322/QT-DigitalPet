#include "login.h"

#include <QGridLayout>
#include <QPainter>
#include "QSound"
#include <QHostAddress>
#include<QDebug>


Login::Login(QWidget *parent) : QWidget(parent)
{
    //********自动连接连接服务器**********//
    tcpSocket=new QTcpSocket(this);
    connectServer(); //登陆时自动连接服务器（注意：必须先打开服务前再运行此项目）
    //连接服务器成功时提示
    connect(tcpSocket,&QTcpSocket::connected,[=](){
        qDebug()<<"成功与服务器建立好连接";
    });

    //******布局*******//
    w=new Begin(NULL,&pet);
    //主题
    titileLabel=new QLabel(this);
    //登陆有关组件
    label1=new QLabel("账号: ");
    label2=new QLabel("密码: ");
    line1=new QLineEdit;
    line2=new QLineEdit;
    enterBt=new QPushButton;
    exitBt=new QPushButton;
    registerBt=new QPushButton;
    QWidget* layout=new QWidget(this);
    QGridLayout* gridlayout=new QGridLayout(layout);
    gridlayout->addWidget(label1,0,0);
    gridlayout->addWidget(label2,1,0);
    gridlayout->addWidget(line1,0,1);
    gridlayout->addWidget(line2,1,1);
    gridlayout->addWidget(enterBt,3,0,1,2);
    gridlayout->addWidget(exitBt,4,0,1,2);
    gridlayout->addWidget(registerBt,2,0,1,2);
    //加载界面
    QLabel* uploadLabel=new QLabel(this);
    QMovie* movie=new QMovie(":/new/prefix5/login/upload.gif");
    //bgm+音效
    QSound* sounds[2];
    sounds[0]=new QSound("../BroadBean/sounds/bgm/开始界面.wav",this);
    sounds[1]=new QSound("../BroadBean/sounds/button/button2.wav",this);
    sounds[0]->play();
    sounds[0]->setLoops(-1);

    
    //********设置样式************//
    layout->setFixedSize(300,371);
    layout->move(75,140);
    setWindowTitle("登陆");
    setFixedSize(450,600);
    this->setMouseTracking(true);      //设置为不按下鼠标键触发moveEvent
    //主题样式
    titileLabel->setStyleSheet({"border-image:url(:/new/prefix1/backImage/title.png)"});
    titileLabel->setAutoFillBackground(true);
    titileLabel->setFixedSize(100,100);
    titileLabel->move(190,45);
    titileLabel->show();
    //label样式
    label1->setStyleSheet("font: 25px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold");
    label2->setStyleSheet("font: 25px/1.5 '华文彩云';color:rgb(57,61,73);font-weight:bold");
    //设置lineEdit样式
    line1->setStyleSheet("width:200;height:30;font: 17px/1.5 '华文彩云';color:black;background-color:rgb(232,232,238);border-radius:10");
    line2->setStyleSheet("width:200;height:30;font: 17px/1.5 '华文彩云';color:black;background-color:rgb(232,232,238);border-radius:10");
    line2->setEchoMode(QLineEdit::Password);
    //Button样式
    enterBt->setStyleSheet({"border-image:url(:/new/prefix5/login/login.png)"});
    enterBt->setAutoFillBackground(true);
    enterBt->setFixedSize(280,50);
    exitBt->setStyleSheet({"border-image:url(:/new/prefix5/login/exit.png)"});
    exitBt->setAutoFillBackground(true);
    exitBt->setFixedSize(280,140);
    registerBt->setStyleSheet({"border-image:url(:/new/prefix5/login/register.png)"});
    registerBt->setAutoFillBackground(true);
    registerBt->setFixedSize(280,50);
    //加载
    uploadLabel->setMovie(movie);
    uploadLabel->setFixedSize(150,150);
    uploadLabel->move(155,205);
    uploadLabel->setScaledContents(true);
    uploadLabel->hide();

    //****************************信号与槽*******************************//
    //从服务器获取信息
        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
            //获取对方发送的内容
             str=tcpSocket->readAll();
            //追加到编辑区中
            qDebug()<<str;
            if(str.mid(0,4)=="注册成功"){
                qDebug()<<"注册成功";
                message.setText("注册成功！");
                message.setGeometry(this->x()+(this->width()-message.width())/2,this->y()+(this->height()-message.height())/2,300,50);
                message.show();
            }else if(str.mid(0,4)=="注册失败"){
                qDebug()<<"注册失败,该账号已存在";
                //登陆消息样式
                message.setText("注册失败,该账号已存在");   
                message.setGeometry(this->x()+(this->width()-message.width())/2,this->y()+(this->height()-message.height())/2,300,50);
                message.show();
            }else if(str.mid(0,4)=="登陆成功"){
                  //*******加载数据*********//
                  int count=0;
                  int index[10]={0};
                  for(int i=4;i<str.size();i++){
                      if(str.mid(i,1)=="#"){
                          count++;
                          continue;
                      }
                      index[count]++;
                      switch (count) {     //处理服务端返回的数据
                      case 0:
                          break;
                      case 1://name
                          pet.setName(str.mid(4,index[0]));
                          break;
                      case 2://state
                          pet.setState(str.mid(5+index[0],index[1]));
                          break;
                      case 3://weight
                          pet.setWeight(str.mid(6+index[0]+index[1],index[2]).toDouble());
                          break;
                      case 4://age
                          pet.setAge(str.mid(7+index[0]+index[1]+index[2],index[3]).toInt());
                          break;
                      case 5://mood
                          pet.setMood(str.mid(8+index[0]+index[1]+index[2]+index[3],index[4]).toInt());
                          break;
                      case 6://health
                          pet.setHealth(str.mid(9+index[0]+index[1]+index[2]+index[3]+index[4],index[5]).toInt());
                          break;
                      case 7://hunger
                          pet.setHunger(str.mid(10+index[0]+index[1]+index[2]+index[3]+index[4]+index[5],index[6]).toInt());
                          break;
                      case 8://active
                          pet.setActive(str.mid(11+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6],index[7]).toInt());
                          break;
                      case 9://width
                          pet.setWidth(str.mid(12+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6]+index[7],index[8]).toInt());
                          //height
                          int temp=13+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6]+index[7]+index[8];
                          pet.setHeight(str.mid(temp,str.size()-temp+1).toInt());
                          count++;
                          break;
                      }
                  }
                  //存储到数据库中
                  qDebug()<<"读取数据";
                  qDebug()<<pet.getName()<<" "<<pet.getState()<<" "<<pet.getWeight()
                         <<" "<<pet.getAge()<<" "<<pet.getMood()<<" "<<pet.getHealth()<<" "<<pet.getHunger()<<" "<<pet.getActive()<<" "
                        <<pet.getWidth()<<" "<<pet.getHeight();
                    //***********************//

                    //**********登陆*********//
                    isloading=true;
                    update();
                    //设置
                    uploadLabel->show();
                    movie->start();
                    upLoadTimer=new QTimer(this);
                    upLoadTimer->start(2000);
                    connect(upLoadTimer,&QTimer::timeout,[this](){
                        hide();
                        animation->start();
                        w->setGeometry(this->geometry());
                        w->show();
                        upLoadTimer->stop();
                    });
                   //***********************//
            }else if(str.mid(0,4)=="登陆失败"){
                   message.setText("账号密码输入有误, 请核对后重新输入");
                    message.setGeometry(this->x()+(this->width()-message.width())/2,this->y()+(this->height()-message.height())/2,300,50);
                   message.show();
            }
        });
    //注册
    connect(registerBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        tcpSocket->write(QString("注册"+line1->text()+"#"+line2->text()).toUtf8().data());
    });
    //登陆
    animation=new QPropertyAnimation(w, "windowOpacity");
    animation->setDuration(3000);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    connect(enterBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        tcpSocket->write(QString("登陆"+line1->text()+"#"+line2->text()).toUtf8().data());
        //是否登陆成功
        qDebug()<<"是否登陆成功:"<<str.mid(0,4);
    });
    //从开始界面返回
    connect(w,&Begin::backToLogin,[=](){
        setGeometry(w->geometry());
        w->hide();
        show();
        uploadLabel->hide();
        isloading=false;
    });
    //退出
    connect(exitBt,&QPushButton::clicked,[=](){
        sounds[1]->play();
        close();
    });
    //从开始界面返回
    connect(w,&Begin::backToLogin,[=](){
        setGeometry(w->geometry());
        w->hide();
        show();
        uploadLabel->hide();
        isloading=false;
    });
    //进入playroom时停止登陆界面bgm
    connect(w,&Begin::stopBGM,[=](){
        sounds[0]->stop();
    });
    //从playroom返回开始界面时重新播放bgm
    connect(w,&Begin::playBGM,[=](){
        sounds[0]->play();
    });
    //从palyroom返回开始界面时存储数据到服务端
    connect(w,&Begin::saveData,[=](){
        //发送数据到服务端并更新账号数据
        tcpSocket->write(QString("保存"+pet.getName()+"#"+pet.getState()+"#"
                                         +QString::number(pet.getWeight())+"#"+QString::number(pet.getAge())
                                         +"#"+QString::number(pet.getMood())+"#"+QString::number(pet.getHealth())
                                         +"#"+QString::number(pet.getHunger())+"#"+QString::number(pet.getActive())
                                         +"#"+QString::number(pet.getWidth())+"#"+QString::number(pet.getHeight())).toUtf8().data());
    });
}

//*********连接服务器********//
void Login::connectServer(){
        //获取服务器端口ip和端口
        QString ip=IP;
        qint16 port=PORT;
        //主动和服务建立连接
        tcpSocket->connectToHost(QHostAddress(ip),port);
}
//********绘画***********//
void Login::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/backImage/login.jpg"));
    if(isloading) {
        p.setBrush(QBrush(QColor(240,240,245,180)));
        p.drawRect(rect());
    }
}
//*********鼠标形状******//
void Login::mouseMoveEvent(QMouseEvent* event)
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



