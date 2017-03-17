#ifndef DB_H
#define DB_H
#include <QtSql>
#include "QString"
#include<iostream>
#include <QWidget>
using namespace std;
class DB: public QWidget
{
    Q_OBJECT
public:
    DB(QWidget *parent=0);
private:
    bool b;
private slots:
    void sendToDB(int time,QString str,int full,QString);
    void refreshTable();
signals:
    void sendToTable(int,int,QString,QString,int);
};

#endif // DB_H
