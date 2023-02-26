#include "spotifymusic.h"

Search_Info * SpotifyMusic::Search(QString KeyWord,QString Offset)
{
    Search_Info * Data = new Search_Info[10];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8386/Search?keyword=" + KeyWord + "&limit=10&offset=" + Offset));

    QJsonArray Json_Data = Json_Doc.object().value("tracks").toObject().value("items").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Id = Info.value("id").toString();

        Data[i].Song_Name = Info.value("name").toString();

        Data[i].Sing_Name = Info.value("artists").toArray().at(0).toObject().value("name").toString();
    }

    return Data;
}

Search_Info * SpotifyMusic::KuGouSearch(QString KeyWord,QString Offset)
{
    Search_Info * Data = new Search_Info[10];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8386/KuGou/Search?keyword=" + KeyWord + "&limit=10&offset=" + Offset));

    QJsonArray Json_Data = Json_Doc.object().value("data").toObject().value("info").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Hash = Info.value("hash").toString();

        Data[i].Album_id = QString::number(Info.value("album_id").toInt());

        Data[i].Album_audio_id = QString::number(Info.value("album_audio_id").toInt());

        Data[i].Song_Name = Info.value("songname").toString();

        Data[i].Sing_Name = Info.value("singername").toString();
    }

    return Data;
}
