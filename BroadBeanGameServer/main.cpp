#include<pertcpserver.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PerTcpServer w;

    return a.exec();
}
