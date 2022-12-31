#ifndef STRUCT_H
#define STRUCT_H

#include <QString>
#include <QByteArray>

typedef struct Music_Info//歌曲信息
{
    QString Singer_Name;//歌手名
    QString Music_Name;//歌曲名
    QString Music_Id;//歌曲ID
    QString Platform;//音乐平台
    QByteArray Music_Lyrics;//歌曲歌词
}Music_Info;

typedef struct Lyrics_Info//歌曲信息
{
    QString Time;//时间
    QString Lyrics;//歌词
}Lyrics_Info;

#endif
