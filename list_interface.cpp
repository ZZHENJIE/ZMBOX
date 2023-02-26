#include "list_interface.h"
#include "ui_list_interface.h"

List_Interface::List_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::List_Interface)
{
    ui->setupUi(this);
    this->move(100,90);
    this->show();
    GetTheRecommendedPlaylist(0);
}

List_Interface::~List_Interface()
{
    delete ui;
}

void List_Interface::UI_Init(QString Color_Info)
{
    ui->List->setStyleSheet("background-color: rgba(" + Color_Info + ");");
    ui->Song_List->setStyleSheet("background-color: rgba(" + Color_Info + ");");

    ui->Song_List->setIconSize(QSize(165,165));
    ui->Song_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Song_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void List_Interface::Search(QString KeyWord,int MusicPlatform)
{
    ui->List->setVisible(true);
    ui->Song_List->setVisible(false);

    ui->List->clear();

    Search_Info * Data = new Search_Info;

    switch(MusicPlatform)//0 网易云音乐 1 QQ音乐 2 酷狗音乐 3 Spotify
    {
        case 0:
        {
            Data = NetMusic::Search(KeyWord);
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            Data = SpotifyMusic::KuGouSearch(KeyWord);
            break;
        }
        case 3:
        {
            Data = SpotifyMusic::Search(KeyWord);
            break;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        QListWidgetItem * List = new QListWidgetItem();

        List->setText(Data[i].Song_Name + "     " + Data[i].Singer_Name);

        List->setSizeHint(QSize(1180,50));

        ui->List->addItem(List);
    }

    delete []Data;
}


void List_Interface::GetTheRecommendedPlaylist(int MusicPlatform)
{
    ui->List->setVisible(false);
    ui->Song_List->setVisible(true);

    ui->Song_List->clear();

    Song_List_Info * Data = new Song_List_Info;

    switch(MusicPlatform)
    {
        case 0:
        {
            Data = NetMusic::GetTheRecommendedPlaylist();
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
            break;
        }
    }

    for(int i = 0; i < 20; i++)
    {
        QListWidgetItem * List = new QListWidgetItem();

        List->setIcon(QIcon(Other::UrlToPixmap(Data[i].List_Image)));

        List->setToolTip(Data[i].List_Name);

        List->setSizeHint(QSize(165,165));

        ui->Song_List->addItem(List);
    }

    delete []Data;
}
