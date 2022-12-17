#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define REBOOT 1

#include <QMainWindow>
#include <QDialog>

#include "set.h"
#include "play.h"
#include "search.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//构造函数

    ~MainWindow();//析构函数

private slots:
    void on_Set_clicked();//点击设置按钮槽函数

    void on_Like_clicked();//点击喜欢列表槽函数

    void on_Play_clicked();//点击播放列表槽函数

    void on_Room_clicked();//点击聊天室槽函数

    void Reboot();//设置类返回重启信号槽函数

private:
    Ui::MainWindow *ui;

    SEARCH *Search;//搜索界面类

    PLAY *Play;//播放界面类

    SET *Set;//设置界面类

    bool User_Log_State = false;//用户登入状态

    void Set_Theme_Color(QString Color);//设置主题颜色函数
};
#endif // MAINWINDOW_H
