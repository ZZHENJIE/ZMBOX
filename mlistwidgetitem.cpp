#include "mlistwidgetitem.h"

MListWidgetItem::MListWidgetItem(QWidget *parent)
    : QWidget{parent}
{
    Button_1 = new QPushButton(this);
    Button_2 = new QPushButton(this);
    Button_3 = new QPushButton(this);
    Text = new QLabel(this);

    Button_1->show();
    Button_2->show();
    Button_3->show();
    Text->show();
}

void MListWidgetItem::Clear_Item()
{
    this->deleteLater();
}

MListWidgetItem::~MListWidgetItem()
{
    delete Button_1;
    delete Button_2;
    delete Button_3;
    delete Text;
}

void MListWidgetItem::Search(Song_Info Data)
{
    Info = Data;

    Text->setText(Info.Song_Name + "    " + Info.Singer_Name);

    Text->setGeometry(QRect(20,5,840,60));
    Button_1->setGeometry(QRect(900,5,60,60));
    Button_2->setGeometry(QRect(1000,5,60,60));
    Button_3->setGeometry(QRect(1100,5,60,60));

    Button_1->setIconSize(QSize(55,55));
    Button_2->setIconSize(QSize(55,55));
    Button_3->setIconSize(QSize(55,55));

    Button_1->setToolTip("添加到播放列表");
    Button_2->setToolTip("添加到喜欢列表");
    Button_3->setToolTip("下载");

    Button_1->setIcon(QIcon(":/Resource/Play_List.png"));
    Button_2->setIcon(QIcon(":/Resource/Like_List.png"));
    Button_3->setIcon(QIcon(":/Resource/Download.png"));
    
    connect(Button_1,&QPushButton::clicked,[=](){
        emit Add_Play(Info);
    });
    connect(Button_2,&QPushButton::clicked,[=](){
        emit Add_Like(Info);
    });
    connect(Button_3,&QPushButton::clicked,[=](){
        QString Url = NetMusic::GetMusicUrl(Info.Id);
        if(Url.isEmpty() == false){
            QDesktopServices::openUrl(QUrl(Url));
        }
    });
}

void MListWidgetItem::Play_Like_List(Song_Info Data,short SerialNumber)
{
    Info = Data;
    List_SerialNumber = SerialNumber;

    Text->setText(Info.Song_Name + "    " + Info.Singer_Name);

    Text->setGeometry(QRect(20,5,740,60));
    Button_1->setGeometry(QRect(800,5,60,60));
    Button_2->setGeometry(QRect(900,5,60,60));
    Button_3->setGeometry(QRect(1000,5,60,60));

    Button_1->setIconSize(QSize(55,55));
    Button_2->setIconSize(QSize(55,55));
    Button_3->setIconSize(QSize(55,55));

    Button_1->setToolTip("播放当前歌曲");
    Button_2->setToolTip("删除");
    Button_3->setToolTip("下载");

    Button_1->setIcon(QIcon(":/Resource/Play.png"));
    Button_2->setIcon(QIcon(":/Resource/Delete.png"));
    Button_3->setIcon(QIcon(":/Resource/Download.png"));
    
    connect(Button_1,&QPushButton::clicked,[=](){
        emit Play_Select_Song(List_SerialNumber);
    });
    connect(Button_2,&QPushButton::clicked,[=](){
        emit Delete_Song(SerialNumber);
    });
    connect(Button_3,&QPushButton::clicked,[=](){
        QString Url = NetMusic::GetMusicUrl(Info.Id);
        if(Url.isEmpty() == false){
            QDesktopServices::openUrl(QUrl(Url));
        }
    });
}

void MListWidgetItem::Song_List(Song_List_Info Data)
{
    List_Info = Data;
    
    Text->setVisible(false);
    Button_2->setVisible(false);
    Button_3->setVisible(false);

    Button_1->setGeometry(QRect(0,0,165,165));

    Button_1->setIconSize(QSize(165,165));

    Button_1->setToolTip(List_Info.List_Name);

    Button_1->setIcon(QIcon(Other::UrlToPixmap(List_Info.List_Image)));
}