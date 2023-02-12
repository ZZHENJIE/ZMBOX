#include "set_interface.h"
#include "ui_set_interface.h"

Set_Interface::Set_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_Interface)
{
    ui->setupUi(this);
    this->move(100,90);
    this->show();

    UI_Init();

    connect(ui->Set_Background_Button,&QPushButton::clicked,this,&Set_Interface::Change_Background);
}

void Set_Interface::UI_Init()
{
    ui->Set_Background_Button->setToolTip("选择背景图片");
}

Set_Interface::~Set_Interface()
{
    delete ui;
}
