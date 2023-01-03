#include "cloud_music.h"

Cloud_Music::Cloud_Music(QObject *parent)
    : QObject{parent}//构造函数
{
    Manager = new QNetworkAccessManager();
    Download = new MThread();
    connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
}

Cloud_Music::~Cloud_Music()//析构函数
{
    delete Manager;
    delete Download;
}

void Cloud_Music::Set_Id(QString Id)//设置音乐ID
{
    Music_ID = Id;
}

QByteArray Cloud_Music::Get_Lyrics()//获取歌词
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "lyric?id=" + Music_ID)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QString Lyrics = Root.value("lrc").toObject().value("lyric").toString();//储存歌词

    return Lyrics.toUtf8();//返回歌词,并且转换为UTF-8编码
}

bool Cloud_Music::Get_Music_Available()//获取歌曲是否可用
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "check/music?id=" + Music_ID)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    return Root.value("success").toBool();
}

QString Cloud_Music::Get_Music_Play()//获取歌曲播放链接
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "song/url?id=" + Music_ID)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    return Root.value("data").toArray().at(0).toObject().value("url").toString();
}

void Cloud_Music::Get_Search_Data(Cloud_Search_Data *Data_Arr,QString Text,QString Number)//获取搜索数据
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "search?keywords=" + Text + "&limit=" + Number)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QJsonObject Result = Root.value("result").toObject();//储存result Json对象

    QJsonArray Songs = Result.value("songs").toArray();//储存Songs Json数组

    for(int Now = 0; Now < Number.toInt(); Now++)
    {
        Root = Songs.at(Now).toObject();//储存一首歌曲Json对象
        Data_Arr[Now].Singer_Name = Root.value("ar").toArray().at(0).toObject().value("name").toString();//储存歌手名
        Data_Arr[Now].Music_Name = Root.value("name").toString();//储存歌曲名
        Data_Arr[Now].Music_Id = QString::number(Root.value("id").toInt());//储存歌曲Id,使用Qstring方法,把整形转换为Qstring类型
        Data_Arr[Now].Music_Image = Root.value("al").toObject().value("picUrl").toString();//储存歌曲图片
    }
}

void Cloud_Music::Download_Music()//下载歌曲
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "song/detail?ids=" + Music_ID)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QString Music_Name;//歌曲名

    QString Singer_Name;//歌手名

    Music_Name = Root.value("songs").toArray().at(0).toObject().value("name").toString();

    Singer_Name = Root.value("songs").toArray().at(0).toObject().value("ar").toArray().at(0).toObject().value("name").toString();

    Download->run(Get_Music_Play(),Music_Name + " - " + Singer_Name,"mp3",".\\Music\\Cloud\\");
}

QStringList Cloud_Music::Get_Playlist_Category()//获取歌单分类
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "playlist/catlist")));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QJsonArray Sub = Root.value("sub").toArray();

    QStringList Ret;

    for(int i = 0; i < Sub.count(); i++)
    {
        Ret.append(Sub.at(i).toObject().value("name").toString());
    }

    return Ret;
}

void Cloud_Music::Get_Recommended_Playlist(QString Category)//获取类型推荐歌单
{
    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "top/playlist/highquality?limit=10&cat=" + Category)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QJsonArray PlayLists = Root.value("playlists").toArray();

    Play_List->open(QFile::WriteOnly);

    QJsonArray ADD;

    for(int i = 0; i < PlayLists.count(); i++)
    {
        QJsonObject Add;
        Add.insert("Id",QString::number(PlayLists.at(i).toObject().value("id").toInteger()));
        Add.insert("Name",PlayLists.at(i).toObject().value("name").toString());
        Add.insert("Image_Url",PlayLists.at(i).toObject().value("coverImgUrl").toString());
        ADD.append(Add);

        QFileInfo Image_File("./Image/List/" + Add.value("Id").toString() +".png");
        
        if(Image_File.isFile() == false)
        {
            Download->run(Add.value("Image_Url").toString(),Add.value("Id").toString(),"png",".\\Image\\List\\");
        }
    }

    Data.setArray(ADD);

    Play_List->write(QByteArray(Data.toJson()));

    Play_List->close();
}

void Cloud_Music::Get_Playlist_Details(QString PlayList_Id)//获取歌单详情
{
    QFile Play_Json(".\\Data\\Play.json");//播放Json文件

    Reply = Manager->get(QNetworkRequest(QUrl(CLOUD_MUSIC_API + "playlist/detail?id=" + PlayList_Id)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonArray Root = Data.object().value("privileges").toArray();//转成为Json数组

    QString Url = CLOUD_MUSIC_API + "song/detail?ids=";

    for(int i = 0; i < Root.size(); i++)
    {
        Url += QString::number(Root.at(i).toObject().value("id").toInteger());
        Url += ",";
    }

    Url.chop(1);

    Reply = Manager->get(QNetworkRequest(QUrl(Url)));
    EventLoop.exec();

    Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    Root = Data.object().value("songs").toArray();//转成为Json数组

    QJsonArray Ret;

    for(int i = 0; i < Root.size(); i++)
    {

        QJsonObject Music;//需要储存的歌曲信息对象
        Music.insert("Platform","W");
        Music.insert("Music_Id",QString::number(Root.at(i).toObject().value("id").toInteger()));
        Music.insert("Music_Name",Root.at(i).toObject().value("name").toString());
        Music.insert("Singer_Name",Root.at(i).toObject().value("ar").toArray().at(0).toObject().value("name").toString());
        Music.insert("Image_Url",Root.at(i).toObject().value("al").toObject().value("picUrl").toString());
        Ret.append(Music);//添加到Json数组尾部
    }

    Play_Json.open(QFile::WriteOnly);

    Data.setArray(Ret);//把Root信息给Temp_Json

    Play_Json.write(QByteArray(Data.toJson()));//把信息写入(清空写入)播放列表

    Play_Json.close();
}