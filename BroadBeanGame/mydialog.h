#ifndef MYDIALOG_H
#define MYDIALOG_H

#include<QDialog>
#include <QLabel>
#include<pet.h>
#include<QPoint>
#include<QMouseEvent>
#include<define.h>
#include <QProgressBar>
#include "Windows.h"

class Mydialog : public QDialog
{
    Q_OBJECT
public:
    Mydialog(Pet* pet=nullptr);
    //永久置顶
    QTimer *m_timer;

protected:
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent(QMouseEvent*);

signals:
    void backToPlay();

private:
    QPoint point;
    int playAction=0;  //原地动作
    QString appearance1="child";
    QString appearance2="Yangpa";
    Pet* pet;

};

#endif // MYDIALOG_H
