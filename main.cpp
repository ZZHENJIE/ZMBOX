#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow Window;
    Window.show();

    int Return = a.exec();//获取客户端返回值
    if(Return == REBOOT)//判断客户端返回值
    {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());//自动重启客户端
    }
    
    return Return;
}
