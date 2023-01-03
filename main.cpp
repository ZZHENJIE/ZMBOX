#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

bool Checks_Whether_Is_Running()//检测是否运行中
{
    int Count = 0;

    QProcess process;

    process.start("tasklist");

    process.waitForFinished();
 
    QByteArray Data = process.readAllStandardOutput();

    QStringList List = QString(Data).split("\n");

    for(int i = 0; i < List.size(); i++)
    {
        if(List[i].contains("ZMBOX.exe",Qt::CaseSensitive))
        {
            Count += 1;
        }
    }

    if(Count == 1)
    {
        return false;
    }
    else
    {
        QMessageBox::information(0,"提示","程序已启动!");
        return true;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(Checks_Whether_Is_Running() == false)
    {
        MainWindow Window;
        if(Window.Tray)
        {
            a.setQuitOnLastWindowClosed(false);
        }
        Window.show();

        int Return = a.exec();//获取客户端返回值

        if(Return == REBOOT)//判断客户端返回值
        {
            QProcess::startDetached(qApp->applicationFilePath(), QStringList());//自动重启客户端
        }

        return Return;
    }
    else
    {
        return 0;
    }
}
