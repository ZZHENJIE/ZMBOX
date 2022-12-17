#include "search.h"
#include "ui_search.h"

SEARCH::SEARCH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH)//构造函数
{
    ui->setupUi(this);
    this->move(100,0);

    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(true);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性

    Get_Recommended_Playlist();//推荐歌单

    Download_Thread = new MThread();//创建下载线程和服务器类
    Server = new SERVER();

    Data_Json->open(QFile::ReadOnly);//获取和设置用户名
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Data_Json->readAll()));
    Data_Json->close();
    Server->User_Name = Temp_Json.object().value("QQ_Name").toString();

    connect(Server,SIGNAL(Server_Send_Signals()),this,SLOT(Server_Send()));//连接服务器发送信号
}

SEARCH::~SEARCH()//析构函数
{
    delete Server;
    delete Data_Json;
    delete Like_Json;
    delete Play_Json;
    delete ui;
    delete Download_Thread;
}

void SEARCH::Set_Theme_Color(QString Color)//设置主题颜色函数
{
    //搜索栏
    ui->Search_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Back_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Search_Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;");
    //平台选择
    ui->Select_Platform->addItem(QIcon(":/Resource/Cloud.png"),"网易云音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/KuGou.png"),"酷狗音乐");
    ui->Select_Platform->addItem(QIcon(":/Resource/QQ.png"),"QQ音乐");
    ui->Select_Platform->setStyleSheet(
    "QComboBox {background-color: rgba(" + Color + ");border-radius: 10px;color:white;}" +
    "QComboBox QAbstractItemView{background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 20pt '楷体';icon-size: 50pt}" +
    "QComboBox QAbstractItemView::item {min-height: 60px;}QComboBox::drop-down{border-style: none;}"
    );
    ui->Select_Platform->view()->window()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    ui->Select_Platform->view()->window()->setAttribute(Qt::WA_TranslucentBackground);
    //搜索结果列表
    ui->Search_Music_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 15pt '楷体';");
    //推荐歌单
    ui->Recommended_Playlist->setStyleSheet("background-color: rgba(0,0,0,0);");
    //其他
    ui->line->setStyleSheet("background-color: rgba(" + Color + ");");
    //推荐歌单
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
    //播放列表-喜欢列表
    ui->Add_Like_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Delete_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Download_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Play_All_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Like_Play_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    //聊天室
    ui->Message_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->Send_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->Clear_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->Input_Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;");
}

