#include "play.h"
#include "ui_play.h"

PLAY::PLAY(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLAY)//构造函数
{
    ui->setupUi(this);
    this->move(0,600);

    Play_Json->open(QFile::ReadOnly);//打开播放列表Json文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();

    Play_List = Temp_Json.array();//储存播放列表信息

    QFile Data_Json;//打开软件设置文件
    Data_Json.setFileName("./Data/Data.json");
    Data_Json.open(QFile::ReadOnly);
    Temp_Json = QJsonDocument::fromJson(QByteArray(Data_Json.readAll()));
    Data_Json.close();

    Save_While_Listening = Temp_Json.object().value("Save_While_Listening").toBool();//储存是否开启边听边存功能

    if(Save_While_Listening == true)//判断是否开启边听边存功能
    {
        Download = new MThread();
    }

    Audio_OP.setVolume(ui->Audio_Size->value() * 1.0);//初始化声音大小
    Music_Media.setAudioOutput(&Audio_OP);//设置音频输出

    Time.setInterval(500);//设置计时器刷新时间

    connect(&Time,SIGNAL(timeout()),this,SLOT(ON_Time_Out()));//超出设置计时器刷新时间调用ON_Time_Out()槽函数,并且重新计时

    connect(&Music_Media,SIGNAL(durationChanged(qint64)),this,SLOT(GetDuration()));//歌曲发生改变时调用获取歌曲总时长槽函数
}

PLAY::~PLAY()//析构函数
{
    Music_Media.stop();
    delete ui;
    delete Download;
    delete Play_Json;
}

void PLAY::Set_Theme_Color(QString Color)//设置主题颜色
{
    ui->Audio_Size->setVisible(false);
    ui->Play->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Back->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Next->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Audio->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Image->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
}

void PLAY::GetDuration()//获取歌曲总时长
{
    Muisc_Max_Leng = Music_Media.duration()/1000;//储存音乐时常
    ui->Music_Pos->setRange(0,Muisc_Max_Leng);//设置音乐进度条值范围
}

void PLAY::ON_Time_Out()//播放歌曲计时器调用槽函数
{
    ui->Music_Pos->setValue(Music_Media.position()/1000);//设置音乐进度条与播放器进度相同
    QString Minute = QString::number(ui->Music_Pos->value() / 60);//储存播放进度 分
    QString Second = QString::number(ui->Music_Pos->value() % 60);//储存播放进度 秒
    ui->Time->setText(Minute + ":" + Second + "/" + QString::number(Muisc_Max_Leng / 60) + ":" + QString::number(Muisc_Max_Leng % 60));//设置播放进度时间文本
    if(Music_Media.position()/1000 == Muisc_Max_Leng)//判断是否播放完毕
    {
        on_Next_clicked();
    }
}

void PLAY::on_Back_clicked()//上一曲按钮槽函数
{
    if(Play_Number == 0)//判断是否为第一首歌曲
    {
        Play_Number = Play_List.count() - 1;//是第一首歌曲则播放最后一首歌曲
    }
    else
    {
        Play_Number -=1;//上一首
    }
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));//设置暂停图标
    Change_Music();//音乐改变
}


void PLAY::on_Play_clicked()//播放或暂停按钮槽函数
{
    if(Music_Media.playbackState() == QMediaPlayer::PlayingState)//判断播放状态 播放中
    {
        ui->Play->setIcon(QIcon(":/Resource/Play.png"));
        Music_Media.pause();
    }
    else if(Music_Media.playbackState() == QMediaPlayer::StoppedState)//判断播放状态 停止中
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Change_Music();
    }
    else if(Music_Media.playbackState() == QMediaPlayer::PausedState)//判断播放状态 暂停中
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Music_Media.play();
    }
}


void PLAY::on_Next_clicked()//下一首按钮槽函数
{
    if(Play_Number == Play_List.count() - 1)//判断是否为最后一首歌曲
    {
        Play_Number = 0;//是最后一首歌曲则播放第一首歌曲
    }
    else
    {
        Play_Number +=1;//下一首
    }
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));//设置暂停图标
    Change_Music();//音乐改变
}


void PLAY::on_Audio_clicked()//音量大小按钮槽函数
{
    if(ui->Audio_Size->isVisible())//判断调整音量大小按钮可用性
    {
        ui->Audio_Size->setVisible(false);
    }
    else
    {
        ui->Audio_Size->setVisible(true);
    }
}


