#ifndef KUGOU_MUSIC_H
#define KUGOU_MUSIC_H

#include <QObject>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include "mthread.h"

typedef struct KuGou//搜索数据结构体
{
    QString Singer_Name;//歌手名
    QString Music_Name;//歌曲名
    QString Music_Hash;//音乐Hash
    QString Album_Id;//Album_Id
    QString Album_Audio_Id;//Album_Audio_Id
}KuGou_Search_Data;

class KuGou_Music : public QObject
{
    Q_OBJECT
public:
    explicit KuGou_Music(QObject *parent = nullptr);//构造函数

    ~KuGou_Music();//析构函数

    void Set_Id(QString Music_Hash,QString Album_Id,QString Album_Audio_Id);//设置音乐Id

    QByteArray Get_Lyrics();//获取歌词

    bool Get_Music_Available();//获取歌曲是否可用

    QString Get_Music_Play();//获取歌曲播放链接

    void Get_Search_Data(KuGou_Search_Data *Data_Arr,QString Text,QString Number);//获取搜索数据 储存数据数组 搜索内容 返回数量

    QString Get_Music_Image();//获取歌曲图片

    void Download_Music();//下载歌曲

private:
    MThread *Download;//下载线程

    QNetworkRequest *Request;//请求头

    QNetworkAccessManager *Manager;//连接

    QNetworkReply *Reply;//存储数据

    QEventLoop EventLoop;//事件循环
};

#endif // KUGOU_MUSIC_H
