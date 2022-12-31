#include "kugou_music.h"

KuGou_Music::KuGou_Music(QObject *parent)
    : QObject{parent}//构造函数
{
    Manager = new QNetworkAccessManager();
    Request = new QNetworkRequest();
    Download = new MThread();
    Request->setRawHeader("cookie",QByteArray("kg_mid=1;"));//设置请求头
    connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
}

KuGou_Music::~KuGou_Music()//析构函数
{
    delete Manager;
    delete Request;
    delete Download;
}

void KuGou_Music::Set_Id(QString Music_Hash,QString Album_Id,QString Album_Audio_Id)//设置音乐数据
{
    Request->setUrl(QUrl("https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Music_Hash +"&album_id=" + Album_Id + "&album_audio_id=" + Album_Audio_Id));
}

QByteArray KuGou_Music::Get_Lyrics()//获取歌词
{
    Reply = Manager->get(*Request);
    EventLoop.exec();

    QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Temp.object();//转成为Json对象

    QString Lyrics = Root.value("data").toObject().value("lyrics").toString();//储存歌词

    Lyrics.remove(0,Lyrics.lastIndexOf("[offset:0]")+12);//删除垃圾段落

    return Lyrics.toUtf8();//返回歌词,并且转换为UTF-8编码
}

bool KuGou_Music::Get_Music_Available()//获取歌曲是否可用
{
    Reply = Manager->get(*Request);
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    if(Root.value("status").toInt())
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString KuGou_Music::Get_Music_Play()//获取歌曲播放链接
{
    Reply = Manager->get(*Request);
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    return Root.value("data").toObject().value("play_url").toString();
}

void KuGou_Music::Get_Search_Data(KuGou_Search_Data *Data_Arr,QString Text,QString Number)//获取搜索数据
{
    Reply = Manager->get(QNetworkRequest(QUrl("http://mobilecdn.kugou.com/api/v3/search/song?keyword=" + Text + "&page=1&pagesize=" + Number)));
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    QJsonObject data = Root.value("data").toObject();//储存data Json对象

    QJsonArray Songs = data.value("info").toArray();//储存Songs Json数组

    for(int Now = 0; Now < Number.toInt(); Now++)
    {
        Root = Songs.at(Now).toObject();//储存一首歌曲Json对象
        Data_Arr[Now].Singer_Name = Root.value("singername").toString();//储存歌手名
        Data_Arr[Now].Music_Name = Root.value("songname").toString();//储存歌曲名
        Data_Arr[Now].Music_Hash = Root.value("hash").toString();//储存歌曲Hash
        Data_Arr[Now].Album_Id = Root.value("album_id").toString();//储存歌曲Album_Id
        Data_Arr[Now].Album_Audio_Id = QString::number(Root.value("album_audio_id").toInt());//储存歌曲Album_Audio_Id
    }
}

QString KuGou_Music::Get_Music_Image()//获取歌曲图片
{
    Reply = Manager->get(*Request);
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    return Root.value("data").toObject().value("img").toString();
}

void KuGou_Music::Download_Music()//下载歌曲
{
    Reply = Manager->get(*Request);
    EventLoop.exec();

    QJsonDocument Data = QJsonDocument::fromJson(Reply->readAll());//存储为Json

    QJsonObject Root = Data.object();//转成为Json对象

    Download->run(Get_Music_Play(),Root.value("data").toObject().value("audio_name").toString(),"mp3",".\\Music\\KuGou\\");
}
