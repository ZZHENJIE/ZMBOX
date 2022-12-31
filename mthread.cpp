#include "mthread.h"

MThread::MThread()//构造函数
{
    //this->start();
    Manager = new QNetworkAccessManager();
    connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
}

MThread::~MThread()//析构函数
{
    //this->quit();
    delete Manager;
}

void MThread::run(QString Download_Url,QString FileName,QString FileType,QString Dir)//下载函数
{
    this->start();
    QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl(Download_Url)));
    EventLoop.exec();

    //保存文件
    QFile Music(Dir + FileName + "." + FileType);
    Music.open(QFile::WriteOnly);
    Music.write(Reply->readAll());
    Music.close();
    this->quit();
}