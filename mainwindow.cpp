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

    connect(SetInterface,&Set_Interface::Change_Background,this,&MainWindow::Change_Background);
}

void MainWindow::Change_Background()
{
    QString Image = QFileDialog::getOpenFileName(nullptr,"选择图片","C://","*.png");

    if(!Image.isEmpty())
    {
        ui->Background->setPixmap(Image);
    }
}

MainWindow::~MainWindow()
{
    delete FunctionInterface;
    delete PlayerInterface;
    delete SearchInterface;
    delete SetInterface;
    delete ui;
}

