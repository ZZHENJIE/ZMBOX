#include "player_interface.h"
#include "ui_player_interface.h"

Player_Interface::Player_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player_Interface)
{
    ui->setupUi(this);
    this->move(0,600);
    this->show();

    MediaPlayer = new QMediaPlayer(this);
    AudioOutput = new QAudioOutput(this);
    MediaPlayer->setAudioOutput(AudioOutput);
    AudioOutput->setVolume((float)ui->Audio_Size->value()/100);

    connect(MediaPlayer,&QMediaPlayer::durationChanged,[=](){
        ui->Music_Pos->setRange(0,MediaPlayer->duration());
    });
    connect(MediaPlayer, &QMediaPlayer::positionChanged,[=](qint64 Pos){
        if(MediaPlayer->duration() == MediaPlayer->position() && Pos > 1000)
        {
            emit Next_Music();
        }
        else
        {
            if(Music_Pos_Move)
            {
                ui->Music_Pos->setValue(Pos);
            }

            ui->Music_Time->setText(Other::MsToSec(Pos));

            for(int i = 0;i < Now_Music_Data.Lyrics.count(); i++)
            {
                if(Pos - Now_Music_Data.Lyrics.at(i).Time > 0 && Pos - Now_Music_Data.Lyrics.at(i).Time < 200)
                {
                    emit Lyrics_Select_Change(i);
                    break;
                }
            }
        }
    });
    connect(ui->Music_Pos,&QSlider::sliderReleased,[=](){
        Music_Pos_Move = true;
        MediaPlayer->setPosition(ui->Music_Pos->value());
    });
    connect(ui->Music_Pos,&QSlider::sliderPressed,[=](){
        Music_Pos_Move = false;
    });
    connect(ui->Audio_Size,&QSlider::sliderReleased,[=](){
        AudioOutput->setVolume((float)ui->Audio_Size->value()/100);
    });
    connect(ui->Audio_Show,&QPushButton::clicked,[=](){
        ui->Audio_Size->setVisible(!ui->Audio_Size->isVisible());
    });
    connect(ui->Play,&QPushButton::clicked,[=](){
        if(MediaPlayer->playbackState() == QMediaPlayer::PlayingState)
        {
            ui->Play->setIcon(QIcon(":/Resource/Play.png"));
            MediaPlayer->pause();
        }
        else if(MediaPlayer->playbackState() == QMediaPlayer::StoppedState || MediaPlayer->playbackState() == QMediaPlayer::PausedState)
        {
            ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
            MediaPlayer->play();
        }
    });

    connect(ui->Next,&QPushButton::clicked,this,emit &Player_Interface::Next_Music);
    connect(ui->Back,&QPushButton::clicked,this,emit &Player_Interface::Back_Music);
    connect(ui->Music_Image,&QPushButton::clicked,this,emit &Player_Interface::Lyrics_Interface_Show);
}

void Player_Interface::Play_Select_Song(Player_Music_Info Data)
{
    Now_Music_Data = Data;
    MediaPlayer->setSource(Data.Music);
    ui->Music_Text->setText(Data.Song_Singer_Name);
    ui->Music_Image->setIcon(QIcon(Data.Image));
    ui->Play->setIcon(QIcon(":/Resource/Paused.png"));
    MediaPlayer->play();
}

void Player_Interface::UI_Init(QFont Font,QString Color_Info)
{
    ui->Music_Image->setToolTip("歌词");
    ui->Back->setToolTip("上一首");
    ui->Next->setToolTip("下一首");
    ui->Play->setToolTip("播放或暂停");
    ui->Audio_Show->setToolTip("调整音量大小");

    ui->Music_Image->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Back->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Next->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Play->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Audio_Show->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");

    ui->Music_Text->setFont(Font);
    ui->Music_Time->setFont(Font);
}

Player_Interface::~Player_Interface()
{
    delete ui;
    delete MediaPlayer;
    delete AudioOutput;
}
