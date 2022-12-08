#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(geometry().size());//设置窗口无法调整大小
    this->setWindowTitle("ZMBOX");//设置窗口标题

    QFile Json("./Data/Data.json");
    Json.open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json.readAll()));
    QJsonObject Root = Temp_Json.object();
    ui->Background->setPixmap(QPixmap(Root.value("Background_Dir").toString()));//显示背景图片

    Json.close();

    Search = new SEARCH(this);
    Play_Interface = new PLAY_INTERFACE(this);
    Search->Set_Theme_Color(Root.value("Theme_Color").toString());
    Play_Interface->Set_Theme_Color(Root.value("Theme_Color").toString());
    Set_Theme_Color(Root.value("Theme_Color").toString());
    Play_Interface->show();
    Search->show();
    connect(Play_Interface,SIGNAL(Clicked_Icon()),Search,SLOT(Music_Data_Show()));
    connect(Search,SIGNAL(Play_All()),Play_Interface,SLOT(Play_Number_Init()));
    connect(Search,SIGNAL(Update_Music()),Play_Interface,SLOT(Update_Music_List()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete Set;
    delete Play_Interface;
    delete Search;
}


void MainWindow::on_Set_clicked()
{
    Set = new SET();
    Set->show();
    connect(Set,SIGNAL(Reboot_Signals()),this,SLOT(Reboot()));
}

void MainWindow::Set_Theme_Color(QString Color)
{
    ui->line_1->setStyleSheet("background-color: rgba(" + Color + ");");
    ui->line_2->setStyleSheet("background-color: rgba(" + Color + ");");
}


void MainWindow::on_Like_clicked()
{
    Search->Like_List_Show();
}


void MainWindow::on_Play_clicked()
{
    Search->Play_List_Show();
}


void MainWindow::on_Room_clicked()
{
    Search->Chat_Room_Show();
}

void MainWindow::Reboot()
{
    qApp->exit(REBOOT);
}
