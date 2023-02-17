#ifndef PLAYER_INTERFACE_H
#define PLAYER_INTERFACE_H

#include <QtWidgets/QWidget>

namespace Ui {
class Player_Interface;
}

class Player_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Player_Interface(QWidget *parent = nullptr);
    ~Player_Interface();

    void UI_Init(QString Color_Info = "255,255,255,255");

private:
    Ui::Player_Interface *ui;
};

#endif // PLAYER_INTERFACE_H
