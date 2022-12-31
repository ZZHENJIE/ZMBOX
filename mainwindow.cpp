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

    Tray = Temp_Json.object().value("Tray").toBool();//储存托盘功能

    if(Temp_Json.object().value("QQ_Logged").toBool() == true)//判断用户是否登入
    {
        User_Log_State = true;
    }

    Search = new SEARCH(this);//创建搜索类
    Play = new PLAY(this);//创建播放类
    Primary = new PRIMARY(this);//创建主要显示类

    Search->Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());//给三个类设置主题颜色
    Play->Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());
    Primary->Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());
    Play->show();//把三个类显示出来
    Search->show();
    Primary->show();

    Set_Theme_Color(Temp_Json.object().value("Theme_Color").toString());//设置主窗口主题颜色

    connect(this,SIGNAL(Like_clicked()),Primary,SLOT(Like_List_Show()));
    connect(this,SIGNAL(Play_clicked()),Primary,SLOT(Play_List_Show()));
    connect(this,SIGNAL(Room_clicked()),Primary,SLOT(Chat_Room_Show()));

    connect(Search,SIGNAL(Search_Button_clicked(int,QString)),Primary,SLOT(Search_Button_clicked(int,QString)));
    connect(Search,SIGNAL(Back_Button_clicked()),Primary,SLOT(Back_Button_clicked()));
    
    connect(Play,SIGNAL(Clicked_Music_Icon(Music_Info)),Primary,SLOT(Lyrics_Show(Music_Info)));//点击歌曲图片信号,显示歌词槽函数
    connect(Primary,SIGNAL(Play_All()),Play,SLOT(Play_Number_Init()));//点击播放全部按钮信号,播放歌曲序号初始化槽函数
    connect(Primary,SIGNAL(Update_Music(bool)),Play,SLOT(Play_Number_Update(bool)));//点击删除或添加歌曲信号,播放歌曲序号更新槽函数
    connect(Primary,SIGNAL(Change_Music_Number(int)),Play,SLOT(Change_Music_Play(int)));//改变歌曲
    connect(Next,SIGNAL(triggered()),Play,SLOT(on_Next_clicked()));//上一首信息
    connect(Back,SIGNAL(triggered()),Play,SLOT(on_Back_clicked()));//下一首信号
    connect(Play_Paused,SIGNAL(triggered()),Play,SLOT(on_Play_clicked()));//播放或暂停信号
    connect(Exit,SIGNAL(triggered()),this,SLOT(Quit()));//退出信号
    connect(SystemIcon,&QSystemTrayIcon::activated,this,&MainWindow::on_activatedSysTrayIcon);//点击系统托盘图标信号,处理事件槽函数
}

MainWindow::~MainWindow()//析构函数
{
    delete ui;
    delete Set;
    delete Play;
    delete Search;
    delete SystemIcon;
    delete Menu;
    delete Exit;
    delete Back;
    delete Next;
    delete Play_Paused;
    delete Primary;
}


void MainWindow::on_Set_clicked()//点击设置按钮槽函数
{
    Set = new SET();//创建设置窗口类
    Set->show();//显示设置窗口
    connect(Set,SIGNAL(Reboot_Signals()),this,SLOT(Reboot()));//连接设置类的重启信号
}

void MainWindow::on_Like_clicked()//点击喜欢列表槽函数
{
    Like_clicked();
}

void MainWindow::on_Play_clicked()//点击播放列表槽函数
{
    Play_clicked();
}

void MainWindow::on_Room_clicked()//点击聊天室槽函数
{
    if(User_Log_State == true)
    {
        Room_clicked();
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
    ui->line_3->setStyleSheet("background-color: rgba(" + Color + ");");
    //系统托盘
    SystemIcon->setIcon(QIcon(":/Resource/Logo.png"));//设置系统托盘图标
    SystemIcon->setToolTip("ZMBOX");//设置鼠标放在图标上提示

    Menu->addAction(Play_Paused);//播放或暂停
    Menu->addAction(Back);//上一首
    Menu->addAction(Next);//下一首
    Menu->addSeparator();//分割
    Menu->addAction(Exit);//退出
    SystemIcon->setContextMenu(Menu);//添加菜单至系统托盘
}

void MainWindow::closeEvent(QCloseEvent *Event)//覆写关闭函数
{
    this->hide();
    if(!SystemIcon->isVisible())
    {
        SystemIcon->show();
    }
}

void MainWindow::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason Reason)//点击系统托盘图标槽函数
{
    if(Reason == QSystemTrayIcon::Trigger)//单击托盘图标
    {
        this->show();
    }
}

void MainWindow::Quit()//退出程序槽函数
{
    qApp->exit(2);
}
