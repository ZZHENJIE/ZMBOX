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

QString NetMusic::GetMusicImage(QString ID)
{
    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/song/detail?ids=" + ID));

    QJsonObject Json_Data = Json_Doc.object();

    return Json_Data.value("songs").toArray().at(0).toObject().value("al").toObject().value("picUrl").toString() + "?param=256y256";
}

QList<Lyrics_Data> NetMusic::GetMusicLyrics(QString ID)
{
    QList<Lyrics_Data> List;
    
    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/lyric?id=" + ID));

    QTextStream Lyric (Json_Doc.object().value("lrc").toObject().value("lyric").toString().toUtf8());

    short Min,Ten_Sec,Sec = 0;

    while(true)
    {
        QString Data = Lyric.readLine();

        if(Data.isEmpty() != true)
        {
            Lyrics_Data Add;

            Add.Data = Data.mid(Data.lastIndexOf("]")+1);

            QString Time = Data.mid(Data.lastIndexOf("[")+1,Data.lastIndexOf("]")-1);

            Min = Time.split(":").at(0).toInt();

            Ten_Sec = Time.split(":").at(1).split(".").at(0).toInt();

            Sec = Time.split(":").at(1).split(".").at(1).toInt();

            if(Data.lastIndexOf("]") == 9)
            {
                Sec *= 10;
            }

            Add.Time = (Min * 60000) + (Ten_Sec * 1000) + Sec;
            
            List.append(Add);
        }
        else
        {
            break;
        }
    }

    return List;
}

void NetMusic::GetMusicData(Player_Music_Info * Data,QString ID)
{
    Data->Image = Other::UrlToPixmap(GetMusicImage(ID));

    Data->Music = GetMusicUrl(ID);

    Data->Lyrics = GetMusicLyrics(ID);
}

