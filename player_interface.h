#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

#include "other.h"
#include "netmusic.h"

namespace Ui {
class Player_Interface;
}

class Player_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Player_Interface(QWidget *parent = nullptr);
    ~Player_Interface();

    void UI_Init(QFont Font,QString Color_Info = "255,255,255,255");

public Q_SLOTS:

    void Play_Select_Song(Player_Music_Info Data);

Q_SIGNALS:

    void Lyrics_Select_Change(short SerialNumber);

    void Lyrics_Interface_Show();

    void Next_Music();

    void Back_Music();

private:
    Ui::Player_Interface *ui;

    bool Music_Pos_Move = true;//调整歌曲进度

    Player_Music_Info Now_Music_Data;

    QMediaPlayer * MediaPlayer;
    QAudioOutput * AudioOutput;
};

#endif // PLAYER_INTERFACE_H
