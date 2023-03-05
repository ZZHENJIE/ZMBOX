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

    void Play_Select_Song(Song_Info Data,short SerialNumber);

private:
    Ui::Player_Interface *ui;
};

#endif // PLAYER_INTERFACE_H
