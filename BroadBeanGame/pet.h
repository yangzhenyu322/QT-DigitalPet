#ifndef PET_H
#define PET_H
#include<QString>
#include<define.h>

class Pet
{
public:
    Pet();
    void setName(QString name);
    void setState(QString state);
    void setWeight(double weight);
    void setAge(int age);
    void setMood(int mood);
    void setHealth(int health);
    void setHunger(int hunger);
    void setActive(int active);
    void setWidth(int width);
    void setHeight(int height);

    QString getName();
    QString getState();
    double getWeight();
    int getAge();
    int getMood();
    int getHealth();
    int getHunger();
    int getActive();
    int getWidth();
    int getHeight();


private:
    QString name="萌馋豆";  //昵称
    QString state="健康";   //状态
    double  weight=WEIGHT;      //体重
    int  age=AGE;          //年龄
    int  mood=MOOD;       //心情
    int health=HEALTH;      //健康
    int hunger=HUNGER;    //饥饿度
    int active=ACTIVE;      //活力值
    int width=WIDTH;      //宠物宽度
    int height=HEIGHT;    //宠物高度
};

#endif // PET_H
