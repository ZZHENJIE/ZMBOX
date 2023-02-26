#ifndef OTHER_H
#define OTHER_H

#include <QtCore/QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtCore/QEventLoop>
#include <QPixmap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

typedef struct SEARCH_INFO
{
    QString Song_Name;
    QString Sing_Name;
    QString Id;

    QString Hash;
    QString Album_id;
    QString Album_audio_id;
}Search_Info;

typedef struct SONG_LIST_INFO
{
    QString List_Name;
    QString List_Image;
    QString Id;
}Song_List_Info;

class Other : public QObject
{
    Q_OBJECT

public:
    static QByteArray GetUrlData(QString Url);

    static QPixmap UrlToPixmap(QString Url);
};

#endif // OTHER_H
