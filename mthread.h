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
#include <QMessageBox>

class MThread : public QThread
{
    public:
        MThread(){};//构造函数
        ~MThread(){};//析构函数
        virtual void run(QString Download_Url,int Platform,QString Music_Name,QString Singer_Name);//Platform:0 网易云音乐 1 酷狗音乐 2 QQ音乐
};

#endif


