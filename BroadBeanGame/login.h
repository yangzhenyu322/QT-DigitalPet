#ifndef LOGIN_H
#define LOGIN_H

#include <QLabel>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPushButton>
#include <QWidget>
#include<begin.h>
#include <QMovie>
#include<define.h>
#include <QPropertyAnimation>
#include<QMouseEvent>
#include<QPoint>
#include<QCursor>
#include<pet.h>
#include<loginmessage.h>
#define IP "127.0.0.1"
#define PORT  7777  //服务器端口号
#include<QTcpSocket> //通信套接字
#include <QLineEdit>


class Login : public QWidget
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent* event);
    void connectServer();  //连接到服务器
signals:

public slots:

private:
    //主窗口
    Begin* w;
    //主题
    //标题
    QLabel* titileLabel;
    //组件
    QLabel *label1,*label2;
    QLineEdit *line1,*line2;
    QPushButton *enterBt,*exitBt,*registerBt;
    //加载
    QTimer* upLoadTimer;
    QPropertyAnimation* animation;
    bool isloading=false;
    //宠物
    Pet pet;
    //客户端套接字
    QTcpSocket *tcpSocket;
    //显示登陆状态
    LoginMessage message;
    //从服务器获取内容
    QString str;
};

#endif // LOGIN_H