void PLAY::on_Image_clicked()//歌曲图片按钮槽函数
{
    Clicked_Music_Icon();
}

void PLAY::on_Music_Pos_sliderReleased()//音乐播放时间进度调整槽函数
{
    Music_Media.setPosition(ui->Music_Pos->value()*1000);//音乐进度跟随进度条位置而改变
}

void PLAY::on_Audio_Size_sliderReleased()//音量大小调整槽函数
{
    Audio_OP.setVolume((float)ui->Audio_Size->value()/100);//音量大小跟随进度条位置而改变
}

void PLAY::Play_Number_Update()//播放歌曲序号更新槽函数
{
    Play_Json->open(QFile::ReadOnly);//打开播放列表文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();
    Play_List = Temp_Json.array();//重新储存播放歌曲信息

    if(Play_Number > Play_List.count() - 1)
    {
        Play_Number = Play_List.count() - 1;
    }
}

void PLAY::Play_Number_Init()//播放歌曲序号初始化槽函数
{
    Play_Json->open(QFile::ReadOnly);//打开播放列表文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();
    Play_List = Temp_Json.array();//重新储存播放歌曲信息
    Play_Number = 0;//从头开始播放
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
    Change_Music();
}

void PLAY::Change_Music()//音乐改变函数
{
    Music_Media.stop();//音乐暂停
    Time.stop();//计时器暂停
    QString Play_Url;//播放音乐Url
    if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "W")//判断音乐平台
    {
        QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() + "&ids=[" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() + "]&br=3200000";//拼接Url
        //获取歌曲Url
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
            //储存播放Url
            Play_Url = Value_2.value("url").toString();

            //获取图片Url
            Reply = Manager->get(QNetworkRequest(QUrl("https://tenapi.cn/wyyinfo/?id=" + Play_List.at(Play_Number).toObject().value("Music_Id").toString())));
            EventLoop.exec();

            Temp = QJsonDocument::fromJson(Reply->readAll());

            Reply = Manager->get(QNetworkRequest(QUrl(Temp.object().value("data").toObject().value("cover").toString() + "?param=150y150")));
            EventLoop.exec();

            //保存Image
            QFile Image(".\\Data\\Music_Image.png");
            Image.open(QFile::WriteOnly);
            Image.write(Reply->readAll());
            Image.close();

            ui->Image->setIcon(QIcon("./Data/Music_Image.png"));

            if(Save_While_Listening == true)//判断是否开启边听边存功能
            {
                Download->start();//线程开启
                Download->run(Download_Url,0,Play_List.at(Play_Number).toObject().value("Music_Name").toString(),Play_List.at(Play_Number).toObject().value("Singer_Name").toString());//下载线程
            }
        }
        else
        {
            QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到下载问题");
            on_Next_clicked();
        }

    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "K")
    {
        QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Play_List.at(Play_Number).toObject().value("Music_Hash").toString() + "&album_id=" + Play_List.at(Play_Number).toObject().value("Album_Id").toString() + "&album_audio_id=" + Play_List.at(Play_Number).toObject().value("Album_Audio_Id").toString();//拼接Url
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
            //储存播放Url
            Play_Url = Root.value("data").toObject().value("play_url").toString();
            //获取图片
            Reply = Manager->get(QNetworkRequest(QUrl(Root.value("data").toObject().value("img").toString())));
            EventLoop.exec();

            //保存Image
            QFile Image(".\\Data\\Music_Image.png");
            Image.open(QFile::WriteOnly);
            Image.write(Reply->readAll());
            Image.close();

            ui->Image->setIcon(QIcon("./Data/Music_Image.png"));

            if(Save_While_Listening == true)
            {
                Download->start();//线程开启
                Download->run(Download_Url,1,Play_List.at(Play_Number).toObject().value("Music_Name").toString(),Play_List.at(Play_Number).toObject().value("Singer_Name").toString());//下载线程
            }
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
    Music_Media.setSource(QUrl(Play_Url));
    Music_Media.play();
    Time.start();
    ui->Name->setText(Play_List.at(Play_Number).toObject().value("Music_Name").toString()+ "    " +Play_List.at(Play_Number).toObject().value("Singer_Name").toString());
}