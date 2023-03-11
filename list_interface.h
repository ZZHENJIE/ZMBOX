#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H

#include "other.h"
#include "mlistwidgetitem.h"
#include "netmusic.h"
#include "spotifymusic.h"

namespace Ui {
class List_Interface;
}

class List_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit List_Interface(QWidget *parent = nullptr);
    ~List_Interface();

    void UI_Init(QFont Font,QString Color_Info = "255,255,255,255");

    void Back();

    void Read_List();

    void Save_List();

    void Clear_Item();

    void UpdataMusic();

public Q_SLOTS:

    void Lyrics_Select_Change(short SerialNumber);

    void Next_Offset();

    void Back_Offset();

    void Play_List_Show();

    void Like_List_Show();

    void Lyrics_Interface_Show();

    void Search(QString KeyWord,int MusicPlatform,int Offset = 1);

    void GetTheRecommendedPlaylist(int MusicPlatform = 0);

    void Next_Music();

    void Back_Music();

Q_SIGNALS:

    void Play_Select_Song(Player_Music_Info Data);

    void Clear_Item_Signals();

private:
    Ui::List_Interface *ui;

    QFont Font_;

    QString Search_KeyWord;

    short Play_SerialNumber = 0;//播放序号

    short Offset_Count = 1;//页数

    short State = 4;// 1 为喜欢列表 2 为播放列表 3 搜索列表 (30 网易云音乐 31 为QQ音乐 32 为酷狗音乐 33 为Spotify) 4 为歌单

    QList <Song_Info> Play_List;
    QList <Song_Info> Like_List;
};

#endif // LIST_INTERFACE_H
