#include "begin.h"
#include <QApplication>
#include <QPropertyAnimation>
#include<login.h>
#include<playroom.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      Login w;
      w.show();
    return a.exec();
}
