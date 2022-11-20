#include "search.h"
#include "ui_search.h"

SEARCH::SEARCH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH)
{
    ui->setupUi(this);
    this->move(100,0);
    ui->Select->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");ui->Select->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");ui->Select->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");
}

SEARCH::~SEARCH()
{
    delete ui;
}

void SEARCH::on_PushButton_clicked()
{

}

