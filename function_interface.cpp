#include "function_interface.h"
#include "ui_function_interface.h"

Function_Interface::Function_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Function_Interface)
{
    ui->setupUi(this);
    this->move(0,0);
    this->show();

    connect(ui->Set,&QPushButton::clicked,[=](){
        emit Set();
    });
    connect(ui->Play,&QPushButton::clicked,[=](){
        emit Play();
    });
    connect(ui->Like,&QPushButton::clicked,[=](){
        emit Like();
    });
}

void Function_Interface::UI_Init(QFont Font,QString Color_Info)
{
    ui->Set->setToolTip("设置");
    ui->Like->setToolTip("喜欢列表");
    ui->Play->setToolTip("播放列表");

    ui->Set->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Like->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Play->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
}

Function_Interface::~Function_Interface()
{
    delete ui;
}
