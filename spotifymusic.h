#ifndef SPOTIFYMUSIC_H
#define SPOTIFYMUSIC_H

#include <QObject>
#include "other.h"

class SpotifyMusic : public QObject
{
    Q_OBJECT
public:
    static Search_Info * Search(QString KeyWord,QString Offset = "0");

    static Search_Info * KuGouSearch(QString KeyWord,QString Offset = "1");
};

#endif // SPOTIFYMUSIC_H
