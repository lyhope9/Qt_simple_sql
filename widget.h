#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlDatabase>
#include<QSqlQuery>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnInsert_clicked();

    void on_btnDelete_clicked();

    void on_btnSelect_clicked();

    void on_btnSelectAll_clicked();

    void on_btnUpdate_clicked();

private:
    Ui::Widget *ui;
    QSqlDatabase  db;

};

#endif // WIDGET_H
