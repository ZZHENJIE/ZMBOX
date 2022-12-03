#include "search.h"
#include "ui_search.h"

SEARCH::SEARCH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH)
{
    ui->setupUi(this);
    this->move(100,0);
    Download_Thread = new MThread();
    ui->Music_List->setVisible(false);
    ui->Play_Like->setVisible(false);
    ui->EverDayMusic->setVisible(true);
    Get_Ever_Day_Music();
}

SEARCH::~SEARCH()
{
    delete Data_Json;
    delete Like_Json;
    delete Play_Json;
    delete ui;
    delete Download_Thread;
}

void SEARCH::on_PushButton_clicked()
{
    if(!ui->Text->text().isEmpty())
    {
        ui->Music_List->clear();
        ui->Music_List->setVisible(true);
        ui->EverDayMusic->setVisible(false);
        ui->Play_Like->setVisible(false);
        switch(ui->Select->currentIndex())
        {
            case 0://网易云
            {
                //获取搜索结果
                QNetworkAccessManager *Manager = new QNetworkAccessManager();
                QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=" + ui->Text->text() + "&type=1&offset=0&total=true&limit=10")));
                QEventLoop EventLoop;
                connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
                EventLoop.exec();

                //解析json
                QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
                //1寻找键值 = "result"
                QJsonObject Root = Temp.object();
                QJsonValue Value_1 = Root.value("result");
                if(Value_1.isObject())
                {
                    //2寻找键值 = "songs"
                    QJsonValue Value_2 = Value_1.toObject().value("songs");
                    if(Value_2.isArray())
                    {
                        //3储存歌曲数组json object
                        QJsonArray Array_1 = Value_2.toArray();
                        //4遍历歌曲数组json object
                        for(int i = 0; i < Music_Max_Number;i++)
                        {
                            Value_1 = Array_1.at(i);
                            //5寻找键值 = "id"
                            Value_2 = Value_1.toObject().value("id");
                            if(Value_2.isDouble())
                            {
                                Cloud_Music_Id[i] = QString::number(Value_2.toInt());
                            }
                            //6寻找键值 = "name"
                            Value_2 = Value_1.toObject().value("name");
                            if(Value_2.isString())
                            {
                                Music_Name[i] = Value_2.toString();
                            }
                            //7寻找键值 = "artist"
                            Value_2 = Value_1.toObject().value("artists");
                            if(Value_2.isArray())
                            {
                                //8寻找键值 = "name"
                                QJsonValue Value_3 = Value_2.toArray().at(0).toObject().value("name");
                                if(Value_3.isString())
                                {
                                    Singer_Name[i] = Value_3.toString();
                                }
                            }
                        }
                    }
                }
                break;
            }
            case 1://QQ
            {
                for(int i = 0; i < Music_Max_Number;i++)
                {
                    Music_Name[i] = " ";
                    Singer_Name[i] = " ";
                }
                break;
            }
            case 2://酷狗
            {
                //获取搜索结果
                QNetworkAccessManager *Manager = new QNetworkAccessManager();
                QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("http://mobilecdn.kugou.com/api/v3/search/song?keyword=" + ui->Text->text() + "&page=1&pagesize=10")));
                QEventLoop EventLoop;
                connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
                EventLoop.exec();

                //解析json
                QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
                //1寻找键值 = "data"
                QJsonObject Root = Temp.object();
                QJsonValue Value_1 = Root.value("data");

                //2寻找键值 = "info"
                Root = Value_1.toObject();
                Value_1 = Root.value("info");
                if(Value_1.isArray())
                {
                    QJsonArray Array_1 = Value_1.toArray();

                    //3遍历info
                    for(int i = 0; i < Music_Max_Number; i++)
                    {
                        QJsonObject Value_2 = Array_1.at(i).toObject();

                        //4存储歌曲hash
                        Kugou_Music_Hash[i] = Value_2.value("hash").toString();

                        //5储存歌曲album_id
                        Kugou_Album_Id[i] = Value_2.value("album_id").toString();

                        //6储存歌曲album_audio_id
                        Kugou_Album_Audio_Id[i] = QString::number(Value_2.value("album_audio_id").toInt(),10);

                        //7存储歌曲名
                        Music_Name[i] = Value_2.value("songname").toString();

                        //8存储歌手名
                        Singer_Name[i] = Value_2.value("singername").toString();
                    }
                }
                break;
            }
        }
        for(int i = 0; i < Music_Max_Number;i++)
        {
            QListWidgetItem *Item = new QListWidgetItem;
            Item->setSizeHint(QSize(1160,50));//设置每行宽高
            Item->setText(Music_Name[i]+"       "+Singer_Name[i]);//设置文本
            ui->Music_List->addItem(Item);//添加至列表
        }
    }
}


