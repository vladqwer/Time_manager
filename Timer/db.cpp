#include "db.h"
DB::DB(QWidget *parent): QWidget(parent)
{
    QString str;
    //QSqlRecord rec;
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("timer_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }
    else
    {
        qDebug() << "открылась";
    }
    QSqlQuery t_query;

    str = "CREATE TABLE time_table ("
          "number integer PRIMARY KEY NOT NULL, "
          "time integer, "
          "typeActivity string, "
          "nameActivity string,"
          "fulltime integer "
          ");";
    b = t_query.exec(str);
    if (!b) {
        qDebug() << "Вроде не удается создать таблицу, провертье карманы!";
    }

    t_query.prepare("INSERT INTO time_table(number,time,typeActivity,nameActivity,fulltime)"
                    " VALUES (:number , :time, :typeActivity, :nameActivity, :fulltime);");
    t_query.bindValue(":number",1);
    t_query.bindValue(":time",0);
    t_query.bindValue(":typeActivity","NULL");
    t_query.bindValue(":nameActivity","STR");
    t_query.bindValue(":fulltime",0);

    b = t_query.exec();
    if (!b) {
        qDebug() << "Вроде не удается создать первую строку!";
    }
    //    int num=0,t=0,fT=0;
    //    QString tA="",nA="";
    //    t_query.exec("SELECT * FROM time_table;");

    //    while (t_query.next()) {
    //        rec = t_query.record();
    //        num = t_query.value(rec.indexOf("number")).toInt();
    //        t = t_query.value(rec.indexOf("time")).toInt();
    //        tA = t_query.value(rec.indexOf("typeActivity")).toString();
    //        nA = t_query.value(rec.indexOf("nameActivity")).toString();
    //        fT = t_query.value(rec.indexOf("fulltime")).toInt();
    //        qDebug() << "number is " << num
    //                 << ". time is " << t
    //                 << ". tA" << tA
    //                 << ". nA" << nA
    //                 << ". fT" << fT;
    //        str=QString::number(t/3600);
    //        emit sendToTable(num,str,tA,tA,fT);
    //    }
}
void DB::sendToDB(int time,QString Qstr,int full,QString strName)
{
    int n=0;//номер строки
    //QString str;
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("timer_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }
    else
    {
        qDebug() << "открылась";
        dbase.open();
    }
    QSqlQuery t_query;
    QSqlRecord rec = t_query.record();


    int num=0,t=0,fT=0;
    QString tA="",nA="";
    t_query.exec("SELECT * FROM time_table;");

    while (t_query.next()) {
        rec = t_query.record();
        num = t_query.value(rec.indexOf("number")).toInt();
        t = t_query.value(rec.indexOf("time")).toInt();
        tA = t_query.value(rec.indexOf("typeActivity")).toString();
        nA = t_query.value(rec.indexOf("nameActivity")).toString();
        fT = t_query.value(rec.indexOf("fulltime")).toInt();

        //        qDebug() << "number is " << num
        //                 << ". time is " << t
        //                 << ". tA" << tA
        //                 << ". nA" << nA;
        n=num+1;
    }
    qDebug()<<n;

    t_query.prepare("INSERT INTO time_table(number,time,typeActivity,nameActivity,fulltime)"
                    " VALUES (:number , :time, :typeActivity, :nameActivity, :fulltime);");
    t_query.bindValue(":number",QString::number(n));
    t_query.bindValue(":time",QString::number(time));
    t_query.bindValue(":typeActivity",Qstr);
    t_query.bindValue(":nameActivity",strName);
    t_query.bindValue(":fulltime",full);
    b = t_query.exec();
    if (!b) {
        qDebug() << "Вроде не удается добавить строку!";
    }
    //    t_query.exec("SELECT * FROM time_table;");

    //    while (t_query.next()) {
    //        rec = t_query.record();
    //        num = t_query.value(rec.indexOf("number")).toInt();
    //        t = t_query.value(rec.indexOf("time")).toInt();
    //        tA = t_query.value(rec.indexOf("typeActivity")).toString();
    //        nA = t_query.value(rec.indexOf("nameActivity")).toString();
    //        fT = t_query.value(rec.indexOf("fulltime")).toInt();

    //        qDebug() << "number is " << num
    //                 << ". time is " << t
    //                 << ". tA" << tA
    //                 << ". nA" << nA
    //                 << ". fT" << fT;
    //    }
}
void DB::refreshTable()
{
    //QString str;
    QSqlRecord rec;
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("timer_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        //return -1;
    }
    else
    {
        qDebug() << "открылась";
    }
    QSqlQuery t_query;
    int num=0,t=0,fT=0;
    QString tA="",nA="";
    t_query.exec("SELECT * FROM time_table;");

    while (t_query.next()) {
        rec = t_query.record();
        num = t_query.value(rec.indexOf("number")).toInt();
        t = t_query.value(rec.indexOf("time")).toInt();
        tA = t_query.value(rec.indexOf("typeActivity")).toString();
        nA = t_query.value(rec.indexOf("nameActivity")).toString();
        fT = t_query.value(rec.indexOf("fulltime")).toInt();
        //        qDebug() << "number is " << num
        //                 << ". time is " << t
        //                 << ". tA" << tA
        //                 << ". nA" << nA
        //                 << ". fT" << fT;
        //str=QString::number(t);
        emit sendToTable(num,t,tA,nA,fT);
    }
}
