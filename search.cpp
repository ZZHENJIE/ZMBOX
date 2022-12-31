#include "search.h"
#include "ui_search.h"

SEARCH::SEARCH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH)//构造函数
{
    ui->setupUi(this);
    this->move(100,0);
}

SEARCH::~SEARCH()//析构函数
{
    delete ui;
}

void SEARCH::Set_Theme_Color(QString Color)//设置主题颜色函数
{
    //搜索栏
    ui->Search_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Back_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Search_Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;");
    //平台选择
    ui->Select_Platform->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");
    ui->Select_Platform->setStyleSheet(
    "QComboBox {background-color: rgba(" + Color + ");border-radius: 10px;color:white;}" +
    "QComboBox QAbstractItemView{background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 20pt '楷体';icon-size: 50pt}" +
    "QComboBox QAbstractItemView::item {min-height: 60px;}QComboBox::drop-down{border-style: none;}"
    );
    ui->Select_Platform->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->Select_Platform->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
}

void SEARCH::on_Search_Button_clicked()//搜索按钮点击槽函数
{
    if(!ui->Search_Text->text().isEmpty())
    {
        Search_Button_clicked(ui->Select_Platform->currentIndex(),ui->Search_Text->text());
    }
}

void SEARCH::on_Back_Button_clicked()//点击返回主页槽函数
{
    Back_Button_clicked();
}