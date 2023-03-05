#include "search_interface.h"
#include "ui_search_interface.h"

Search_Interface::Search_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_Interface)
{
    ui->setupUi(this);
    this->move(100,0);
    this->show();

    connect(ui->Search_Button,&QPushButton::clicked,[=](){
        if(ui->Search_Text->text().isEmpty() == false)
        {
            emit Search(ui->Search_Text->text(),ui->Select_Platform->currentIndex());
        }
    });

    connect(ui->Back_Button,&QPushButton::clicked,[=](){
        emit Back();
    });

    ui->Select_Platform->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/Spotify.png"),"Spotify");
}

void Search_Interface::UI_Init(QFont Font,QString Color_Info)
{
    ui->Back_Button->setToolTip("返回主页");
    ui->Search_Button->setToolTip("搜索");

    ui->Back_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Search_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Search_Text->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");

    ui->Select_Platform->setStyleSheet(
    "QComboBox {background-color: rgba(" + Color_Info + ");border-radius: 5px;}" +
    "QComboBox QAbstractItemView{background-color: rgba(" + Color_Info + ");border-radius: 10px;color:black;icon-size: 50pt}" +
    "QComboBox QAbstractItemView::item {min-height: 60px;}QComboBox::drop-down{border-style: none;}"
    );
    ui->Select_Platform->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->Select_Platform->view()->window()->setAttribute(Qt::WA_TranslucentBackground);

    Font.setPointSize(20);

    ui->Select_Platform->setFont(Font);
    ui->Search_Text->setFont(Font);
}

Search_Interface::~Search_Interface()
{
    delete ui;
}
