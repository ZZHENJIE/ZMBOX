#ifndef SET_H
#define SET_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QPixmap>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QJsonValueRef>
#include <QFileDialog>

namespace Ui {
class Set;
}

class SET : public QMainWindow
{
    Q_OBJECT

public:
    explicit SET(QWidget *parent = nullptr);//构造函数

    ~SET();//析构函数

private slots:
    void on_Select_Background_clicked();//选择背景图片按钮槽函数

    void on_Open_Dir_clicked();//打开音乐下载文件夹按钮槽函数

    void on_Log_Pushbutton_clicked();//登入QQ按钮槽函数

    void on_Exit_Log_clicked();//退出QQ登入按钮槽函数

    void on_Open_clicked();//打开边听边存槽函数

    void on_Close_clicked();//关闭边听边存槽函数

    void on_Application_clicked();//应用主题颜色按钮槽函数

    void on_Fix_clicked();//修复槽函数

    void on_Tray_Open_clicked();//开启托盘功能槽函数

    void on_Tray_Close_clicked();//关闭托盘功能槽函数

signals:
    void Reboot_Signals();//重启软件信号

private:
    QFile *Json = new QFile("./Data/Data.json");//软件设置Json

    Ui::Set *ui;
};

#endif // SET_H
