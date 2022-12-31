#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define REBOOT 1

#include <QMainWindow>
#include <QCloseEvent>
#include <QDialog>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include "set.h"
#include "play.h"
#include "search.h"
#include "primary.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);//构造函数

    ~MainWindow();//析构函数

    void closeEvent(QCloseEvent *Event);//覆写关闭函数

    bool Tray;//托盘功能是否开启

private slots:
    void on_Set_clicked();//点击设置按钮槽函数

    void on_Like_clicked();//点击喜欢列表槽函数

    void on_Play_clicked();//点击播放列表槽函数

    void on_Room_clicked();//点击聊天室槽函数

    void Reboot();//设置类返回重启信号槽函数

    void Quit();//退出程序槽函数

    void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason Reason);//点击系统托盘图标槽函数
signals:

    void Like_clicked();//点击喜欢列表信号

    void Play_clicked();//点击播放列表信号

    void Room_clicked();//点击聊天室列表信号

private:
    Ui::MainWindow *ui;

    QSystemTrayIcon *SystemIcon = new QSystemTrayIcon();//系统托盘图标类

    SEARCH *Search;//搜索界面类

    PLAY *Play;//播放界面类

    SET *Set;//设置界面类

    PRIMARY *Primary;//主要显示区域类

    QMenu *Menu = new QMenu(this);//菜单

    QAction *Exit = new QAction("退出",this);//退出

    QAction *Back = new QAction("上一首",this);//上一首

    QAction *Next = new QAction("下一首",this);//下一首

    QAction *Play_Paused = new QAction("播放或暂停",this);//播放或暂停

    bool User_Log_State = false;//用户登入状态

    void Set_Theme_Color(QString Color);//设置主题颜色函数
};
#endif // MAINWINDOW_H