void SEARCH::on_Music_List_itemClicked(QListWidgetItem *item)
{
    int Item_Number = ui->Music_List->currentRow();
    switch(ui->Select->currentIndex())
    {
        case 0://网易云音乐
        {
            Play_Json->open(QFile::ReadOnly);
            QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
            Play_Json->close();
            QJsonArray Root = Temp_Json.array();
            bool Find_Music = true;
            for(int i = 0; i < Root.count(); i++)
            {
                if(Root.at(i).toObject().value("Music_Id").toString() == Cloud_Music_Id[Item_Number])
                {
                    Find_Music = false;
                    break;
                }
            }
            if(Find_Music == true)
            {
                Play_Json->open(QFile::WriteOnly);

                QJsonObject Data;
                Data.insert("Platform","W");
                Data.insert("Music_Id",Cloud_Music_Id[Item_Number]);
                Data.insert("Music_Name",Music_Name[Item_Number]);
                Data.insert("Singer_Name",Singer_Name[Item_Number]);

                Root.append(Data);

                Temp_Json.setArray(Root);
                Play_Json->write(QByteArray(Temp_Json.toJson()));
                Play_Json->close();
            }
            break;
        }
        case 1://QQ音乐
        {
            break;
        }
        case 2://酷狗音乐
        {
            Play_Json->open(QFile::ReadOnly);
            QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
            Play_Json->close();
            QJsonArray Root = Temp_Json.array();
            bool Find_Music = true;
            for(int i = 0; i < Root.count(); i++)
            {
                if(Root.at(i).toObject().value("Album_Id").toString() == Kugou_Album_Id[Item_Number] && Root.at(i).toObject().value("Album_Audio_Id").toString() == Kugou_Album_Audio_Id[Item_Number])
                {
                    Find_Music = false;
                    break;
                }
            }
            if(Find_Music == true)
            {
                Play_Json->open(QFile::WriteOnly);

                QJsonObject Data;
                Data.insert("Platform","K");
                Data.insert("Music_Hash",Kugou_Music_Hash[Item_Number]);
                Data.insert("Album_Id",Kugou_Album_Id[Item_Number]);
                Data.insert("Album_Audio_Id",Kugou_Album_Audio_Id[Item_Number]);
                Data.insert("Music_Name",Music_Name[Item_Number]);
                Data.insert("Singer_Name",Singer_Name[Item_Number]);

                Root.append(Data);

                Temp_Json.setArray(Root);
                Play_Json->write(QByteArray(Temp_Json.toJson()));
                Play_Json->close();
            }
            break;
        }
    }
}
void SEARCH::Set_Theme_Color(QString Color)
{
    ui->PushButton->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Back->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;");
    ui->Music_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 15pt '楷体';");
    ui->EverDayMusic->setStyleSheet("background-color: rgba(0,0,0,0);");
    ui->line->setStyleSheet("background-color: rgba(" + Color + ");");

    ui->Select->setView(new QListView());
    ui->Select->setStyleSheet(
    "QComboBox {background-color: rgba(" + Color + ");border-radius: 10px;color:white;}" +
    "QComboBox QAbstractItemView{background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 20pt '楷体';icon-size: 50pt}" +
    "QComboBox QAbstractItemView::item {min-height: 60px;}QComboBox::drop-down{border-style: none;}"
    );
    ui->Select->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->Select->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    qApp->setEffectEnabled(Qt::UI_AnimateCombo, false);//去掉弹窗动画

    ui->Select->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");ui->Select->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");ui->Select->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");

    ui->List_0->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_1->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_2->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_3->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_4->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_5->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_6->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_7->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_8->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->List_9->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");

    ui->Add_Like->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Delete->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Download->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Play_All->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Like_Play_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
}
void SEARCH::on_Back_clicked()
{
    ui->Music_List->setVisible(false);
    ui->Play_Like->setVisible(false);
    ui->EverDayMusic->setVisible(true);
}

