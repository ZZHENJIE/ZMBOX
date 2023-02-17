#include "player_interface.h"
#include "ui_player_interface.h"

Player_Interface::Player_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player_Interface)
{
    ui->setupUi(this);
    this->move(0,600);
    this->show();
}

void Player_Interface::UI_Init(QString Color_Info)
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
}

Player_Interface::~Player_Interface()
{
    delete ui;
}