#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QListWidgetItem>
#include <QListView>
#include <QDir>
#include <QByteArray>
#include <QTcpSocket>

#include "server.h"

namespace Ui {
class SEARCH;
}

class SEARCH : public QWidget
{
Q_OBJECT

public:
    explicit SEARCH(QWidget *parent = nullptr);//构造函数

    ~SEARCH();//析构函数

    void Set_Theme_Color(QString Color);//设置主题颜色函数

private slots:
    void on_Search_Button_clicked();//搜索按钮点击槽函数

    void on_Back_Button_clicked();//点击返回主页槽函数

signals:

    void Search_Button_clicked(int Platform,QString Text);//搜索按钮点击信号

    void Back_Button_clicked();//点击返回主页槽信号

private:
    Ui::SEARCH *ui;
};

#endif // SEARCH_H
