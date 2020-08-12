#ifndef PETDATABSE_H
#define PETDATABSE_H

#define TABLENAME "petData"
#include <QWidget>
#include <QSqlQuery>
#include<pet.h>

class PetDatabse : public QWidget
{
    Q_OBJECT
public:
    explicit PetDatabse(QWidget *parent = 0);
    ~PetDatabse();

//数据库操作
        QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
        QSqlQuery query;
        void createTable();   //输入sql语句建表
        void insertIntable(Pet strInsert);  //用DatabaseValue对象插入一条数据
        void deleteFromTable();   //从表中删除一条数据
        void updateTable(Pet data);  //更新表中数据
        Pet selectTable(QString account); //从表中查询并获取数据
        bool isAccountExist(QString account); //查询账号是否存在
        bool isPasswordExist(QString account,QString password); //查询密码是否正确
};

#endif // PETDATABSE_H
