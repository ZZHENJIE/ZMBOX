#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("ZMBOX");//设置窗口标题
    this->setWindowIcon(QIcon(":/Resource/Logo.ico"));//设置窗口图标
    this->setFixedSize(QSize(1280,720));//设置窗口固定大小

    FunctionInterface = new Function_Interface(this);
    PlayerInterface = new Player_Interface(this);
    SearchInterface = new Search_Interface(this);
    SetInterface = new Set_Interface(this);

    UI_Init();

    connect(SetInterface,&Set_Interface::Change_Background,this,&MainWindow::Change_Background);
    connect(SetInterface,&Set_Interface::Change_Theme,this,&MainWindow::Change_Theme);
}

void MainWindow::Change_Theme(QString Color_Info)
{
    FunctionInterface->UI_Init(Color_Info);
    PlayerInterface->UI_Init(Color_Info);
    SearchInterface->UI_Init(Color_Info);
    SetInterface->UI_Init(Color_Info);
}

void MainWindow::UI_Init()
{
    QFile Data_Json(".//Data//Set.json");

    Data_Json.open(QFile::ReadOnly);

    QJsonDocument Data_Doc = QJsonDocument::fromJson(Data_Json.readAll());

    QJsonObject Data = Data_Doc.object();

    ui->Background->setPixmap(Data.value("Background").toString());

    FunctionInterface->UI_Init(Data.value("Theme").toString());
    PlayerInterface->UI_Init(Data.value("Theme").toString());
    SearchInterface->UI_Init(Data.value("Theme").toString());
    SetInterface->UI_Init(Data.value("Theme").toString());

    Data_Json.close();
}

void MainWindow::Change_Background(QString Image_Url)
{
    ui->Background->setPixmap(Image_Url);
}

MainWindow::~MainWindow()
{
    delete FunctionInterface;
    delete PlayerInterface;
    delete SearchInterface;
    delete SetInterface;
    delete ui;
}

