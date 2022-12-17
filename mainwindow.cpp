#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)//构造函数
{
    ui->setupUi(this);
    this->setFixedSize(geometry().size());//设置窗口无法调整大小
    this->setWindowTitle("ZMBOX");//设置窗口标题

    QFile Data_Json("./Data/Data.json");//获取背景图片路径并且显示背景图片
    Data_Json.open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Data_Json.readAll()));
    Data_Json.close();
    ui->Background->setPixmap(QPixmap(Temp_Json.object().value("Background_Dir").toString()));

    if(Temp_Json.object().value("QQ_Logged").toBool() == true)//判断用户是否登入
    {
        User_Log_State = true;
    }

    Search = new SEARCH(this);//创建搜索类
    Play = new PLAY(this);//创建播放类

    Search->Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());//给两个类设置主题颜色
    Play->Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());
    Play->show();//把两个类显示出来
    Search->show();

    Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());//设置主窗口主题颜色

    connect(Play,SIGNAL(Clicked_Music_Icon()),Search,SLOT(Lyrics_Show()));//点击歌曲图片信号,显示歌词槽函数
    connect(Search,SIGNAL(Play_All()),Play,SLOT(Play_Number_Init()));//点击播放全部按钮信号,播放歌曲序号初始化槽函数
    connect(Search,SIGNAL(Update_Music()),Play,SLOT(Play_Number_Update()));//点击删除或添加歌曲信号,播放歌曲序号更新槽函数

}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
    delete Set;
    delete Play;
    delete Search;
}


void MainWindow::on_Set_clicked()//点击设置按钮槽函数
{
    Set = new SET();//创建设置窗口类
    Set->show();//显示设置窗口
    connect(Set,SIGNAL(Reboot_Signals()),this,SLOT(Reboot()));//连接设置类的重启信号
}

void MainWindow::on_Like_clicked()//点击喜欢列表槽函数
{
    Search->Like_List_Show();
}


void MainWindow::on_Play_clicked()//点击播放列表槽函数
{
    Search->Play_List_Show();
}


void MainWindow::on_Room_clicked()//点击聊天室槽函数
{
    if(User_Log_State == true)
    {
        Search->Chat_Room_Show();
    }
    else
    {
        QMessageBox::information(0,"提示","需要登入QQ才可使用聊天室功能,登入按钮在设置窗口内.");
    }
}

void MainWindow::Reboot()//设置类返回重启信号槽函数
{
    qApp->exit(REBOOT);
}

void MainWindow::Set_Theme_Color(QString Color)//设置主题颜色函数
{
    ui->line_1->setStyleSheet("background-color: rgba(" + Color + ");");
    ui->line_2->setStyleSheet("background-color: rgba(" + Color + ");");
}