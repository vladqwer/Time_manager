#include "timer.h"

timer::timer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timer)
{

    ui->setupUi(this);
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    QStringList name_table;
    name_table << "time" << "p/s" << "time limit"<<"name activity";
    ui->tableWidget->setHorizontalHeaderLabels(name_table);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
}

timer::~timer()
{
    delete ui;
}
void timer::update(int c11, int c12, int c13, int c21, int c22, int c23, int c31, int c32, int c33, int coeff)
{
    ui->lcdNumber->display(c11);
    ui->lcdNumber_2->display(c12);
    ui->lcdNumber_3->display(c13);

    ui->lcdNumber_4->display(c21);
    ui->lcdNumber_5->display(c22);
    ui->lcdNumber_6->display(c23);

    ui->lcdNumber_7->display(c31);
    ui->lcdNumber_8->display(c32);
    ui->lcdNumber_9->display(c33);
}


void timer::on_pushButtonProfit_clicked()
{
    this->ch='1';
    emit CH(ch);
    ui->pushButtonActivity->setEnabled(true);
    ui->pushButton->setEnabled(false);
}

void timer::on_pushButtonEnterteinment_clicked()
{
    this->ch='2';
    emit CH(ch);
    emit getANeme(ui->lineEdit->text());
    ui->pushButtonActivity->setEnabled(true);
    ui->pushButton->setEnabled(false);
}

void timer::on_pushButton_clicked()
{
    this->ch='4';
    emit CH(ch);
    Sleep(1000);
    this->close();

}

void timer::on_doubleSpinBox_valueChanged(double arg1)
{
    emit updateKoef(arg1);
}

void timer::on_pushButtonActivity_clicked()
{

    ui->pushButtonActivity->setEnabled(false);
    ui->pushButton->setEnabled(true);
    emit getANeme(ui->lineEdit->text());
    this->ch='3';
    emit CH(ch);

}
void timer::addToTable(int n, int t, QString str2, QString str3,int full)
{
    //qDebug()<<"addToTable";
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    QTableWidgetItem *item1 =new QTableWidgetItem();
    QTableWidgetItem *item2 =new QTableWidgetItem();
    QTableWidgetItem *item3 =new QTableWidgetItem();
    QTableWidgetItem *item4 =new QTableWidgetItem();
    QString str;
    str=QString::number(t/3600000)+" "+QString::number(t/60000%60)+" "\
            +QString::number(t/1000%60)+" ";
    item1->setText(str);
    item2->setText(str2);
    item3->setText(str3);
    str=QString::number(full/3600000)+" "+QString::number(full/60000%60)+" "\
            +QString::number(full/1000%60)+" ";
    item4->setText(str);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,item1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,item2);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,item4);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,item3);
}

void timer::on_tabWidget_tabBarClicked(int index)
{
    if(index==1){
        ui->tableWidget->clear();
        ui->tableWidget->setRowCount(0);
        QStringList name_table;
        name_table << "time" << "p/s" << "time limit"<<"name activity";
        ui->tableWidget->setHorizontalHeaderLabels(name_table);
        emit refreshTable();
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Stretch);
    }
}

void timer::on_lineEdit_textChanged(const QString &arg1)
{
    if(!ui->lineEdit->text().isEmpty())
    {
        ui->pushButtonProfit->setEnabled(true);
        ui->pushButtonEnterteinment->setEnabled(true);

    }
    else
    {
        ui->pushButtonProfit->setEnabled(false);
        ui->pushButtonEnterteinment->setEnabled(false);
    }
}
