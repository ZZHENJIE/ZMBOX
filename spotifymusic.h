#ifndef SPOTIFYMUSIC_H
#define SPOTIFYMUSIC_H

#include "other.h"

class SpotifyMusic : public QObject
{
    Q_OBJECT
public:
    static Song_Info * Search(QString KeyWord,QString Offset = "0");

    static Song_Info * KuGouSearch(QString KeyWord,QString Offset = "1");
};

#endif // SPOTIFYMUSIC_H
