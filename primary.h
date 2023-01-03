#ifndef PRIMARY_H
#define PRIMARY_H
#define Music_Max_Number 10 //获取搜索歌曲最大值

#include <QWidget>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QListWidgetItem>
#include <QDir>
#include "struct.h"
#include "server.h"
#include "cloud_music.h"
#include "kugou_music.h"

namespace Ui {
class PRIMARY;
}

class PRIMARY : public QWidget
{
    Q_OBJECT

public:
    explicit PRIMARY(QWidget *parent = nullptr);//构造函数

    ~PRIMARY();//析构函数

    void Set_Theme_Color(QString Color);//设置主题颜色函数

private slots:
    void Play_List_Show();//显示播放列表函数

    void Like_List_Show();//显示喜欢列表函数

    void Chat_Room_Show();//显示聊天室函数

    void on_Search_Music_List_itemClicked(QListWidgetItem *item);//搜索音乐列表点击槽函数

    void on_Play_All_Button_clicked();//点击播放全部槽函数

    void on_Delete_Button_clicked();//点击删除歌单内歌曲槽函数

    void on_Download_Button_clicked();//点击下载歌曲槽函数

    void on_Add_Like_Button_clicked();//点击添加到喜欢列表槽函数

    void on_Send_Button_clicked();//点击发送信息给服务器槽函数

    void on_Clear_Button_clicked();//点击清除信息列表和输入框槽函数

    void Server_Send();//服务器发送信息槽函数

    void Lyrics_Show();//显示歌词槽函数

    void on_Like_Play_List_itemDoubleClicked(QListWidgetItem *item);//双击播放和喜欢列表槽函数

    void Search_Button_clicked(int Platform,QString Text);//搜索按钮点击槽函数

    void Back_Button_clicked();//点击返回主页槽函数

    void Lyrics_Change(Music_Info Info);//歌词更新槽函数

    void on_List_0_clicked();//歌单按钮槽函数

    void on_List_1_clicked();

    void on_List_2_clicked();

    void on_List_3_clicked();

    void on_List_4_clicked();

    void on_List_5_clicked();

    void on_List_6_clicked();

    void on_List_7_clicked();

    void on_List_8_clicked();

    void on_List_9_clicked();

signals:

    void Play_All();//播放全部歌曲信号

    void Update_Music(bool Delete);//播放歌曲更新信号

    void Change_Music_Number(int Number);//改变播放歌曲信号

private:
    Ui::PRIMARY *ui;

    QFile *Data_Json = new QFile("./Data/Data.json");//客户端设置文件

    QFile *Like_Json = new QFile("./Data/Like.json");//喜欢列表文件

    QFile *Play_Json = new QFile("./Data/Play.json");//播放列表文件

    QFile *List_Json = new QFile("./Data/List.json");//歌单列表文件

    Cloud_Search_Data Cloud_Search[Music_Max_Number];//网易云音乐搜索内容

    KuGou_Search_Data KuGou_Search[Music_Max_Number];//酷狗音乐搜索内容

    Lyrics_Info Lyrics_Data[200];//歌词行

    Cloud_Music *Cloud;//网易云音乐类

    KuGou_Music *KuGou;//酷狗音乐类

    SERVER *Server;//连接服务器

    int Search_Platform = 0;//音乐搜索平台

    void Set_Recommended_Playlist();//设置歌单
};

#endif // PRIMARY_H
