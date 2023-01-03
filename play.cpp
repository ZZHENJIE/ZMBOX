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

    Cloud = new Cloud_Music();
    KuGou = new KuGou_Music();
    Image = new MThread();

    Audio_OP->setVolume(ui->Audio_Size->value() * 1.0);//初始化声音大小
    Music_Media->setAudioOutput(Audio_OP);//设置音频输出

    Time->setInterval(500);//设置计时器刷新时间

    connect(Time,SIGNAL(timeout()),this,SLOT(ON_Time_Out()));//超出设置计时器刷新时间调用ON_Time_Out()槽函数,并且重新计时

    connect(Music_Media,SIGNAL(durationChanged(qint64)),this,SLOT(GetDuration()));//歌曲发生改变时调用获取歌曲总时长槽函数
}

PLAY::~PLAY()//析构函数
{
    Music_Media->stop();
    delete ui;
    delete Play_Json;
    delete Audio_OP;
    delete Music_Media;
    delete Time;
    delete Cloud;
    delete KuGou;
    delete Image;
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
    Muisc_Max_Leng = Music_Media->duration()/1000;//储存音乐时常
    ui->Music_Pos->setRange(0,Muisc_Max_Leng);//设置音乐进度条值范围
}

void PLAY::ON_Time_Out()//播放歌曲计时器调用槽函数
{
    ui->Music_Pos->setValue(Music_Media->position()/1000);//设置音乐进度条与播放器进度相同
    QString Minute = QString::number(ui->Music_Pos->value() / 60);//储存播放进度 分
    QString Second = QString::number(ui->Music_Pos->value() % 60);//储存播放进度 秒
    ui->Time->setText(Minute + ":" + Second + "/" + QString::number(Muisc_Max_Leng / 60) + ":" + QString::number(Muisc_Max_Leng % 60));//设置播放进度时间文本
    if(Music_Media->position()/1000 == Muisc_Max_Leng)//判断是否播放完毕
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
    if(Music_Media->playbackState() == QMediaPlayer::PlayingState)//判断播放状态 播放中
    {
        ui->Play->setIcon(QIcon(":/Resource/Play.png"));
        Music_Media->pause();
    }
    else if(Music_Media->playbackState() == QMediaPlayer::StoppedState)//判断播放状态 停止中
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Change_Music();
    }
    else if(Music_Media->playbackState() == QMediaPlayer::PausedState)//判断播放状态 暂停中
    {
        ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
        Music_Media->play();
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
    Music_Media->setPosition(ui->Music_Pos->value()*1000);//音乐进度跟随进度条位置而改变
}

void PLAY::on_Audio_Size_sliderReleased()//音量大小调整槽函数
{
    Audio_OP->setVolume((float)ui->Audio_Size->value()/100);//音量大小跟随进度条位置而改变
}

