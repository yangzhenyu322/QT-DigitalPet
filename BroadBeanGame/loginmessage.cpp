#include "loginmessage.h"


LoginMessage::LoginMessage(QDialog *parent) : QDialog(parent)
{
        massage = new QLabel(this);
        massage->setFixedSize(300,50);
        setFixedSize(300,50);
}

void LoginMessage::setText(QString str)
{
        massage->setText(str);
}
