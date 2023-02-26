#ifndef NETMUSIC_H
#define NETMUSIC_H

#include <QObject>
#include "other.h"

class NetMusic : public QObject
{
    Q_OBJECT
public:
    static Search_Info * Search(QString KeyWord,QString Offset = "1");

    static Song_List_Info * GetTheRecommendedPlaylist(QString Limit = "20");
};

#endif // NETMUSIC_H
