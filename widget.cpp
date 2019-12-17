#include "widget.h"
#include "ui_widget.h"
#include <QTextCodec>
#include<QMessageBox>
#include<QDebug>

# pragma execution_character_set("utf-8")


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug()<<QSqlDatabase::drivers();
    setWindowTitle("SQL_Student");

    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());  //设置显示中文
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("qt_test");  // 已有数据库名称
    db.setUserName("root");
    db.setPassword("********");

    if(!db.open()){
        QMessageBox::warning(this, "警告", "数据库打开失败");
    }
    else{
        ui->textEdit->setText("数据库打开成功");
    }

//    QString str = "create table student(num int, name varchar(32), score double);";
//    QSqlQuery query;
//    query.exec(str);


}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnInsert_clicked()
{
    QString namestr = ui->lineEditName->text();
    int num = ui->lineEditNum->text().toInt();
    double score = ui->lineEditScore->text().toDouble();
    if(namestr==nullptr || num==0 || ui->lineEditScore==nullptr){
        ui->textEdit->setText("请输入完整的信息");
    }
    else{
        QString str = QString("insert into student(num, name, score) values('%1', '%2', '%3')").arg(num).arg(namestr).arg(score);
        QSqlQuery query;
        query.exec(str);
        ui->lineEditName->clear();
        ui->lineEditNum->clear();
        ui->lineEditScore->clear();
        ui->textEdit->setText("插入成功");
    }
}

void Widget::on_btnDelete_clicked()
{
    QString name = ui->lineEditName->text();
    if(name==nullptr){
        ui->textEdit->setText("请输入需要删除的人的名字");
    }
    else{
        QSqlQuery query;
        QString temp = QString("select * from student where name = '%1'").arg(name);
        query.exec(temp);
        QString deletename;
        while(query.next()){
            deletename = query.value(1).toString();
        }
        if(deletename==nullptr){
            QString a = QString("没有叫%1的人，删除失败").arg(name);
            ui->textEdit->setText(a);
            ui->lineEditName->clear();
            ui->lineEditNum->clear();
            ui->lineEditScore->clear();
        }
        else{
            QString str = QString("delete from student where name = '%1'").arg(name);
            query.exec(str);
            ui->lineEditName->clear();
            ui->lineEditNum->clear();
            ui->lineEditScore->clear();
            ui->textEdit->setText("删除成功");
        }
    }
}

void Widget::on_btnSelect_clicked()
{
    QString searchname = ui->lineEditName->text();
    if(searchname==nullptr){
        ui->textEdit->setText("请输入需要查询的人名");
    }
    else{
        QString str = QString("select * from student where name = '%1'").arg(searchname);
        QSqlQuery query;
        query.exec(str);
        QString name;
        int number=0;
        double score=0;
        while(query.next()){
            number = query.value(0).toInt();
            name = query.value(1).toString();
            score = query.value(2).toDouble();
        }
        if(name==nullptr){
            QString a = QString("没有叫%1的人，请重新输入人名").arg(searchname);
            ui->textEdit->setText(a);
            ui->lineEditName->clear();
            ui->lineEditNum->clear();
            ui->lineEditScore->clear();
        }
        else{
            ui->lineEditName->setText(name);
            ui->lineEditNum->setText(QString().setNum(number));
            ui->lineEditScore->setText(QString().setNum(score));
            ui->textEdit->setText("查询成功");
        }
    }
}




void Widget::on_btnSelectAll_clicked()
{
    QString name[100];
    int number[100];
    double score[100];
    int i = 0;
    QSqlQuery query;
    query.exec("select * from student");
    while(query.next()){
        number[i] = query.value(0).toInt();
        name[i] = query.value(1).toString();
        score[i] = query.value(2).toDouble();
        i++;
    }
    ui->textEdit->clear();
    int j = 0;
    for(j=0;j<i;j++){
        QString str = QString("学号：%1    姓名：%2   成绩：%3").arg(number[j]).arg(name[j]).arg(score[j]);
        ui->textEdit->append(str);
    }
}

void Widget::on_btnUpdate_clicked()
{
    QString updatename = ui->lineEditName->text();
    int number = ui->lineEditNum->text().toInt();
    double score = ui->lineEditScore->text().toDouble();
    if(updatename==nullptr || number==0 || ui->lineEditScore->text()==nullptr){
        ui->textEdit->setText("请输入需要修改的人的学号，姓名以及成绩");
    }
    else{
        QString temp = QString("select * from student where name='%1'").arg(updatename);
        QSqlQuery query;
        query.exec(temp);
        QString a;
        while(query.next()){
            a = query.value(1).toString();
        }
        if(a==nullptr){
            QString b = QString("没有名叫%1的人，修改失败").arg(updatename);
            ui->textEdit->setText(b);
            ui->lineEditName->clear();
            ui->lineEditNum->clear();
            ui->lineEditScore->clear();
        }
        else{
            temp = QString("update student set num='%1', score = '%2' where name='%3'").arg(number).arg(score).arg(updatename);
            query.exec(temp);
            ui->textEdit->setText("修改成功");
            ui->lineEditName->clear();
            ui->lineEditNum->clear();
            ui->lineEditScore->clear();
        }
    }

}
