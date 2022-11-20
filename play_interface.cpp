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
