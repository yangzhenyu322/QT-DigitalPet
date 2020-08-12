#ifndef PERTCPSERVER_H
#define PERTCPSERVER_H

#define PORT  7777  //服务器端口号
#include <QWidget>
#include<QTcpServer> //监听套接字
#include<QTcpSocket> //通信套接字
#include<pet.h>
#include<petdatabse.h>

class PerTcpServer : public QWidget
{
    Q_OBJECT

public:
    PerTcpServer(QWidget *parent = 0);
    ~PerTcpServer();

private:
    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字
    Pet pet;
    PetDatabse db;
};

#endif // PERTCPSERVER_H