void PLAY::Play_Number_Update(bool Delete)//播放歌曲序号更新槽函数
{
    Play_Json->open(QFile::ReadOnly);//打开播放列表文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();
    Play_List = Temp_Json.array();//重新储存播放歌曲信息

    if(Delete)//判断是否为删除事件
    {
        if(Play_Number > Play_List.count() - 1)
        {
            Play_Number = Play_List.count() - 1;
        }
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

void PLAY::Change_Music_Play(int Number)//播放歌曲改变
{
    Play_Number = Number;
    Change_Music();
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
}

void PLAY::Change_Music()//音乐改变函数
{
    Music_Media->stop();//音乐暂停
    Time->stop();//计时器暂停
    if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "W")//判断音乐平台
    {
        Cloud->Set_Id(Play_List.at(Play_Number).toObject().value("Music_Id").toString());

        if(Cloud->Get_Music_Available())//判断音乐神佛可下载
        {
            Music_Media->setSource(QUrl(Cloud->Get_Music_Play()));

            QFileInfo Image_File("./Image/Cloud/" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() +".png");
            if(Image_File.isFile() == false)
            {
                Image->run(Play_List.at(Play_Number).toObject().value("Image_Url").toString(),Play_List.at(Play_Number).toObject().value("Music_Id").toString(),"png",".\\Image\\Cloud\\");
            }

            ui->Image->setIcon(QIcon("./Image/Cloud/" + Play_List.at(Play_Number).toObject().value("Music_Id").toString() +".png"));

            if(Save_While_Listening == true)//判断是否开启边听边存功能
            {
                Cloud->Download_Music();
            }
        }
        else
        {
            QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到问题");
            on_Next_clicked();
        }

    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "K")
    {
        KuGou->Set_Id(Play_List.at(Play_Number).toObject().value("Music_Hash").toString(),Play_List.at(Play_Number).toObject().value("Album_Id").toString(),Play_List.at(Play_Number).toObject().value("Album_Audio_Id").toString());
        
        Music_Media->setSource(QUrl(KuGou->Get_Music_Play()));

        QFileInfo Image_File("./Image/KuGou/" + Play_List.at(Play_Number).toObject().value("Album_Id").toString() +".png");
        if(Image_File.isFile() == false)
        {
            Image->run(KuGou->Get_Music_Image(),Play_List.at(Play_Number).toObject().value("Album_Id").toString(),"png",".\\Image\\KuGou\\");
        }

        ui->Image->setIcon(QIcon("./Image/KuGou/" + Play_List.at(Play_Number).toObject().value("Album_Id").toString() +".png"));

        if(Save_While_Listening == true)
        {
            KuGou->Download_Music();
        }
    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "Q")
    {

    }
    Music_Media->play();
    Time->start();
    ui->Name->setText(Play_List.at(Play_Number).toObject().value("Music_Name").toString()+ "    " +Play_List.at(Play_Number).toObject().value("Singer_Name").toString());
    Preload_Image();
    Music_Info_Pack();
}

void PLAY::Preload_Image()//预加载图片函数
{
    int Temp_Play_Number = 0;

    if(Play_Number != Play_List.count() - 1)
    {
        Temp_Play_Number = Play_Number + 1;
    }

    if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "W")//判断音乐平台
    {
        QFileInfo Image_File("./Image/Cloud/" + Play_List.at(Temp_Play_Number).toObject().value("Music_Id").toString() +".png");
        if(Image_File.isFile() == false)
        {
            Image->run(Play_List.at(Temp_Play_Number).toObject().value("Image_Url").toString(),Play_List.at(Temp_Play_Number).toObject().value("Music_Id").toString(),"png",".\\Image\\Cloud\\");
        }
    }
    else if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "K")
    {
        QFileInfo Image_File("./Image/KuGou/" + Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString() +".png");
        if(Image_File.isFile() == false)
        {
            KuGou->Set_Id(Play_List.at(Temp_Play_Number).toObject().value("Music_Hash").toString(),Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString(),Play_List.at(Temp_Play_Number).toObject().value("Album_Audio_Id").toString());

            Image->run(KuGou->Get_Music_Image(),Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString(),"png",".\\Image\\KuGou\\");
        }
    }
    else if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "Q")
    {

    }

    if(Play_Number == 0)
    {
        Temp_Play_Number = Play_List.count() - 1;
    }
    else
    {
        Temp_Play_Number = Play_Number - 1;
    }

    if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "W")//判断音乐平台
    {
        QFileInfo Image_File("./Image/Cloud/" + Play_List.at(Temp_Play_Number).toObject().value("Music_Id").toString() +".png");
        if(Image_File.isFile() == false)
        {
            Image->run(Play_List.at(Temp_Play_Number).toObject().value("Image_Url").toString(),Play_List.at(Temp_Play_Number).toObject().value("Music_Id").toString(),"png",".\\Image\\Cloud\\");
        }
    }
    else if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "K")
    {
        QFileInfo Image_File("./Image/KuGou/" + Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString() +".png");
        if(Image_File.isFile() == false)
        {
            KuGou->Set_Id(Play_List.at(Temp_Play_Number).toObject().value("Music_Hash").toString(),Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString(),Play_List.at(Temp_Play_Number).toObject().value("Album_Audio_Id").toString());

            Image->run(KuGou->Get_Music_Image(),Play_List.at(Temp_Play_Number).toObject().value("Album_Id").toString(),"png",".\\Image\\KuGou\\");
        }
    }
    else if(Play_List.at(Temp_Play_Number).toObject().value("Platform").toString() == "Q")
    {

    }
}

void PLAY::Music_Info_Pack()//歌曲信息打包
{
    Music_Info Info;
    if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "W")//判断音乐平台
    {
        Info.Platform = "W";
        Info.Music_Id = Play_List.at(Play_Number).toObject().value("Music_Id").toString();
        Cloud->Set_Id(Info.Music_Id);
        Info.Music_Lyrics = Cloud->Get_Lyrics();
        Info.Music_Name = Play_List.at(Play_Number).toObject().value("Music_Name").toString();
        Info.Singer_Name = Play_List.at(Play_Number).toObject().value("Singer_Name").toString();
    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "K")
    {
        Info.Platform = "K";
        Info.Music_Id = Play_List.at(Play_Number).toObject().value("Album_Id").toString();
        KuGou->Set_Id(Play_List.at(Play_Number).toObject().value("Music_Hash").toString(),Info.Music_Id,Play_List.at(Play_Number).toObject().value("Album_Audio_Id").toString());
        Info.Music_Lyrics = KuGou->Get_Lyrics();
        Info.Music_Name = Play_List.at(Play_Number).toObject().value("Music_Name").toString();
        Info.Singer_Name = Play_List.at(Play_Number).toObject().value("Singer_Name").toString();
    }
    else if(Play_List.at(Play_Number).toObject().value("Platform").toString() == "Q")
    {
        Info.Platform = "Q";
    }
    Lyrics_Change(Info);
}