#ifndef NETMUSIC_H
#define NETMUSIC_H

#include "other.h"

class NetMusic : public QObject
{
    Q_OBJECT
public:
    static Song_Info * Search(QString KeyWord,QString Offset = "1");

    static Song_List_Info * GetTheRecommendedPlaylist(QString Limit = "15");

    static QString GetMusicUrl(QString ID);
};

#endif // NETMUSIC_H