void SEARCH::Play_List_Show()//显示播放列表函数
{
    ui->Like_Play_List->clear();//清空列表信息
    ui->Play_Like->setVisible(true);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
    ui->Add_Like_Button->setVisible(true);//因为播放列表没有添加至喜欢列表按钮,所以设置喜欢按钮的可用性

    Play_Json->open(QFile::ReadOnly);//打开播放Json文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));//读取Json文件信息
    Play_Json->close();//Json文件关闭

    QJsonArray Root = Temp_Json.array();//储存Json数组

    for(int i = 0; i < Root.count();i++)//遍历数组
    {
        QListWidgetItem *Item = new QListWidgetItem();
        Item->setSizeHint(QSize(1160,50));//设置每行宽高
        Item->setText(Root.at(i).toObject().value("Music_Name").toString()+"       "+Root.at(i).toObject().value("Singer_Name").toString());//设置每行文本
        if(Root.at(i).toObject().value("Platform").toString() == "W")//判断音乐平台
        {
            Item->setIcon(QIcon(":/Resource/Cloud.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "K")
        {
            Item->setIcon(QIcon(":/Resource/KuGou.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "Q")
        {
            Item->setIcon(QIcon(":/Resource/QQ.png"));
        }
        ui->Like_Play_List->addItem(Item);//添加至列表
    }
}

void SEARCH::Like_List_Show()//显示喜欢列表函数
{
    ui->Like_Play_List->clear();//清空列表信息
    ui->Play_Like->setVisible(true);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
    ui->Add_Like_Button->setVisible(false);//因为播放列表没有添加至喜欢列表按钮,所以设置喜欢按钮的可用性

    Like_Json->open(QFile::ReadOnly);//打开播放Json文件
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));//读取Json文件信息
    Like_Json->close();//Json文件关闭

    QJsonArray Root = Temp_Json.array();//储存Json数组

    for(int i = 0; i < Root.count();i++)//遍历数组
    {
        QListWidgetItem *Item = new QListWidgetItem();
        Item->setSizeHint(QSize(1160,50));//设置每行宽高
        Item->setText(Root.at(i).toObject().value("Music_Name").toString()+"       "+Root.at(i).toObject().value("Singer_Name").toString());//设置文本
        if(Root.at(i).toObject().value("Platform").toString() == "W")//判断音乐平台
        {
            Item->setIcon(QIcon(":/Resource/Cloud.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "K")
        {
            Item->setIcon(QIcon(":/Resource/KuGou.png"));
        }
        else if(Root.at(i).toObject().value("Platform").toString() == "Q")
        {
            Item->setIcon(QIcon(":/Resource/QQ.png"));
        }
        ui->Like_Play_List->addItem(Item);//添加至列表
    }
}

void SEARCH::Chat_Room_Show()//显示聊天室函数
{
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(true);//设置聊天室窗体可用性
}

void SEARCH::on_Search_Button_clicked()//搜索按钮点击槽函数
{
    if(!ui->Search_Text->text().isEmpty())
    {
        ui->Search_Music_List->clear();//清空列表信息
        ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
        ui->Search_Music_List->setVisible(true);//设置搜索列表窗体可用性
        ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
        ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
        switch(ui->Select_Platform->currentIndex())
        {
            case 0://网易云
            {
                //获取搜索结果
                QNetworkAccessManager *Manager = new QNetworkAccessManager();
                QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("http://music.163.com/api/search/get/web?csrf_token=hlpretag=&hlposttag=&s=" + ui->Search_Text->text() + "&type=1&offset=0&total=true&limit=10")));
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
            case 1://酷狗
            {
                //获取搜索结果
                QNetworkAccessManager *Manager = new QNetworkAccessManager();
                QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("http://mobilecdn.kugou.com/api/v3/search/song?keyword=" + ui->Search_Text->text() + "&page=1&pagesize=10")));
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
            case 2://QQ
            {
                for(int i = 0; i < Music_Max_Number;i++)
                {
                    Music_Name[i] = " ";
                    Singer_Name[i] = " ";
                }
                break;
            }
        }
        for(int i = 0; i < Music_Max_Number;i++)
        {
            QListWidgetItem *Item = new QListWidgetItem;
            Item->setSizeHint(QSize(1160,50));//设置每行宽高
            Item->setText(Music_Name[i]+"       "+Singer_Name[i]);//设置文本
            ui->Search_Music_List->addItem(Item);//添加至列表
        }
    }
}

void SEARCH::on_Search_Music_List_itemClicked(QListWidgetItem *item)//搜索音乐列表点击槽函数
{
    int Item_Number = ui->Search_Music_List->currentRow();//获取点击列表序号
    switch(ui->Select_Platform->currentIndex())//判断搜索平台
    {
        case 0://网易云音乐
        {
            Play_Json->open(QFile::ReadOnly);//获取播放列表内的信息
            QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
            Play_Json->close();
            QJsonArray Root = Temp_Json.array();//储存播放列表信息
            bool Find_Music = true;//查找相同歌曲
            for(int i = 0; i < Root.count(); i++)//判断播放列表内是否有相同歌曲
            {
                if(Root.at(i).toObject().value("Music_Id").toString() == Cloud_Music_Id[Item_Number])
                {
                    Find_Music = false;//有相同歌曲不需要再次存储
                    break;
                }
            }
            if(Find_Music == true)//没有相同歌曲时储存歌曲信息
            {
                Play_Json->open(QFile::WriteOnly);//打开文件

                QJsonObject Data;//需要储存的歌曲信息对象
                Data.insert("Platform","W");
                Data.insert("Music_Id",Cloud_Music_Id[Item_Number]);
                Data.insert("Music_Name",Music_Name[Item_Number]);
                Data.insert("Singer_Name",Singer_Name[Item_Number]);

                Root.append(Data);//添加到原有的Json数组尾部

                Temp_Json.setArray(Root);//把Root信息给Temp_Json
                Play_Json->write(QByteArray(Temp_Json.toJson()));//把信息写入(清空写入)播放列表
                Play_Json->close();//关闭文件
            }
            break;
        }
        case 1://酷狗音乐
        {
            Play_Json->open(QFile::ReadOnly);//获取播放列表内的信息
            QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
            Play_Json->close();
            QJsonArray Root = Temp_Json.array();//储存播放列表信息
            bool Find_Music = true;//查找相同歌曲
            for(int i = 0; i < Root.count(); i++)//判断播放列表内是否有相同歌曲
            {
                if(Root.at(i).toObject().value("Album_Id").toString() == Kugou_Album_Id[Item_Number] && Root.at(i).toObject().value("Album_Audio_Id").toString() == Kugou_Album_Audio_Id[Item_Number])
                {
                    Find_Music = false;//有相同歌曲不需要再次存储
                    break;
                }
            }
            if(Find_Music == true)//没有相同歌曲时储存歌曲信息
            {
                Play_Json->open(QFile::WriteOnly);//打开文件

                QJsonObject Data;//需要储存的歌曲信息对象
                Data.insert("Platform","K");
                Data.insert("Music_Hash",Kugou_Music_Hash[Item_Number]);
                Data.insert("Album_Id",Kugou_Album_Id[Item_Number]);
                Data.insert("Album_Audio_Id",Kugou_Album_Audio_Id[Item_Number]);
                Data.insert("Music_Name",Music_Name[Item_Number]);
                Data.insert("Singer_Name",Singer_Name[Item_Number]);

                Root.append(Data);//添加到原有的Json数组尾部

                Temp_Json.setArray(Root);//把Root信息给Temp_Json
                Play_Json->write(QByteArray(Temp_Json.toJson()));//把信息写入(清空写入)播放列表
                Play_Json->close();//关闭文件
            }
            break;
        }
        case 2://QQ音乐
        {
            break;
        }
    }
    Update_Music();
}

void SEARCH::on_Back_Button_clicked()//点击返回主页槽函数
{
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(true);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
}

void SEARCH::on_Play_All_Button_clicked()//点击播放全部槽函数
{
    if(!ui->Add_Like_Button->isVisible())//判断是否为喜欢列表,把喜欢列表给播放列表
    {
        Like_Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();

        Play_Json->open(QFile::WriteOnly);
        Play_Json->write(QByteArray(Temp_Json.toJson()));
        Play_Json->close();
    }
    Play_All();
}

void SEARCH::on_Delete_Button_clicked()//点击删除歌单内歌曲槽函数
{
    if(ui->Add_Like_Button->isVisible())//判断是否为喜欢列表
    {
        Play_Json->open(QFile::ReadOnly);//获取列表信息
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();
        
        QJsonArray Root = Temp_Json.array();//储存列表信息

        Play_Json->open(QFile::WriteOnly);//编辑列表信息

        Root.removeAt(ui->Like_Play_List->currentRow());//删除选中歌曲序号

        Temp_Json.setArray(Root);//把Root信息给Temp_Json
        Play_Json->write(QByteArray(Temp_Json.toJson()));//写入信息
        Play_Json->close();//关闭

        Play_List_Show();
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);//获取列表信息
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();
        
        QJsonArray Root = Temp_Json.array();//储存列表信息

        Like_Json->open(QFile::WriteOnly);//编辑列表信息

        Root.removeAt(ui->Like_Play_List->currentRow());//删除选中歌曲序号

        Temp_Json.setArray(Root);//把Root信息给Temp_Json
        Like_Json->write(QByteArray(Temp_Json.toJson()));//写入信息
        Like_Json->close();//关闭

        Like_List_Show();
    }
    Update_Music();
}

void SEARCH::on_Download_Button_clicked()//点击下载歌曲槽函数
{
    Download_Thread->start();//下载线程开始
    if(!QDir("./Music").exists())//判断是否有储存歌曲文件夹
    {
        QDir Temp_Dir;
        Temp_Dir.mkdir("./Music");//创建文件夹
    }
    if(ui->Add_Like_Button->isVisible())//判断是否为喜欢列表
    {
        Play_Json->open(QFile::ReadOnly);//读取列表信息
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();
        QJsonObject Root = Temp_Json.array().at(ui->Like_Play_List->currentRow()).toObject();//储存选择歌曲序号信息
        if(Root.value("Platform").toString() == "W")//判断音乐平台
        {
            QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Root.value("Music_Id").toString() + "&ids=[" + Root.value("Music_Id").toString() + "]&br=3200000";//下载链接
            Download_Thread->run(Download_Url,0,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());//多线程下载
        }
        else if(Root.value("Platform").toString() == "K")
        {
            QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Root.value("Music_Hash").toString() + "&album_id=" + Root.value("Album_Id").toString() + "&album_audio_id=" + Root.value("Album_Audio_Id").toString();//下载链接
            Download_Thread->run(Download_Url,1,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());//多线程下载
        }
        else if(Root.value("Platform").toString() == "Q")
        {
            
        }
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);//读取列表信息
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();
        QJsonObject Root = Temp_Json.array().at(ui->Like_Play_List->currentRow()).toObject();//储存选择歌曲序号信息
        if(Root.value("Platform").toString() == "W")//判断音乐平台
        {
            QString Download_Url = "http://music.163.com/api/song/enhance/player/url?id=" + Root.value("Music_Id").toString() + "&ids=" + Root.value("Music_Id").toString() + "&br=3200000";//下载链接
            Download_Thread->run(Download_Url,0,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());//多线程下载
        }
        else if(Root.value("Platform").toString() == "K")
        {
            QString Download_Url = "https://wwwapi.kugou.com/yy/index.php?r=play/getdata&hash=" + Root.value("Music_Hash").toString() + "&album_id=" + Root.value("Album_Id").toString() + "&album_audio_id=" + Root.value("Album_Audio_Id").toString();//下载链接
            Download_Thread->run(Download_Url,1,Root.value("Music_Name").toString(),Root.value("Singer_Name").toString());//多线程下载
        }
        else if(Root.value("Platform").toString() == "Q")
        {
            
        }

    }
}

void SEARCH::on_Add_Like_Button_clicked()//点击添加到喜欢列表槽函数
{
    Like_Json->open(QFile::ReadOnly);//读取喜欢列表信息
    QJsonDocument Temp_Like_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
    Like_Json->close();
    
    Play_Json->open(QFile::ReadOnly);//读取播放列表信息
    QJsonDocument Temp_Play_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
    Play_Json->close();

    QJsonArray Play_Root = Temp_Play_Json.array();//储存喜欢列表信息
    QJsonArray Like_Root = Temp_Like_Json.array();//储存播放列表信息

    QJsonObject Add_Music = Play_Root.at(ui->Like_Play_List->currentRow()).toObject();//储存需要添加的Json歌曲对象

    bool Find_Music = true;//查看喜欢列表是否有相同歌曲

    for(int i = 0; i < Like_Root.count(); i ++)//遍历喜欢列表
    {
        if(Like_Root.at(i).toObject() == Add_Music)//判断是否相同
        {
            Find_Music = false;
            break;
        }
    }

    if(Find_Music == true)//如果没有相同歌曲就把Add_Music添加到喜欢列表
    {
        Like_Json->open(QFile::WriteOnly);
        QJsonArray Root = Temp_Like_Json.array();
        Root.append(Add_Music);
        Temp_Like_Json.setArray(Root);
        Like_Json->write(QByteArray(Temp_Like_Json.toJson()));
        Like_Json->close();
    }
}

void SEARCH::on_Send_Button_clicked()//点击发送信息给服务器槽函数
{
    if(ui->Input_Text->text().size() < 1024)//判断输入字符数据大小
    {
        Server->Client_Send(ui->Input_Text->text());
    }
    else
    {
        QMessageBox::information(0,"提示","输入字符过多");
    }
}

void SEARCH::on_Clear_Button_clicked()//点击清除信息列表和输入框槽函数
{
    ui->Input_Text->clear();//清空输入框信息
    ui->Message_List->clear();//清空信息列表信息
}

void SEARCH::Server_Send()//服务器发送信息槽函数
{
    ui->Message_List->addItem(Server->Data.data());//服务器发送信息给客户端
}

void SEARCH::Lyrics_Show()//显示歌词槽函数
{
    
}

void SEARCH::Get_Recommended_Playlist()//获取推荐歌单
{
    //获取推荐歌单Json
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
        Image[i] = List.at(i).toObject().value("picUrl").toString();//储存图片下载链接
    }

    for(int i = 0;i < 10; i++)
    {
        QFile Img(".\\Data\\List_png");//下载图片并保存
        Img.open(QFile::WriteOnly);
        Reply = Manager->get(QNetworkRequest(QUrl(Image[i])));
        EventLoop.exec();
        Img.write(Reply->readAll());
        Img.close();

        switch(i)//遍历歌单按钮,设置按钮图片
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

        QFile::remove(".\\Data\\List_png");//删除图片
    }
}