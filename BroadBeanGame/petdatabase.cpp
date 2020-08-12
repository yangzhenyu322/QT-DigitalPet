#include "petdatabase.h"
#include<QTextCodec>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QDebug>
#include<QCoreApplication>


PetDataBase::PetDataBase(QWidget *parent)
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

}

PetDataBase::~PetDataBase()
{

}

//建表
void PetDataBase::createTable(){
    QString sql=QString("create table %1(id int primary key,name varchar,state varchar,weight double,age int,mood int,health int,hunger int,active int,width int,height int);").arg(TABLENAME);
    bool success=query.exec(sql);
    if(success)
        qDebug()<<QObject::tr("数据库表创建成功！\n");
    else
        qDebug()<<QObject::tr("数据库表创建失败,该表已存在！\n");
}

//插值
void PetDataBase::insertIntable(Pet strInsert){
    bool insert=false;
    while(!insert){
        qDebug()<<records;
        query.prepare(QString("insert into %1 values(?,?,?,?,?,?,?,?,?,?,?)").arg(TABLENAME));
        query.bindValue(0,records);
        query.bindValue(1,strInsert.getName());
        query.bindValue(2,strInsert.getState());
        query.bindValue(3,strInsert.getWeight());
        query.bindValue(4,strInsert.getAge());
        query.bindValue(5,strInsert.getMood());
        query.bindValue(6,strInsert.getHealth());
        query.bindValue(7,strInsert.getHunger());
        query.bindValue(8,strInsert.getActive());
        query.bindValue(9,strInsert.getWidth());
        query.bindValue(10,strInsert.getHeight());
        bool success=query.exec();
        if(!success)
        {
            qDebug()<<QString(QObject::tr("插入失败"));
            records++;
        }
        else{
            qDebug()<<QString(QObject::tr("插入成功"));
            insert=true;
        }
    }
    records++;
}

//删值
void PetDataBase::deleteFromTable(){
    if(records>0){
        QString sql=QString("delete from %1 where id=%2").arg(TABLENAME).arg(records-1);
        query.exec(sql);
        bool success=query.exec();
        if(!success)
        {
            qDebug()<<QString(QObject::tr("删除失败"));
        }
        else{
            qDebug()<<QString(QObject::tr("删除成功"));
        }
        records--;
    }

}

//修改
void PetDataBase::updateTable(Pet data){
    query.prepare(QString("update %1 set id=%2,name=?,"
                                  "state=?,weight=?,age=?,mood=?,health=?,hunger=?,active=?,width=?,height=?").arg(TABLENAME).arg(records-1));
            query.bindValue(0,records-1);
            query.bindValue(1,data.getName());
            query.bindValue(2,data.getState());
            query.bindValue(3,data.getWeight());
            query.bindValue(4,data.getAge());
            query.bindValue(5,data.getMood());
            query.bindValue(6,data.getHealth());
            query.bindValue(7,data.getHunger());
            query.bindValue(8,data.getActive());
            query.bindValue(9,data.getWidth());
            query.bindValue(10,data.getHeight());
}

Pet PetDataBase::selectTable(){

    Pet strInsert;
    //排序：desc（降序）  、 asc（默认为升序）
    bool success=query.exec(QString("select * from %1 order by id desc").arg(TABLENAME));
    if(success)
        qDebug()<<QObject::tr("按id降序降序成功 ");
    else
        qDebug()<<QObject::tr("按id降序降序失败！");
    //查询
    query.first();
    strInsert.setName(query.value(1).toString());
    strInsert.setState(query.value(2).toString());
    strInsert.setWeight(query.value(3).toDouble());\
    strInsert.setAge(query.value(4).toInt());
    strInsert.setMood(query.value(5).toInt());
    strInsert.setHealth(query.value(6).toInt());
    strInsert.setHunger(query.value(7).toInt());
    strInsert.setActive(query.value(8).toInt());
    strInsert.setWidth(query.value(9).toInt());
    strInsert.setHeight(query.value(10).toInt());

    qDebug()<<"查询成功";
    return  strInsert;
}
