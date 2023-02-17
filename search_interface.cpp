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

void Search_Interface::UI_Init(QString Color_Info)
{
    ui->Back_Button->setToolTip("返回主页");
    ui->Search_Button->setToolTip("搜索");
    ui->Select_Platform->setToolTip("选择音乐平台");

    ui->Select_Platform->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");

    ui->Back_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Search_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Search_Text->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");

    ui->Select_Platform->setStyleSheet(
    "QComboBox {background-color: rgba(" + Color_Info + ");border-radius: 10px;color:black;}" +
    "QComboBox QAbstractItemView{background-color: rgba(" + Color_Info + ");border-radius: 10px;color:black;icon-size: 50pt}" +
    "QComboBox QAbstractItemView::item {min-height: 60px;}QComboBox::drop-down{border-style: none;}"
    );
    ui->Select_Platform->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->Select_Platform->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
}

Search_Interface::~Search_Interface()
{
    delete ui;
}
