#ifndef CLOUD_MUSIC_H
#define CLOUD_MUSIC_H

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

typedef struct Cloud//搜索数据结构体
{
    QString Singer_Name;//歌手名
    QString Music_Name;//歌曲名
    QString Music_Id;//歌曲ID
    QString Music_Image;//歌曲图片
}Cloud_Search_Data;

class Cloud_Music : public QObject
{
    Q_OBJECT
public:
    explicit Cloud_Music(QObject *parent = nullptr);//构造函数

    ~Cloud_Music();//析构函数

    void Set_Id(QString Id);//设置音乐ID

    QByteArray Get_Lyrics();//获取歌词

    bool Get_Music_Available();//获取歌曲是否可用

    QString Get_Music_Play();//获取歌曲播放链接

    void Get_Search_Data(Cloud_Search_Data *Data_Arr,QString Text,QString Number,bool Array = true);//获取搜索数据 储存数据数组 搜索内容 返回数量

    void Download_Music();//下载歌曲

    QStringList Get_Playlist_Category();//获取歌单分类

    void Get_Recommended_Playlist(QString Category = "流行");//获取类型推荐歌单

private:
    MThread *Download;//下载线程

    QString CLOUD_MUSIC_API = "https://www.cloudmusicapi.tk/";//API Url

    QString Music_ID = " ";//音乐ID

    QNetworkAccessManager *Manager;//连接

    QNetworkReply *Reply;//存储数据

    QEventLoop EventLoop;//事件循环

    QFile *Play_List = new QFile("./Data/List.json");//播放列表文件
};

#endif // CLOUD_MUSIC_H
