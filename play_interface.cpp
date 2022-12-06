#include "play_interface.h"
#include "ui_play_interface.h"

PLAY_INTERFACE::PLAY_INTERFACE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLAY_INTERFACE)
{
    ui->setupUi(this);
    this->move(0,600);

    Play_Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();
    Play_List = Temp_Json.array();

    QFile Data_Json;
    Data_Json.setFileName("./Data/Data.json");
    Data_Json.open(QFile::ReadOnly);
    Temp_Json = QJsonDocument::fromJson(QByteArray(Data_Json.readAll()));
    Data_Json.close();

    Save_While_Listening = Temp_Json.object().value("Save_While_Listening").toBool();
    //ui->Audio_Size->value()
    Audio_OP.setVolume(50 * 1.0);//初始化声音大小
    Music_Media.setAudioOutput(&Audio_OP);//设置音频输出

    connect(&Music_Media,SIGNAL(durationChanged(qint64)),this,SLOT(GetDuration()));
    Time.setInterval(500);//设置计时器刷新时间
}

PLAY_INTERFACE::~PLAY_INTERFACE()
{
    delete ui;
    delete Download;
}

void PLAY_INTERFACE::Set_Theme_Color(QString Color)
{
    ui->Audio_Size->setVisible(false);
    ui->Play->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Back->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Next->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Audio->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
}

void PLAY_INTERFACE::on_Back_clicked()
{
    if(Play_Number == 0)
    {
        Play_Number = Play_List.count() - 1;
    }
    else
    {
        Play_Number -=1;
    }
    Change_Music();
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
}


void PLAY_INTERFACE::on_Play_clicked()
{
    if(Music_Media.playbackState() == QMediaPlayer::PlayingState)
    {
        ui->Play->setIcon(QIcon(":/Resource/Play.png"));
        Music_Media.pause();
    }
    else if(Music_Media.playbackState() == QMediaPlayer::StoppedState)
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Change_Music();
    }
    else if(Music_Media.playbackState() == QMediaPlayer::PausedState)
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Music_Media.play();
    }
}


void PLAY_INTERFACE::on_Next_clicked()
{
    if(Play_Number == Play_List.count() - 1)
    {
        Play_Number = 0;
    }
    else
    {
        Play_Number +=1;
    }
    Change_Music();
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
}


void PLAY_INTERFACE::on_Audio_clicked()
{
    if(ui->Audio_Size->isVisible())
    {
        ui->Audio_Size->setVisible(false);
    }
    else
    {
        ui->Audio_Size->setVisible(true);
    }
}


void PLAY_INTERFACE::on_Image_clicked()
{

}


void PLAY_INTERFACE::Play_State(int State)
{
    if(State == 1)
    {
        Play_Number = 0;
    }
    else if(State == 2)
    {
        Play_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();
        Play_List = Temp_Json.array();
    }
}

void PLAY_INTERFACE::Change_Music()
{
    Music_Media.stop();
    Time.stop();
    QString Play_Url;
    if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "W")
    {
        QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() + "&ids=[" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() + "]&br=3200000";
        if(Save_While_Listening == true)
        {
            Download->run(Download_Url,0,Play_List.at(Play_Number).toObject().value("Music_Name").toString(),Play_List.at(Play_Number).toObject().value("Singer_Name").toString());
        }
        QNetworkAccessManager *Manager = new QNetworkAccessManager();
        QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl(Download_Url)));
        QEventLoop EventLoop;
        connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
        EventLoop.exec();

        //解析json
        QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
        QJsonObject Root = Temp.object();
        QJsonValue Value_1 = Root.value("data");
        QJsonObject Value_2 = Value_1.toArray().at(0).toObject();

        if(Value_2.value("url").isNull() == false)//判断音乐神佛可下载
        {
            Play_Url = Value_2.value("url").toString();
        }
        else
        {
            QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到下载问题");
            on_Next_clicked();
        }

    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "K")
    {
        QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Play_List.at(Play_Number).toObject().value("Music_Hash").toString() + "&album_id=" + Play_List.at(Play_Number).toObject().value("Album_Id").toString() + "&album_audio_id=" + Play_List.at(Play_Number).toObject().value("Album_Audio_Id").toString();
        if(Save_While_Listening == true)
        {
            Download->run(Download_Url,1,Play_List.at(Play_Number).toObject().value("Music_Name").toString(),Play_List.at(Play_Number).toObject().value("Singer_Name").toString());
        }

        QNetworkRequest Url;
        Url.setUrl(QUrl(Download_Url));
        Url.setRawHeader("cookie",QByteArray("kg_mid=1"));
        //获取音乐下载json
        QNetworkAccessManager *Manager = new QNetworkAccessManager();
        QNetworkReply *Reply = Manager->get(Url);
        QEventLoop EventLoop;
        connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
        EventLoop.exec();

        //解析json
        QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
        QJsonObject Root = Temp.object();

        if(Root.value("status").toInt() == 1)
        {
            Play_Url = Root.value("data").toObject().value("play_url").toString();
        }
        else
        {
            QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到下载问题");
            on_Next_clicked();
        }
    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "Q")
    {

    }
    //connect(&Music_Media, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    Music_Media.setSource(QUrl(Play_Url));
    Music_Media.play();
    Time.start();
    connect(&Time,SIGNAL(timeout()),this,SLOT(ON_Time_Out()));
    ui->Name->setText(Play_List.at(Play_Number).toObject().value("Music_Name").toString()+ "    " +Play_List.at(Play_Number).toObject().value("Singer_Name").toString());
}

void PLAY_INTERFACE::ON_Time_Out()
{
    ui->Music_Pos->setValue(Music_Media.position()/1000);
    QString Minute = QString::number(ui->Music_Pos->value() / 60);
    QString Second = QString::number(ui->Music_Pos->value() % 60);
    ui->Time->setText(Minute + ":" + Second + "/" + QString::number(Muisc_Max_Leng / 60) + ":" + QString::number(Muisc_Max_Leng % 60));
    // if(Lyrics[Now_Lyrics].at(2) == Minute)
    // {
    //     if(Second.toInt() < 10)
    //     {
    //         if(Lyrics[Now_Lyrics].at(5) == Second)
    //         {
    //             ui->Lyrics_List->item(Now_Lyrics)->setBackground(Brush);
    //             Now_Lyrics++;
    //         }
    //     }
    //     else
    //     {
    //         QString Temp[2];
    //         Temp[0] = Lyrics[Now_Lyrics].at(4);
    //         Temp[1] = Lyrics[Now_Lyrics].at(5);
    //         if(Temp[0] + Temp[1] == Second)
    //         {
    //             ui->Lyrics_List->item(Now_Lyrics)->setBackground(Brush);
    //             Now_Lyrics++;
    //         }
    //     }
    // }
    if(Music_Media.position()/1000 == Muisc_Max_Leng)
    {
        on_Next_clicked();
    }
}

void PLAY_INTERFACE::GetDuration()
{
    Muisc_Max_Leng = Music_Media.duration()/1000;
    ui->Music_Pos->setRange(0,Muisc_Max_Leng);
}