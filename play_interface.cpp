#include "play_interface.h"
#include "ui_play_interface.h"

PLAY_INTERFACE::PLAY_INTERFACE(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLAY_INTERFACE)
{
    ui->setupUi(this);
    this->move(0,600);
    
}

PLAY_INTERFACE::~PLAY_INTERFACE()
{
    delete ui;
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

}


void PLAY_INTERFACE::on_Play_clicked()
{

}


void PLAY_INTERFACE::on_Next_clicked()
{

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

