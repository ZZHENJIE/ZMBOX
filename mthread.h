#ifndef MTHREAD
#define MTHREAD

#include <QThread>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

class MThread : public QThread
{
public:
    MThread();//构造函数
    ~MThread();//析构函数
    virtual void run(QString Download_Url,QString FileName,QString FileType,QString Dir);//下载函数 下载链接 文件名 文件类型 文件路径
private:
    QNetworkAccessManager *Manager;//连接

    QNetworkReply *Reply;//存储数据

    QEventLoop EventLoop;//事件循环
};

#endif