void SEARCH::Get_Ever_Day_Music()
{
    QNetworkAccessManager *Manager = new QNetworkAccessManager();
    QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("https://music.cyrilstudio.top/personalized?limit=10")));
    QEventLoop EventLoop;
    connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
    EventLoop.exec();

    //解析json
    QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
    //1寻找数组 = "list"
    QJsonObject Root = Temp.object();
    QJsonValue Value_1 = Root.value("result");
    QJsonArray List = Value_1.toArray();

    QString Image [10];

    for(int i = 0; i < 10; i++)
    {
        Image[i] = List.at(i).toObject().value("picUrl").toString();
    }

    for(int i = 0;i < 10; i++)
    {
        QFile Img(".\\Data\\List_png");
        Img.open(QFile::WriteOnly);
        Reply = Manager->get(QNetworkRequest(QUrl(Image[i])));
        connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
        EventLoop.exec();
        Img.write(Reply->readAll());
        Img.close();

        switch(i)
        {
            case 0:
            {
                ui->List_0->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 1:
            {
                ui->List_1->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 2:
            {
                ui->List_2->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 3:
            {
                ui->List_3->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 4:
            {
                ui->List_4->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 5:
            {
                ui->List_5->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 6:
            {
                ui->List_6->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 7:
            {
                ui->List_7->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 8:
            {
                ui->List_8->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
            case 9:
            {
                ui->List_9->setIcon(QIcon(".\\Data\\List_png"));
                break;
            }
        }

        QFile::remove(".\\Data\\List_png");
    }
}


void SEARCH::Play_List_Show()
{
    ui->Like_Play_List->clear();
    ui->Play_Like->setVisible(true);
    ui->Music_List->setVisible(false);
    ui->EverDayMusic->setVisible(false);
    ui->Add_Like->setVisible(true);

    Play_Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    QJsonArray Root = Temp_Json.array();

    for(int i = 0; i < Root.count();i++)
    {
        QListWidgetItem *Item = new QListWidgetItem;
        Item->setSizeHint(QSize(1160,50));//设置每行宽高
        Item->setText(Root.at(i).toObject().value("Music_Name").toString()+"       "+Root.at(i).toObject().value("Singer_Name").toString());//设置文本
        if(Root.at(i).toObject().value("Platform").toString() == "W")
        {
            Item->setIcon(QIcon(":/Resource/Cloud.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "K")
        {
            Item->setIcon(QIcon(":/Resource/KuGou.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "Q")
        {

        }
        ui->Like_Play_List->addItem(Item);//添加至列表
    }

    Play_Json->close();
}

void SEARCH::Like_List_Show()
{
    ui->Like_Play_List->clear();
    ui->Play_Like->setVisible(true);
    ui->Music_List->setVisible(false);
    ui->EverDayMusic->setVisible(false);
    ui->Add_Like->setVisible(false);

    Like_Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
    QJsonArray Root = Temp_Json.array();

    for(int i = 0; i < Root.count();i++)
    {
        QListWidgetItem *Item = new QListWidgetItem;
        Item->setSizeHint(QSize(1160,50));//设置每行宽高
        Item->setText(Root.at(i).toObject().value("Music_Name").toString()+"       "+Root.at(i).toObject().value("Singer_Name").toString());//设置文本
        if(Root.at(i).toObject().value("Platform").toString() == "W")
        {
            Item->setIcon(QIcon(":/Resource/Cloud.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "K")
        {
            Item->setIcon(QIcon(":/Resource/KuGou.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "Q")
        {

        }
        ui->Like_Play_List->addItem(Item);//添加至列表
    }

    Like_Json->close();
}

void SEARCH::on_Play_All_clicked()
{
    if(ui->Add_Like->isVisible())
    {
        
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();

        Play_Json->open(QFile::WriteOnly);
        Play_Json->write(QByteArray(Temp_Json.toJson()));
        Play_Json->close();
    }
}


void SEARCH::on_Delete_clicked()
{
    if(ui->Add_Like->isVisible())
    {
        Play_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();
        Play_Json->open(QFile::WriteOnly);
        QJsonArray Root = Temp_Json.array();

        Root.removeAt(ui->Like_Play_List->currentRow());

        Temp_Json.setArray(Root);
        Play_Json->write(QByteArray(Temp_Json.toJson()));
        Play_Json->close();

        Play_List_Show();
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();
        Like_Json->open(QFile::WriteOnly);
        QJsonArray Root = Temp_Json.array();

        Root.removeAt(ui->Like_Play_List->currentRow());

        Temp_Json.setArray(Root);
        Like_Json->write(QByteArray(Temp_Json.toJson()));
        Like_Json->close();

        Like_List_Show();
    }
}


void SEARCH::on_Download_clicked()
{
    Download_Thread->start();
    if(!QDir("./Music").exists())
    {
        QDir Temp_Dir;
        Temp_Dir.mkdir("./Music");//创建文件夹
    }
    if(ui->Add_Like->isVisible())
    {
        Play_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();
        QJsonObject Root = Temp_Json.array().at(ui->Like_Play_List->currentRow()).toObject();
        if(Root.value("Platform").toString() == "W")
        {
            QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Root.value("Music_Id").toString() + "&ids=[" + Root.value("Music_Id").toString() + "]&br=3200000";
            Download_Thread->run(Download_Url,0,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());
        }
        else if(Root.value("Platform").toString() == "K")
        {
            QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Root.value("Music_Hash").toString() + "&album_id=" + Root.value("Album_Id").toString() + "&album_audio_id=" + Root.value("Album_Audio_Id").toString();
            Download_Thread->run(Download_Url,2,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());
        }
        else if(Root.value("Platform").toString() == "Q")
        {
            
        }
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();
        QJsonObject Root = Temp_Json.array().at(ui->Like_Play_List->currentRow()).toObject();
        if(Root.value("Platform").toString() == "W")
        {
            QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Root.value("Music_Id").toString() + "&ids=" + Root.value("Music_Id").toString() + "&br=3200000";
            Download_Thread->run(Download_Url,0,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());
        }
        else if(Root.value("Platform").toString() == "K")
        {
            QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Root.value("Music_Hash").toString() + "&album_id=" + Root.value("Album_Id").toString() + "&album_audio_id=" + Root.value("Album_Audio_Id").toString();
            Download_Thread->run(Download_Url,2,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());
        }
        else if(Root.value("Platform").toString() == "Q")
        {
            
        }

    }
}


void SEARCH::on_Add_Like_clicked()
{
    Like_Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Like_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
    Like_Json->close();
    
    Play_Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Play_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();

    QJsonArray Play_Root = Temp_Play_Json.array();
    QJsonArray Like_Root = Temp_Like_Json.array();

    QJsonObject Add_Music = Play_Root.at(ui->Like_Play_List->currentRow()).toObject();

    bool This_Music = true;
    for(int i = 0; i < Like_Root.count(); i ++)
    {
        if(Like_Root.at(i).toObject() == Add_Music)
        {
            This_Music = false;
            break;
        }
    }

    if(This_Music == true)
    {
        Like_Json->open(QFile::WriteOnly);
        QJsonArray Root = Temp_Like_Json.array();
        Root.append(Add_Music);
        Temp_Like_Json.setArray(Root);
        Like_Json->write(QByteArray(Temp_Like_Json.toJson()));
        Like_Json->close();
    }
}
