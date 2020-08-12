#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include <QLabel>
#include <QWidget>
#include<QDialog>

class LoginMessage : public QDialog
{
    Q_OBJECT
public:
    explicit LoginMessage(QDialog *parent = 0);
    void setText(QString str);

private:
    QLabel* massage;

signals:

public slots:
};

#endif // LOGINMESSAGE_H
