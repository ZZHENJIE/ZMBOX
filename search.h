#ifndef SEARCH_H
#define SEARCH_H

#define Music_Max_Number 10 //获取搜索歌曲最大值

#include <QWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QListView>
#include <QDir>
#include <QByteArray>
#include <QTcpSocket>
#include "mthread.h"
#include "server.h"

namespace Ui {
class SEARCH;
}

class SEARCH : public QWidget
{
Q_OBJECT

public:
    explicit SEARCH(QWidget *parent = nullptr);//构造函数

    ~SEARCH();//析构函数

    void Set_Theme_Color(QString Color);//设置主题颜色函数

    void Play_List_Show();//显示播放列表函数

    void Like_List_Show();//显示喜欢列表函数

    void Chat_Room_Show();//显示聊天室函数

private slots:
    void on_Search_Button_clicked();//搜索按钮点击槽函数

    void on_Search_Music_List_itemClicked(QListWidgetItem *item);//搜索音乐列表点击槽函数

    void on_Back_Button_clicked();//点击返回主页槽函数

    void on_Play_All_Button_clicked();//点击播放全部槽函数

    void on_Delete_Button_clicked();//点击删除歌单内歌曲槽函数

    void on_Download_Button_clicked();//点击下载歌曲槽函数

    void on_Add_Like_Button_clicked();//点击添加到喜欢列表槽函数

    void on_Send_Button_clicked();//点击发送信息给服务器槽函数

    void on_Clear_Button_clicked();//点击清除信息列表和输入框槽函数

    void Server_Send();//服务器发送信息槽函数

    void Lyrics_Show();//显示歌词槽函数

signals:

    void Play_All();//播放全部歌曲信号

    void Update_Music();//播放歌曲更新信号

private:
    QString Music_Name[Music_Max_Number];//歌名

    QString Singer_Name[Music_Max_Number];//歌手名

    QString Cloud_Music_Id[Music_Max_Number];//网易云音乐ID

    QString Kugou_Music_Hash[Music_Max_Number];//酷狗音乐Hash

    QString Kugou_Album_Id[Music_Max_Number];//酷狗音乐Album_Id

    QString Kugou_Album_Audio_Id[Music_Max_Number];//酷狗音乐Album_Audio_Id

    QString QQ_Music_Id[Music_Max_Number];//QQ音乐ID

    QFile *Data_Json = new QFile("./Data/Data.json");//客户端设置文件

    QFile *Like_Json = new QFile("./Data/Like.json");//喜欢列表文件

    QFile *Play_Json = new QFile("./Data/Play.json");//播放列表文件

    MThread *Download_Thread;//下载音乐线程

    SERVER *Server;//连接服务器
    
    Ui::SEARCH *ui;

    void Get_Recommended_Playlist();//获取推荐歌单
};

#endif // SEARCH_H
