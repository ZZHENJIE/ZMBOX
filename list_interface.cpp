#include "list_interface.h"
#include "ui_list_interface.h"

List_Interface::List_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::List_Interface)
{
    ui->setupUi(this);
    this->move(100,90);
    this->show();

    Back();
    Read_List();

    GetTheRecommendedPlaylist();
}

void List_Interface::Lyrics_Interface_Show()
{
    ui->Lyrics->setVisible(true);
    ui->Song_List_List->setVisible(false);
    ui->Song_List_Widget->setVisible(false);
}

void List_Interface::Lyrics_Select_Change(short SerialNumber)
{
    ui->Lyrics_List->setCurrentRow(SerialNumber);
}

void List_Interface::UpdataMusic()
{
    Player_Music_Info Data;

    ui->Lyrics_List->clear();

    Data.Song_Singer_Name = Play_List.at(Play_SerialNumber).Song_Name + "   " + Play_List.at(Play_SerialNumber).Singer_Name;

    switch(Play_List.at(Play_SerialNumber).MusicPlatform)
    {
        case 0:
        {
            NetMusic::GetMusicData(&Data,Play_List.at(Play_SerialNumber).Id);
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

    for(int i = 0; i < Data.Lyrics.count(); i ++)
    {
        QListWidgetItem *Item = new QListWidgetItem; 
        Item->setSizeHint(QSize(774,40));//设置每行宽高
        Item->setTextAlignment(Qt::AlignCenter);//设置文本居中
        Item->setText(Data.Lyrics.at(i).Data);//设置文本
        ui->Lyrics_List->addItem(Item);
    }

    if(Data.Image.isNull() == true)
    {
        Data.Image.load(":/Resource/Logo.png");
    }
    
    ui->Lyrics_Image->setIcon(QIcon(Data.Image));

    emit Play_Select_Song(Data);
}

void List_Interface::Next_Music()
{
    if(Play_SerialNumber == Play_List.count() - 1)//判断是否为最后一首歌曲
    {
        Play_SerialNumber = 0;//是最后一首歌曲则播放第一首歌曲
    }
    else
    {
        Play_SerialNumber +=1;//下一首
    }
    UpdataMusic();//音乐改变
}

void List_Interface::Back_Music()
{
    if(Play_SerialNumber == 0)//判断是否为第一首歌曲
    {
        Play_SerialNumber = Play_List.count() - 1;//是第一首歌曲则播放最后一首歌曲
    }
    else
    {
        Play_SerialNumber -=1;//上一首
    }
    UpdataMusic();//音乐改变
}

List_Interface::~List_Interface()
{
    Save_List();
    delete ui;
}

void List_Interface::Clear_Item()
{
    ui->Song_List->clear();

    emit Clear_Item_Signals();

    for(int i = 0; i < ui->Song_List->count(); i ++)
    {
        ui->Song_List->takeItem(i);
    }

    ui->Song_List->setFont(Font_);
}

void List_Interface::Next_Offset()
{
    switch(State)
    {
        case 1:
        {
            if(Like_List.count() - Offset_Count * 10 > 0)
            {
                Offset_Count ++;
                Like_List_Show();
            }
            break;
        }
        case 2:
        {
            if(Play_List.count() - Offset_Count * 10 > 0)
            {
                Offset_Count ++;
                Play_List_Show();
            }
            break;
        }
        case 30:
        {
            Offset_Count ++;
            Search(Search_KeyWord,0,Offset_Count);
            break;
        }
        case 31:
        {
            Offset_Count ++;
            Search(Search_KeyWord,1,Offset_Count);
            break;
        }
        case 32:
        {
            Offset_Count ++;
            Search(Search_KeyWord,2,Offset_Count);
            break;
        }
        case 33:
        {
            Offset_Count ++;
            Search(Search_KeyWord,3,Offset_Count);
            break;
        }
    }
}

void List_Interface::Back_Offset()
{
    if(Offset_Count > 1)
    {
        Offset_Count --;
        switch(State)
        {
            case 1:
            {
                Like_List_Show();
                break;
            }
            case 2:
            {
                Play_List_Show();
                break;
            }
            case 30:
            {
                Search(Search_KeyWord,0,Offset_Count);
                break;
            }
            case 31:
            {
                Search(Search_KeyWord,1,Offset_Count);
                break;
            }
            case 32:
            {
                Search(Search_KeyWord,2,Offset_Count);
                break;
            }
            case 33:
            {
                Search(Search_KeyWord,3,Offset_Count);
                break;
            }
        }
    }
}

void List_Interface::Play_List_Show()
{
    ui->Song_List_List->setVisible(false);
    ui->Lyrics->setVisible(false);
    ui->Song_List_Widget->setVisible(true);
    Clear_Item();

    if(State != 2)
    {
        Offset_Count = 1;
        State = 2;
    }

    for(int i = (Offset_Count * 10) - 10; i < (Offset_Count * 10 > Play_List.count() ? Play_List.count() : Offset_Count * 10) ; i ++)
    {
        QListWidgetItem * QListItem = new QListWidgetItem;
        MListWidgetItem * MListItem = new MListWidgetItem;

        QListItem->setSizeHint(QSize(1180, 70));

        MListItem->Play_Like_List(Play_List.at(i),i);

        ui->Song_List->addItem(QListItem);

        ui->Song_List->setItemWidget(QListItem, MListItem);

        connect(this,&List_Interface::Clear_Item_Signals,MListItem,&MListWidgetItem::Clear_Item);
        connect(MListItem,&MListWidgetItem::Delete_Song,[=](short SerialNumber){
            Play_List.removeAt(SerialNumber);
            Play_List_Show();
        });
        connect(MListItem,&MListWidgetItem::Play_Select_Song,[=](short SerialNumber){
            Play_SerialNumber = SerialNumber;
            UpdataMusic();
        });

        switch(Play_List.at(i).MusicPlatform)
        {
            case 0:
            {
                QListItem->setIcon(QIcon(":/Resource/Cloud.png"));
                break;
            }
            case 1:
            {
                QListItem->setIcon(QIcon(":/Resource/QQ.png"));
                break;
            }
            case 2:
            {
                QListItem->setIcon(QIcon(":/Resource/KuGou.png"));
                break;
            }
            case 3:
            {
                QListItem->setIcon(QIcon(":/Resource/Spotify.png"));
                break;
            }
        }
    }
}

void List_Interface::Like_List_Show()
{
    ui->Song_List_List->setVisible(false);
    ui->Lyrics->setVisible(false);
    ui->Song_List_Widget->setVisible(true);
    Clear_Item();

    if(State != 1)
    {
        Offset_Count = 1;
        State = 1;
    }

    for(int i = (Offset_Count * 10) - 10; i < (Offset_Count * 10 > Like_List.count() ? Like_List.count() : Offset_Count * 10) ; i ++)
    {
        QListWidgetItem * QListItem = new QListWidgetItem;
        MListWidgetItem * MListItem = new MListWidgetItem;

        QListItem->setSizeHint(QSize(1180, 70));

        MListItem->Play_Like_List(Like_List.at(i),i);

        ui->Song_List->addItem(QListItem);

        ui->Song_List->setItemWidget(QListItem, MListItem);

        connect(this,&List_Interface::Clear_Item_Signals,MListItem,&MListWidgetItem::Clear_Item);
        connect(MListItem,&MListWidgetItem::Delete_Song,[=](short SerialNumber){
            Like_List.removeAt(SerialNumber);
            Like_List_Show();
        });
        connect(MListItem,&MListWidgetItem::Play_Select_Song,[=](short SerialNumber){
            bool Is_Have = false;

            for(int i = 0; i < Play_List.count(); i++)
            {
                if(Like_List.at(SerialNumber).MusicPlatform == Play_List.at(i).MusicPlatform && (Like_List.at(SerialNumber).Id == Play_List.at(i).Id || Like_List.at(SerialNumber).Hash == Play_List.at(i).Hash))
                {
                    Play_SerialNumber = i;
                    Is_Have = true;
                    UpdataMusic();
                    break;
                }
            }

            if(Is_Have == false)
            {
                Play_List.append(Like_List.at(SerialNumber));
                Play_SerialNumber = Play_List.count() - 1;
                UpdataMusic();
            }
        });

        switch(Like_List.at(i).MusicPlatform)
        {
            case 0:
            {
                QListItem->setIcon(QIcon(":/Resource/Cloud.png"));
                break;
            }
            case 1:
            {
                QListItem->setIcon(QIcon(":/Resource/QQ.png"));
                break;
            }
            case 2:
            {
                QListItem->setIcon(QIcon(":/Resource/KuGou.png"));
                break;
            }
            case 3:
            {
                QListItem->setIcon(QIcon(":/Resource/Spotify.png"));
                break;
            }
        }
    }
}

void List_Interface::Read_List()
{
    //播放列表

    QFile Data_Json(".//Data//Play.json");

    Data_Json.open(QFile::ReadOnly);

    QJsonDocument Json_Doc = QJsonDocument::fromJson(Data_Json.readAll());

    Data_Json.close();

    if(Json_Doc.isEmpty() == false)
    {
        QJsonArray Data = Json_Doc.array();

        for(int i = 0; i < Data.size(); i ++)
        {
            Song_Info Temp;

            Temp.Song_Name = Data.at(i).toObject().value("Song_Name").toString();
            Temp.Singer_Name = Data.at(i).toObject().value("Singer_Name").toString();
            Temp.MusicPlatform = Data.at(i).toObject().value("MusicPlatform").toString().toInt();

            if(Temp.MusicPlatform == 2)
            {
                Temp.Hash = Data.at(i).toObject().value("Hash").toString();
                Temp.Album_id = Data.at(i).toObject().value("Album_id").toString();
                Temp.Album_audio_id = Data.at(i).toObject().value("Album_audio_id").toString();
            }
            else
            {
                Temp.Id = Data.at(i).toObject().value("Id").toString();
            }

            Play_List.append(Temp);
        }
    }

    //喜欢列表

    Data_Json.setFileName(".//Data//Like.json");

    Data_Json.open(QFile::ReadOnly);

    Json_Doc = QJsonDocument::fromJson(Data_Json.readAll());

    Data_Json.close();

    if(Json_Doc.isEmpty() == false)
    {
        QJsonArray Data = Json_Doc.array();

        for(int i = 0; i < Data.size(); i ++)
        {
            Song_Info Temp;

            Temp.Song_Name = Data.at(i).toObject().value("Song_Name").toString();
            Temp.Singer_Name = Data.at(i).toObject().value("Singer_Name").toString();
            Temp.MusicPlatform = Data.at(i).toObject().value("MusicPlatform").toString().toInt();

            if(Temp.MusicPlatform == 2)
            {
                Temp.Hash = Data.at(i).toObject().value("Hash").toString();
                Temp.Album_id = Data.at(i).toObject().value("Album_id").toString();
                Temp.Album_audio_id = Data.at(i).toObject().value("Album_audio_id").toString();
            }
            else
            {
                Temp.Id = Data.at(i).toObject().value("Id").toString();
            }

            Like_List.append(Temp);
        }
    }
}

void List_Interface::Save_List()
{
    //播放列表

    QFile Data_Json(".//Data//Play.json");

    QJsonDocument Json_Doc;

    if(Play_List.isEmpty() == false)
    {
        Data_Json.open(QFile::WriteOnly);

        QJsonArray Play_Data;

        for(int i = 0; i < Play_List.count(); i ++)
        {
            QJsonObject Temp;
            Temp.insert("Song_Name",Play_List.at(i).Song_Name);
            Temp.insert("Singer_Name",Play_List.at(i).Singer_Name);
            Temp.insert("MusicPlatform",QString::number(Play_List.at(i).MusicPlatform));

            if(Play_List.at(i).MusicPlatform == 2)
            {
                Temp.insert("Hash",Play_List.at(i).Hash);
                Temp.insert("Album_id",Play_List.at(i).Album_id);
                Temp.insert("Album_audio_id",Play_List.at(i).Album_audio_id);
            }
            else
            {
                Temp.insert("Id",Play_List.at(i).Id);
            }
            Play_Data.append(Temp);
        }

        Json_Doc.setArray(Play_Data);

        Data_Json.write(Json_Doc.toJson());

        Data_Json.close();
    }

    //喜欢列表

    Data_Json.setFileName(".//Data//Like.json");

    if(Like_List.isEmpty() == false)
    {

        Data_Json.open(QFile::WriteOnly);

        QJsonArray Like_Data;
    
        for(int i = 0; i < Like_List.count(); i ++)
        {
            QJsonObject Temp;
            Temp.insert("Song_Name",Like_List.at(i).Song_Name);
            Temp.insert("Singer_Name",Like_List.at(i).Singer_Name);
            Temp.insert("MusicPlatform",QString::number(Like_List.at(i).MusicPlatform));

            if(Like_List.at(i).MusicPlatform == 2)
            {
                Temp.insert("Hash",Like_List.at(i).Hash);
                Temp.insert("Album_id",Like_List.at(i).Album_id);
                Temp.insert("Album_audio_id",Like_List.at(i).Album_audio_id);
            }
            else
            {
                Temp.insert("Id",Like_List.at(i).Id);
            }
            Like_Data.append(Temp);
        }

        Json_Doc.setArray(Like_Data);

        Data_Json.write(Json_Doc.toJson());

        Data_Json.close();
    }
}

void List_Interface::Back()
{
    ui->Song_List_List->setVisible(true);
    ui->Lyrics->setVisible(false);
    ui->Song_List_Widget->setVisible(false);
    Clear_Item();
}

void List_Interface::UI_Init(QFont Font,QString Color_Info)
{
    ui->Song_List->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 10px;");
    ui->Song_List_List->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 10px;");
    ui->Lyrics_List->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 10px;");
    ui->Lyrics_Image->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 10px;");

    ui->Song_List_List->setIconSize(QSize(165,165));
    ui->Song_List_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Song_List_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->Song_List->setIconSize(QSize(55,55));
    ui->Song_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Song_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->Lyrics_List->setFont(Font);
    ui->Lyrics_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->Lyrics_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(ui->Next,&QPushButton::clicked,this,&List_Interface::Next_Offset);
    connect(ui->Back,&QPushButton::clicked,this,&List_Interface::Back_Offset);

    Font_ = Font;
}

void List_Interface::Search(QString KeyWord,int MusicPlatform,int Offset)
{
    ui->Song_List_List->setVisible(false);
    ui->Lyrics->setVisible(false);
    ui->Song_List_Widget->setVisible(true);

    Clear_Item();

    Song_Info * Data = new Song_Info;

    if(Search_KeyWord != KeyWord || State - 30 != MusicPlatform)
    {
        Offset_Count = 1;
        Search_KeyWord = KeyWord;
    }

    switch(MusicPlatform)//0 网易云音乐 1 QQ音乐 2 酷狗音乐 3 Spotify
    {
        case 0:
        {
            Data = NetMusic::Search(KeyWord,QString::number(Offset));
            State = 30;
            break;
        }
        case 1:
        {
            break;
        }
        case 2:
        {
            Data = SpotifyMusic::KuGouSearch(KeyWord,QString::number(Offset));
            State = 32;
            break;
        }
        case 3:
        {
            Data = SpotifyMusic::Search(KeyWord,QString::number(Offset - 1));
            State = 33;
            break;
        }
    }

    for(int i = 0; i < 10; i++)
    {
        QListWidgetItem * QListItem = new QListWidgetItem;
        MListWidgetItem * MListItem = new MListWidgetItem;

        Data[i].MusicPlatform = MusicPlatform;

        QListItem->setSizeHint(QSize(1180, 70));

        MListItem->Search(Data[i]);

        ui->Song_List->addItem(QListItem);

        ui->Song_List->setItemWidget(QListItem, MListItem);

        connect(MListItem,&MListWidgetItem::Add_Play,[=](Song_Info Data){
            bool Is_Have = false;

            for(int i = 0; i < Play_List.count();i++)
            {
                if(Play_List.at(i).MusicPlatform == Data.MusicPlatform)
                {
                    if((Play_List.at(i).MusicPlatform == 0 || Play_List.at(i).MusicPlatform == 3) && Data.Id == Play_List.at(i).Id)
                    {
                        Is_Have = true;
                        break;
                    }
                    else if(Play_List.at(i).MusicPlatform == 2 && Data.Hash == Play_List.at(i).Hash)
                    {
                        Is_Have = true;
                        break;
                    }
                }
            }

            if(Is_Have == false)
            {
                Play_List.append(Data);
            }
        });
        connect(MListItem,&MListWidgetItem::Add_Like,[=](Song_Info Data){
            bool Is_Have = false;

            for(int i = 0; i < Like_List.count();i++)
            {
                if(Like_List.at(i).MusicPlatform == Data.MusicPlatform)
                {
                    if((Like_List.at(i).MusicPlatform == 0 || Like_List.at(i).MusicPlatform == 3) && Data.Id == Like_List.at(i).Id)
                    {
                        Is_Have = true;
                        break;
                    }
                    else if(Like_List.at(i).MusicPlatform == 2 && Data.Hash == Like_List.at(i).Hash)
                    {
                        Is_Have = true;
                        break;
                    }
                }
            }
            
            if(Is_Have == false)
            {
                Like_List.append(Data);
            }
        });
        connect(this,&List_Interface::Clear_Item_Signals,MListItem,&MListWidgetItem::Clear_Item);
    }

    delete []Data;
}


void List_Interface::GetTheRecommendedPlaylist(int MusicPlatform)
{
    Back();

    State = 4;

    ui->Song_List_List->clear();

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

    for(int i = 0; i < 15; i++)
    {
        QListWidgetItem * QListItem = new QListWidgetItem;
        MListWidgetItem * MListItem = new MListWidgetItem;

        QListItem->setSizeHint(QSize(165, 165));

        MListItem->Song_List(Data[i]);

        ui->Song_List_List->addItem(QListItem);

        ui->Song_List_List->setItemWidget(QListItem, MListItem);
    }

    delete []Data;
}