#include "pertcpserver.h"
#include<QDebug>

PerTcpServer::PerTcpServer(QWidget *parent)
    : QWidget(parent)
{
    tcpSocket=new QTcpSocket(this);
    //监听套接字，置顶父对象让其自动回收空间
    tcpServer=new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,PORT); //Any表示绑定当前网卡的任意IP地址，6666为端口号
    connect(tcpServer,&QTcpServer::newConnection,[=](){
        //去除建立好连接的套接字
        tcpSocket = tcpServer->nextPendingConnection();
        //获取对方的IP和端口
        QString ip=tcpSocket->peerAddress().toString();
        qint16 port=tcpSocket->peerPort();
        QString temp=QString("[%1:%2]:成功连接").arg(ip).arg(port);
        qDebug()<<temp;

        connect(tcpSocket,&QTcpSocket::readyRead,[=](){
                QString str=tcpSocket->readAll();
                qDebug()<<str;
                if(str.mid(0,2)=="注册"){
                     QString account="";
                     QString password="";
                     int count=0;
                     for(int i=2;i<str.size();i++){
                         if(str.mid(i,1)=="#"){
                             count++;
                             continue;
                         }
                         if(count==0){
                             account+=str.mid(i,1);
                             continue;
                         }
                         if(count==1){
                             password=str.mid(i,str.size()-i+1);
                             break;
                         }
                     }
                     qDebug()<<"账号"<<account;
                     qDebug()<<"密码"<<password;
                     if(db.isAccountExist(account)){  //账号存在
                            tcpSocket->write(QString("注册失败").toUtf8().data());
                     }else{  //账号不存在,注册成功
                         //注册账号
                         Pet pet;
                         pet.setAccount(account);
                         pet.setPassword(password);
                         db.insertIntable(pet);
                         //提示客户端注册成功
                         tcpSocket->write(QString("注册成功").toUtf8().data());
                     }
                }else if(str.mid(0,2)=="登陆"){
                    QString account="";
                    QString password="";
                    int count=0;
                    for(int i=2;i<str.size();i++){
                        if(str.mid(i,1)=="#"){
                            count++;
                            continue;
                        }
                        if(count==0){
                            account+=str.mid(i,1);
                            continue;
                        }
                        if(count==1){
                            password=str.mid(i,str.size()-i+1);
                            break;
                        }
                    }
                    qDebug()<<"账号"<<account;
                    qDebug()<<"密码"<<password;
                    if(db.isPasswordExist(account,password)){  //登陆成功
                        //暂时保存当前用户的账号密码
                        pet=db.selectTable(account);
                        //提示客户端登陆成功并将该账号数据并返回给客户端
                        tcpSocket->write(QString("登陆成功"+pet.getName()+"#"+pet.getState()+"#"
                                                 +QString::number(pet.getWeight())+"#"+QString::number(pet.getAge())
                                                 +"#"+QString::number(pet.getMood())+"#"+QString::number(pet.getHealth())
                                                 +"#"+QString::number(pet.getHunger())+"#"+QString::number(pet.getActive())
                                                 +"#"+QString::number(pet.getWidth())+"#"+QString::number(pet.getHeight())).toUtf8().data());
                    }else{  //登陆失败
                        //提示客户端登陆失败
                        tcpSocket->write(QString("登陆失败").toUtf8().data());
                    }

                }else if(str.mid(0,2)=="保存"){
                      int count=0;
                      int index[10]={0};
                      for(int i=2;i<str.size();i++){
                          if(str.mid(i,1)=="#"){
                              count++;
                              continue;
                          }
                          index[count]++;
                          switch (count) {
                          case 0:
                              break;
                          case 1://name
                              pet.setName(str.mid(2,index[0]));
                              break;
                          case 2://state
                              pet.setState(str.mid(3+index[0],index[1]));
                              break;
                          case 3://weight
                              pet.setWeight(str.mid(4+index[0]+index[1],index[2]).toDouble());
                              break;
                          case 4://age
                              pet.setAge(str.mid(5+index[0]+index[1]+index[2],index[3]).toInt());
                              break;
                          case 5://mood
                              pet.setMood(str.mid(6+index[0]+index[1]+index[2]+index[3],index[4]).toInt());
                              break;
                          case 6://health
                              pet.setHealth(str.mid(7+index[0]+index[1]+index[2]+index[3]+index[4],index[5]).toInt());
                              break;
                          case 7://hunger
                              pet.setHunger(str.mid(8+index[0]+index[1]+index[2]+index[3]+index[4]+index[5],index[6]).toInt());
                              break;
                          case 8://active
                              pet.setActive(str.mid(9+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6],index[7]).toInt());
                              break;
                          case 9://width
                              pet.setWidth(str.mid(10+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6]+index[7],index[8]).toInt());
                              //height
                              int temp=11+index[0]+index[1]+index[2]+index[3]+index[4]+index[5]+index[6]+index[7]+index[8];
                              pet.setHeight(str.mid(temp,str.size()-temp+1).toInt());
                              count++;
                              break;
                          }
                      }
                      //存储到数据库中
                      qDebug()<<"存储";
                      qDebug()<<pet.getAccount()<<" "<<pet.getPassword()<<" "<<pet.getName()<<" "<<pet.getState()<<" "<<pet.getWeight()
                             <<" "<<pet.getAge()<<" "<<pet.getMood()<<" "<<pet.getHealth()<<" "<<pet.getHunger()<<" "<<pet.getActive()<<" "
                            <<pet.getWidth()<<" "<<pet.getHeight();
                      //更新当前账号数据
                      db.updateTable(pet);
                }
        });
    });

    setWindowTitle("服务端");
}

//void ServerWidget::on_buttonSend_clicked()
//{
//    if(tcpSocket==NULL){
//        return;
//    }
//    //获取编辑区内容
//    QString str=ui->textEditWrite->toPlainText();
//    //给对方发送数据，使用套接字是tcpSocket
//    tcpSocket->write(str.toUtf8().data());
//    //清口输入框的内容
//    ui->textEditWrite->clear();
//}

//void ServerWidget::on_pushButton_2_clicked()
//{
//    if(tcpSocket==NULL){
//        return;
//    }
//    //主动和客户端断开连接
//    tcpSocket->disconnectFromHost();
//    tcpSocket->close();
//    tcpSocket=NULL;
//}

PerTcpServer::~PerTcpServer()
{

}
