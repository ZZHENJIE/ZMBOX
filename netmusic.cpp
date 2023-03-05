#include "netmusic.h"

Song_Info * NetMusic::Search(QString KeyWord,QString Offset)
{
    Song_Info * Data = new Song_Info[10];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/search?keywords=" + KeyWord + "&limit=10" + "&offset=" + Offset));

    QJsonArray Json_Data = Json_Doc.object().value("result").toObject().value("songs").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Id = QString::number(Info.value("id").toInt());

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


Song_List_Info * NetMusic::GetTheRecommendedPlaylist(QString Limit)
{
    Song_List_Info * Data = new Song_List_Info[15];

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/personalized?limit=" + Limit));

    QJsonArray Json_Data = Json_Doc.object().value("result").toArray();

    for(int i = 0; i < Json_Data.size(); i++)
    {
        QJsonObject Info = Json_Data.at(i).toObject();

        Data[i].Id = QString::number(Info.value("id").toInt());

        Data[i].List_Name = Info.value("name").toString();

        Data[i].List_Image = Info.value("picUrl").toString() + "?param=165y165";
    }

    return Data;
}

QString NetMusic::GetMusicUrl(QString ID)
{
    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/check/music?id=" + ID));

    QJsonObject Json_Data = Json_Doc.object();

    if(Json_Data.value("success").toBool() == true)
    {
        Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/song/url?id=" + ID));

        Json_Data = Json_Doc.object();

        return Json_Data.value("data").toArray().at(0).toObject().value("url").toString();
    }
    else
    {
        QMessageBox::information(0,"提示",Json_Data.value("message").toString());

        return "";
    }
}


