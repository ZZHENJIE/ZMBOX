#include "function_interface.h"
#include "ui_function_interface.h"

Function_Interface::Function_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Function_Interface)
{
    ui->setupUi(this);
    this->move(0,0);
    this->show();

    UI_Init();
}

void Function_Interface::UI_Init()
{
    ui->Set->setToolTip("设置");
    ui->Like->setToolTip("喜欢列表");
    ui->Play->setToolTip("播放列表");
}

Function_Interface::~Function_Interface()
{
    delete ui;
}
