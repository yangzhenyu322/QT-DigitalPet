#include "petdatabse.h"
#include<QTextCodec>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QCoreApplication>


PetDatabse::PetDatabse(QWidget *parent)
    : QWidget(parent)
{
    //连接数据库
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    db.setHostName("127.0.0.1");          //设置数据库主机名,如localhost
    QString dbPath = QCoreApplication::applicationDirPath() + "//myqtDB.db";
    db.setDatabaseName("PetDB.db");     //设置数据库名   //①绝对路径可行 F:/QCProject/Digital_pet/DatabaseMode/qtDB1.db//②
    db.setUserName("root");                     //设置数据库用户名
    db.setPassword("root");                           //设置数据库密码
    //打开数据库
    if(!db.open()){  //数据库打开失败
        QMessageBox::warning(this,"错误",db.lastError().text());
    }
    else{
        qDebug()<<"数据库打开成功";
    }
    //建表
    createTable();
}

PetDatabse::~PetDatabse()
{

}

//建表
void PetDatabse::createTable(){
    QString sql=QString("create table %1(id int primary key,account varchar,password varchar,name varchar,state varchar,weight double,age int,mood int,health int,hunger int,active int,width int,height int);").arg(TABLENAME);
    bool success=query.exec(sql);
    if(success)
        qDebug()<<QObject::tr("数据库表创建成功！\n");
    else
        qDebug()<<QObject::tr("数据库表创建失败,该表已存在！\n");
}

//查询账号是否存在
bool PetDatabse::isAccountExist(QString account){
    bool success=false;
    query.exec(QString("select * from %1 where account='%2'").arg(TABLENAME).arg(account));
    if(query.next())
    {
        qDebug()<<QObject::tr("该账号已被注册 ");
        success=true;
    }
    else
        qDebug()<<QObject::tr("该账号可以注册");

    return success;
}

//插值（注册）
void PetDatabse::insertIntable(Pet strInsert){
    bool insert=false;
    int id=0;
    while(!insert){
        query.prepare(QString("insert into %1 values(?,?,?,?,?,?,?,?,?,?,?,?,?)").arg(TABLENAME));
        query.bindValue(0,id);
        query.bindValue(1,strInsert.getAccount());
        query.bindValue(2,strInsert.getPassword());
        query.bindValue(3,strInsert.getName());
        query.bindValue(4,strInsert.getState());
        query.bindValue(5,strInsert.getWeight());
        query.bindValue(6,strInsert.getAge());
        query.bindValue(7,strInsert.getMood());
        query.bindValue(8,strInsert.getHealth());
        query.bindValue(9,strInsert.getHunger());
        query.bindValue(10,strInsert.getActive());
        query.bindValue(11,strInsert.getWidth());
        query.bindValue(12,strInsert.getHeight());
        bool success=query.exec();
        if(!success)
        {
            id++;
        }
        else{
            qDebug()<<QString(QObject::tr("插入成功"));
            insert=true;
        }
    }
}



//查询密码是否正确
bool PetDatabse::isPasswordExist(QString account,QString password){
    bool success=false;
    query.exec(QString("select * from %1 where account='%2' AND password='%3'").arg(TABLENAME).arg(account).arg(password));
    if(query.next())
    {
        qDebug()<<QObject::tr("密码正确 ");
        success=true;
    }
    else
        qDebug()<<QObject::tr("密码不正确");

    return success;
}


//查询（返回上次保存的数值）
Pet PetDatabse::selectTable(QString account){

    Pet strInsert;
    bool success=query.exec(QString("select * from %1 where account='%2'").arg(TABLENAME).arg(account));
    if(success)
        qDebug()<<QObject::tr("查询成功 ");
    else
        qDebug()<<QObject::tr("查询失败");
    //查询
    query.first();  //必须要使用
    strInsert.setAccount(query.value(1).toString());
    strInsert.setPassword(query.value(2).toString());
    strInsert.setName(query.value(3).toString());
    strInsert.setState(query.value(4).toString());
    strInsert.setWeight(query.value(5).toDouble());\
    strInsert.setAge(query.value(6).toInt());
    strInsert.setMood(query.value(7).toInt());
    strInsert.setHealth(query.value(8).toInt());
    strInsert.setHunger(query.value(9).toInt());
    strInsert.setActive(query.value(10).toInt());
    strInsert.setWidth(query.value(11).toInt());
    strInsert.setHeight(query.value(12).toInt());
    return  strInsert;
}


//保存数据
void PetDatabse::updateTable(Pet data){
    query.prepare(QString("update %1 set name=?,"
                                  "state=?,weight=?,age=?,mood=?,health=?,hunger=?,active=?,width=?,height=?"
                                   "where account='%2';").arg(TABLENAME).arg(data.getAccount()));
            query.bindValue(0,data.getName());
            query.bindValue(1,data.getState());
            query.bindValue(2,data.getWeight());
            query.bindValue(3,data.getAge());
            query.bindValue(4,data.getMood());
            query.bindValue(5,data.getHealth());
            query.bindValue(6,data.getHunger());
            query.bindValue(7,data.getActive());
            query.bindValue(8,data.getWidth());
            query.bindValue(9,data.getHeight());
            bool success=query.exec();
            if(!success)
            {
                qDebug()<<QString(QObject::tr("保存失败"));
            }
            else{
                qDebug()<<QString(QObject::tr("保存成功"));
            }
}


//删值(注销账号)
//void PetDatabse::deleteFromTable(){
//    if(records>0){
//        QString sql=QString("delete from %1 where id=%2").arg(TABLENAME).arg(records-1);
//        query.exec(sql);
//        bool success=query.exec();
//        if(!success)
//        {
//            qDebug()<<QString(QObject::tr("删除失败"));
//        }
//        else{
//            qDebug()<<QString(QObject::tr("删除成功"));
//        }
//        records--;
//    }

//}

