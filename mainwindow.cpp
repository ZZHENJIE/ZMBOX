#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ZMBOX");//设置窗口标题
    this->setFixedSize(QSize(1280,720));//设置窗口固定大小

    Net_Music = new QProcess(this);
    Spotify_KuGou = new QProcess(this);
    Font = new QFont(QFontDatabase::applicationFontFamilies(QFontDatabase::addApplicationFont(":/Resource/QingNingYouYuan.ttf")).at(0),15);
    Font->setLetterSpacing(QFont::PercentageSpacing,120);

    Net_Music->start(".\\API\\网易云音乐API.exe");
    Spotify_KuGou->start(".\\API\\Spotify-Kugou-API.exe");

    FunctionInterface = new Function_Interface(this);
    PlayerInterface = new Player_Interface(this);
    SearchInterface = new Search_Interface(this);
    SetInterface = new Set_Interface(this);
    ListInterface = new List_Interface(this);

    UI_Init();

    connect(SetInterface,&Set_Interface::Change_Background,this,&MainWindow::Change_Background);
    connect(SetInterface,&Set_Interface::Change_Theme,this,&MainWindow::Change_Theme);
    connect(SearchInterface,&Search_Interface::Search,this,&MainWindow::Search);
    connect(ListInterface,&List_Interface::Play_Select_Song,PlayerInterface,&Player_Interface::Play_Select_Song);
    connect(FunctionInterface,&Function_Interface::Play,[=](){
        SetInterface->setVisible(false);
        ListInterface->setVisible(true);
        ListInterface->Play_List_Show();
    });
    connect(FunctionInterface,&Function_Interface::Like,[=](){
        SetInterface->setVisible(false);
        ListInterface->setVisible(true);
        ListInterface->Like_List_Show();
    });
    connect(FunctionInterface,&Function_Interface::Set,[=](){
        SetInterface->setVisible(true);
        ListInterface->setVisible(false);
    });
    connect(SearchInterface,&Search_Interface::Back,[=](){
        SetInterface->setVisible(false);
        ListInterface->setVisible(true);
        ListInterface->Back();
    });
    connect(SetInterface,&Set_Interface::ReBoot_Nodejs,[=](){
        Net_Music->close();
        Net_Music->start(".\\API\\网易云音乐API.exe");
    });
    connect(PlayerInterface,&Player_Interface::Back_Music,ListInterface,&List_Interface::Back_Music);
    connect(PlayerInterface,&Player_Interface::Next_Music,ListInterface,&List_Interface::Next_Music);
    connect(PlayerInterface,&Player_Interface::Lyrics_Interface_Show,ListInterface,&List_Interface::Lyrics_Interface_Show);
    connect(PlayerInterface,&Player_Interface::Lyrics_Select_Change,ListInterface,&List_Interface::Lyrics_Select_Change);
}

void MainWindow::Search(QString KeyWord,int MusicPlatform)
{
    SetInterface->setVisible(false);
    ListInterface->setVisible(true);
    ListInterface->Search(KeyWord,MusicPlatform);
}

void MainWindow::Change_Theme(QString Color_Info)
{
    FunctionInterface->UI_Init(Color_Info);
    PlayerInterface->UI_Init(Color_Info);
    SearchInterface->UI_Init(Color_Info);
    SetInterface->UI_Init(Color_Info);
    ListInterface->UI_Init(Color_Info);
}

void MainWindow::UI_Init()
{
    SetInterface->setVisible(false);
    ListInterface->setVisible(true);

    QFile Data_Json(".//Data//Set.json");

    Data_Json.open(QFile::ReadOnly);

    QJsonDocument Data_Doc = QJsonDocument::fromJson(Data_Json.readAll());

    QJsonObject Data = Data_Doc.object();

    ui->Background->setPixmap(Data.value("Background").toString());

    FunctionInterface->UI_Init(*Font,Data.value("Theme").toString());
    PlayerInterface->UI_Init(*Font,Data.value("Theme").toString());
    SearchInterface->UI_Init(*Font,Data.value("Theme").toString());
    SetInterface->UI_Init(*Font,Data.value("Theme").toString());
    ListInterface->UI_Init(*Font,Data.value("Theme").toString());

    QApplication::setFont(*Font);
}

void MainWindow::Change_Background(QString Image_Url)
{
    ui->Background->setPixmap(Image_Url);
}

MainWindow::~MainWindow()
{
    Net_Music->close();
    Spotify_KuGou->close();

    delete Net_Music;
    delete Spotify_KuGou;
    delete Font;
    delete FunctionInterface;
    delete PlayerInterface;
    delete SearchInterface;
    delete SetInterface;
    delete ListInterface;
    delete ui;
}

