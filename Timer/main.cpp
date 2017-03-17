#include "mythread.h"
#include "timer.h"
#include "db.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    timer *w = new timer();
    w->show();
    MyThread *A = new MyThread();
    A->start();
    DB *db = new DB();
    QObject::connect(A, SIGNAL(sendToForm(int,int,int,int,int,int,int,int,int,int)),\
                     w, SLOT(update(int,int,int,int,int,int,int,int,int,int)));
    QObject::connect(w, SIGNAL(CH(char)),A, SLOT(CH(char)));
    QObject::connect(w, SIGNAL(updateKoef(double)),A, SLOT(updateKoef(double)));
    QObject::connect(A,SIGNAL(sendToDB(int,QString,int,QString)),\
                     db,SLOT(sendToDB(int,QString,int,QString)));
    QObject::connect(db,SIGNAL(sendToTable(int,int,QString,QString,int)),\
                     w,SLOT(addToTable(int,int,QString,QString,int)));
    QObject::connect(w,SIGNAL(refreshTable()),db,SLOT(refreshTable()));
    QObject::connect(w,SIGNAL(getANeme(QString)),A,SLOT(setAName(QString)));
    return a.exec();
}
