#ifndef TIMER_H
#define TIMER_H

#include <QDialog>

#include "ui_timer.h"
#include <windows.h>
#include<QString>
#include<QDebug>

namespace Ui {
class timer;
}
class timer : public QDialog
{
    Q_OBJECT

public:
    explicit timer(QWidget *parent = 0);
    ~timer();

private slots:
    void on_pushButtonProfit_clicked();
    void update(int c11,int c12,int c13,int c21,int c22,int c23,int c31,int c32,int c33,\
                int coeff);

    void on_pushButtonEnterteinment_clicked();

    void on_pushButton_clicked();

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButtonActivity_clicked();
    void addToTable(int,int,QString,QString,int);

    void on_tabWidget_tabBarClicked(int index);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::timer *ui;
    char ch='0';

signals:
    void CH(char ch);// передача указателя действия
    void updateKoef(double d);// передача коэффициента
    void refreshTable();
    void getANeme(QString);
};

#endif // TIMER_H
