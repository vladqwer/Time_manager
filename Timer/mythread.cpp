#include "mythread.h"

MyThread::MyThread()
{
    QSqlRecord rec;
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("timer_db.sqlite");
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
    }
    else
    {
        qDebug() << "открылась";
    }
    QSqlQuery t_query;
    int num=0;
    t_query.exec("SELECT fulltime FROM time_table;");

    while (t_query.next()) {
        rec = t_query.record();
        num = t_query.value(rec.indexOf("fulltime")).toInt();
    }
    earned_full=num;
}
MyThread::~MyThread(){
    qDebug()<<"MyThreadDestructor";
}
void MyThread::run()
{
    int c11=0,c12=0,c13=0,//переменные для передачи чч мм сс
            c21=0,c22=0,c23=0,// в каждый раздел
            c31=0,c32=0,c33=0;
    clock_t c = clock(),c1=clock();//с1 на сохранение начального времени режима
    clock_t d;
    QString process = "waiting";
    coeff = 1;

    char ch1 = ch;
    long long int time1 = 0, fulltime1 = 0, fulltime2 = 0, time2 = 0;
    int flag = 0,//флаг на текущий режим
            flag2 = 0;//флаг предыдущего режима
    while (true)
    {
        if (ch == '4')
        {
            fulltime1 = fulltime1 + time1;
            fulltime2 = fulltime2 + time2;

            earned_full = earned_full - time2;
            earned_full = earned_full + time1*coeff;
            this->thread()->quit();
            //delete this;
            //break;
            //this->thread()->SetStop();
        }
        //            if (ch == '5')
        //            {
        //                flag = 3;
        //                earned_full = earned_full - time2;
        //                earned_full = earned_full + time1*coeff;
        //                fulltime1 = fulltime1 + time1;
        //                time1 = 0;
        //                fulltime2 = fulltime2 + time2;
        //                time2 = 0;
        //                cin >> coeff;
        //            }

        if (ch != ch1)
        {
            c1=c;
            switch (ch)
            {
            case ('1'):
                ch1 = ch;
                c = clock();
                flag2=flag;
                flag = 1;
                fulltime2 = fulltime2 + time2;
                earned_full = earned_full - time2;
                time2 = 0;
                process = "runing";
                break;
            case ('2'):
                ch1 = ch;
                c = clock();
                flag2=flag;
                flag = 2;
                fulltime1 = fulltime1 + time1;
                earned_full = earned_full + time1*coeff;
                time1 = 0;
                process = "runing";
                break;
            case('3'):
                ch1 = ch;
                c = clock();
                flag2=flag;
                flag = 3;
                earned_full = earned_full - time2;
                earned_full = earned_full + time1*coeff;
                fulltime1 = fulltime1 + time1;
                time1 = 0;
                fulltime2 = fulltime2 + time2;
                time2 = 0;
                process = "waiting";
                break;
            default:
                break;
            }

            d = clock();
            if((flag2==1 && flag==2)||(flag2==1 && flag==3))
                emit sendToDB((d-c1),"+",earned_full,str);
            if((flag2==2 && flag==1)||(flag2==2 && flag==3))
                emit sendToDB((d-c1),"-",earned_full,str);
        }

        Sleep(10);
        //system("cls");
        d = clock();
        if (flag == 1) time1 = d - c;
        if (flag == 2) time2 = d - c;
        c11=(time1 + fulltime1) / 3600000;
        c12=(time1 + fulltime1) / 60000 % 60;
        c13=(time1 + fulltime1) / 1000 % 60;
        c21=(time2 + fulltime2) / 3600000;
        c22=(time2 + fulltime2) / 60000 % 60;
        c23=(time2 + fulltime2) / 1000 % 60;
        c31=(long long int)(earned_full - time2 + time1*coeff) / 3600000;
        c32=(long long int)(earned_full - time2 + time1*coeff) / 60000 % 60;
        c33=(long long int)(earned_full - time2 + time1*coeff) / 1000 % 60;
        emit sendToForm(c11,c12,c13,c21,c22,c23,c31,c32,c33,coeff);

        //            cout << c11 << " " << c12 << "  " << c13 <<"   profit 1"<< endl;
        //            cout << c21 << " " << c22 << "  " << c23 <<"   entertainment 2"<< endl;
        //            cout << c31 << " " << c32 << "  " << c33 << "   earned" << endl;
        //            cout << coeff << " coeff" << endl;
        //            cout << process <<"  3"<< endl;
        //            cout << "press double 4 for exit"<< endl;

    }
}
void MyThread::CH(char cha)
{
    this->ch = cha;
}
void MyThread::updateKoef(double d)
{
    this->coeff = d;
}
void MyThread::setAName(QString s)
{
    this->str = s;
}
