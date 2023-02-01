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

    Finterface = new Function_Interface(this);

    Finterface->show();
}

MainWindow::~MainWindow()
{
    delete Finterface;
    delete ui;
}

