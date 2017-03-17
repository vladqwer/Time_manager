#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <iostream>
#include "ctime"
#include <windows.h>
#include "QString"
#include <conio.h>
#include <QDebug>
#include <windows.h>
#include<QtSql>

using namespace std;
class MyThread: public QThread
{
    Q_OBJECT
public:
    MyThread();
    ~MyThread();
    void run();
signals:
    void sendToForm(int c11,int c12,int c13,int c21,int c22,int c23,int c31,int c32,int c33,\
                    int coeff);
    void sendToDB(int time,QString str,int full,QString);

private:
    double coeff;
    char ch='0';
    long long earned_full;
    QString str;

private slots:
    void updateKoef(double d);
    void CH(char );
    void setAName(QString);
};

#endif // MYTHREAD_H
