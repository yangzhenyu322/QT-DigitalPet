#ifndef PETDATABASE_H
#define PETDATABASE_H

#include <QWidget>
#include <QSqlQuery>
#define TABLENAME "petData"
#include<pet.h>

class PetDataBase : public QWidget
{
    Q_OBJECT
public:
    explicit PetDataBase(QWidget *parent = 0);
    ~PetDataBase();

//数据库操作
        QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
        QSqlQuery query;
        int records=0;
        void createTable();   //输入sql语句建表
        void insertIntable(Pet strInsert);  //用DatabaseValue对象插入一条数据
        void deleteFromTable();   //从表中删除一条数据
        void updateTable(Pet data);  //更新表中数据
        Pet selectTable(); //从表中查询并获取数据
};

#endif // PETDATABASE_H
