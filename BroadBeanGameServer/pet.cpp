#include "pet.h"

Pet::Pet()
{

}

void Pet::setAccount(QString account){
    this->account=account;
}

void Pet::setPassword(QString password){
    this->password=password;
}

void Pet::setName(QString name){
    this->name=name;
}

void Pet::setState(QString state){
     this->state=state;
}

void Pet::setWeight(double weight){
    this->weight=weight;
}

void Pet::setAge(int age){
    this->age=age;
}

void Pet::setMood(int mood){
    this->mood=mood;
}

void Pet::setHealth(int health){
    this->health=health;
}

void Pet::setHunger(int hunger){
    this->hunger=hunger;
}

void Pet::setActive(int active){
    this->active=active;
}

void Pet::setWidth(int width){
    this->width=width;
}

void Pet::setHeight(int height){
    this->height=height;
}

QString Pet::getName(){
    return name;
}

QString Pet::getState(){
    return state;
}

QString Pet::getAccount(){
    return account;
}

QString Pet::getPassword(){
    return password;
}

double Pet::getWeight(){
    return weight;
}

int Pet::getAge(){
    return age;
}

int Pet::getMood(){
    return mood;
}

int Pet::getHealth(){
    return health;
}

int Pet::getHunger(){
    return hunger;
}

int Pet::getActive(){
    return active;
}

int Pet::getWidth(){
    return width;
}

int Pet::getHeight(){
    return height;
}
