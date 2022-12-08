#include "mainwindow.h"

#include <QApplication>
#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow Window;
    Window.show();

    int Return = a.exec();
    if(Return == REBOOT)
    {
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    
    return Return;
}
