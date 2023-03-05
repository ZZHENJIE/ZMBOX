#include "spotifymusic.h"

Song_Info * SpotifyMusic::Search(QString KeyWord,QString Offset)
{
    Song_Info * Data = new Song_Info[10];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8386/Search?keyword=" + KeyWord + "&limit=10&offset=" + Offset));

    QJsonArray Json_Data = Json_Doc.object().value("tracks").toObject().value("items").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Id = Info.value("id").toString();

        Data[i].Song_Name = Info.value("name").toString();
        
        Data[i].Singer_Name = Info.value("artists").toArray().at(0).toObject().value("name").toString();

        if(Info.value("artists").toArray().size() > 1)
        {
            for(int j = 1; j < Info.value("artists").toArray().size(); j++)
            {
                Data[i].Singer_Name += "/";
                Data[i].Singer_Name += Info.value("artists").toArray().at(j).toObject().value("name").toString();
            }
        }
    }

    return Data;
}

Song_Info * SpotifyMusic::KuGouSearch(QString KeyWord,QString Offset)
{
    Song_Info * Data = new Song_Info[10];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://mobilecdn.kugou.com/api/v3/search/song?keyword=" + KeyWord + "&pagesize=10&page=" + Offset));

    QJsonArray Json_Data = Json_Doc.object().value("data").toObject().value("info").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Hash = Info.value("hash").toString();

        Data[i].Album_id = QString::number(Info.value("album_id").toInt());

        Data[i].Album_audio_id = QString::number(Info.value("album_audio_id").toInt());

        Data[i].Song_Name = Info.value("songname").toString();

        Data[i].Singer_Name = Info.value("singername").toString();
    }

    return Data;
}
