#ifndef SEARCH_H
#define SEARCH_H

#define Music_Max_Number 10

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
    explicit SEARCH(QWidget *parent = nullptr);
    ~SEARCH();
    void Set_Theme_Color(QString Color);
    void Play_List_Show();
    void Like_List_Show();
    void Chat_Room_Show();
    int Return_State();

private slots:
    void on_PushButton_clicked();

    void on_Music_List_itemClicked(QListWidgetItem *item);

    void on_Back_clicked();

    void on_Play_All_clicked();

    void on_Delete_clicked();

    void on_Download_clicked();

    void on_Add_Like_clicked();

    void on_Send_clicked();

    void on_Clear_clicked();

    void Server_Send();

    void Music_Data_Show();

signals:

    void Play_All();

    void Update_Music();

private:
    //歌名 歌手名
    QString Music_Name[Music_Max_Number];
    QString Singer_Name[Music_Max_Number];
    //网易云
    QString Cloud_Music_Id[Music_Max_Number];
    //酷狗
    QString Kugou_Music_Hash[Music_Max_Number];
    QString Kugou_Album_Id[Music_Max_Number];
    QString Kugou_Album_Audio_Id[Music_Max_Number];
    //QQ
    QString QQ_Music_Id[Music_Max_Number];

    QJsonDocument Json_File_Temp;

    QFile *Data_Json = new QFile("./Data/Data.json");
    QFile *Like_Json = new QFile("./Data/Like.json");
    QFile *Play_Json = new QFile("./Data/Play.json");

    MThread *Download_Thread;
    SERVER *Server;
    Ui::SEARCH *ui;
    QString User_Name = " ";

    void Get_Ever_Day_Music();
};

#endif // SEARCH_H
