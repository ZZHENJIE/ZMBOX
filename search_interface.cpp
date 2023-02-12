#include "search_interface.h"
#include "ui_search_interface.h"

Search_Interface::Search_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_Interface)
{
    ui->setupUi(this);
    this->move(100,0);
    this->show();

    UI_Init();
}

void Search_Interface::UI_Init()
{
    ui->Back_Button->setToolTip("返回主页");
    ui->Search_Button->setToolTip("搜索");
    ui->Select_Platform->setToolTip("选择音乐平台");
}

Search_Interface::~Search_Interface()
{
    delete ui;
}
