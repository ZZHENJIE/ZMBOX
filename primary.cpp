#include "primary.h"
#include "ui_primary.h"

PRIMARY::PRIMARY(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PRIMARY)//构造函数
{
    ui->setupUi(this);
    this->move(100,90);

    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(true);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性

    Server = new SERVER();//创建服务器类和音乐类
    Cloud = new Cloud_Music();
    KuGou = new KuGou_Music();

    Cloud->Get_Recommended_Playlist("夜晚");//获取歌单

    Set_Recommended_Playlist();//设置歌单

    Data_Json->open(QFile::ReadOnly);//获取和设置用户名
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Data_Json->readAll()));
    Data_Json->close();
    Server->User_Name = Temp_Json.object().value("QQ_Name").toString();

    connect(Server,SIGNAL(Server_Send_Signals()),this,SLOT(Server_Send()));//连接服务器发送信号

    if(Temp_Json.object().value("ChatRoom").toBool() == true)
    {
        Server->Server_Connection();
    }
}

PRIMARY::~PRIMARY()//析构函数
{
    delete Server;
    delete Data_Json;
    delete Like_Json;
    delete Play_Json;
    delete ui;
    delete Cloud;
    delete KuGou;
}

void PRIMARY::Set_Theme_Color(QString Color)//设置主题颜色函数
{
    //搜索结果列表
    ui->Search_Music_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;font: 15pt '楷体';");
    ui->Search_Music_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽垂直滚动条
    ui->Search_Music_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽横向滚动条
    //推荐歌单
    ui->Recommended_Playlist->setStyleSheet("background-color: rgba(0,0,0,0);");
    //推荐歌单
    ui->List_0->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_1->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_2->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_3->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_4->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_5->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_6->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_7->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_8->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->List_9->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    //播放列表-喜欢列表
    ui->Add_Like_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Delete_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Download_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Play_All_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 5px;color:white;");
    ui->Like_Play_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->Like_Play_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽垂直滚动条
    ui->Like_Play_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽横向滚动条
    //聊天室
    ui->Message_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    ui->Send_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->Clear_Button->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
    ui->Input_Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;");
    //歌词
    ui->Lyrics_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;color:white;font: 15pt '楷体';");
    
    ui->Lyrics_List->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽垂直滚动条
    ui->Lyrics_List->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//屏蔽横向滚动条
    ui->Image->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 8px;");
}

void PRIMARY::Play_List_Show()//显示播放列表函数
{
    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
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

void PRIMARY::Like_List_Show()//显示喜欢列表函数
{
    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
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

void PRIMARY::Chat_Room_Show()//显示聊天室函数
{
    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(true);//设置聊天室窗体可用性
}

void PRIMARY::on_Search_Music_List_itemClicked(QListWidgetItem *item)//搜索音乐列表点击槽函数
{
    int Item_Number = ui->Search_Music_List->currentRow();//获取点击列表序号
    switch(Search_Platform)//判断搜索平台
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
                if(Root.at(i).toObject().value("Music_Id").toString() == Cloud_Search[Item_Number].Music_Id)
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
                Data.insert("Music_Id",Cloud_Search[Item_Number].Music_Id);
                Data.insert("Music_Name",Cloud_Search[Item_Number].Music_Name);
                Data.insert("Singer_Name",Cloud_Search[Item_Number].Singer_Name);
                Data.insert("Image_Url",Cloud_Search[Item_Number].Music_Image);

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
                if(Root.at(i).toObject().value("Album_Id").toString() == KuGou_Search[Item_Number].Album_Id && Root.at(i).toObject().value("Album_Audio_Id").toString() == KuGou_Search[Item_Number].Album_Audio_Id)
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
                Data.insert("Music_Hash",KuGou_Search[Item_Number].Music_Hash);
                Data.insert("Album_Id",KuGou_Search[Item_Number].Album_Id);
                Data.insert("Album_Audio_Id",KuGou_Search[Item_Number].Album_Audio_Id);
                Data.insert("Music_Name",KuGou_Search[Item_Number].Music_Name);
                Data.insert("Singer_Name",KuGou_Search[Item_Number].Singer_Name);

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
    Update_Music(false);
}

void PRIMARY::on_Play_All_Button_clicked()//点击播放全部槽函数
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

void PRIMARY::on_Delete_Button_clicked()//点击删除歌单内歌曲槽函数
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
    Update_Music(true);
}

void PRIMARY::on_Download_Button_clicked()//点击下载歌曲槽函数
{
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
            Cloud->Set_Id(Root.value("Music_Id").toString());
            Cloud->Download_Music();
        }
        else if(Root.value("Platform").toString() == "K")
        {
            KuGou->Set_Id(Root.value("Music_Hash").toString(),Root.value("Album_Id").toString(),Root.value("Album_Audio_Id").toString());
            KuGou->Download_Music();
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
            Cloud->Set_Id(Root.value("Music_Id").toString());
            Cloud->Download_Music();
        }
        else if(Root.value("Platform").toString() == "K")
        {
            KuGou->Set_Id(Root.value("Music_Hash").toString(),Root.value("Album_Id").toString(),Root.value("Album_Audio_Id").toString());
            KuGou->Download_Music();
        }
        else if(Root.value("Platform").toString() == "Q")
        {
            
        }
    }
}

void PRIMARY::on_Add_Like_Button_clicked()//点击添加到喜欢列表槽函数
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

void PRIMARY::on_Send_Button_clicked()//点击发送信息给服务器槽函数
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

void PRIMARY::on_Clear_Button_clicked()//点击清除信息列表和输入框槽函数
{
    ui->Input_Text->clear();//清空输入框信息
    ui->Message_List->clear();//清空信息列表信息
}

void PRIMARY::on_Like_Play_List_itemDoubleClicked(QListWidgetItem *item)//双击播放和喜欢列表槽函数
{
    if(ui->Add_Like_Button->isVisible())//判断是否为喜欢列表
    {
        Change_Music_Number(ui->Like_Play_List->currentRow());
    }
    else
    {
        Like_Json->open(QFile::ReadOnly);//读取喜欢列表信息
        QJsonDocument Temp_Like_Json = QJsonDocument::fromJson(QByteArray(Like_Json->readAll()));
        Like_Json->close();
        
        Play_Json->open(QFile::ReadOnly);//读取播放列表信息
        QJsonDocument Temp_Play_Json = QJsonDocument::fromJson(QByteArray(Play_Json->readAll()));
        Play_Json->close();

        QJsonArray Play_Root = Temp_Play_Json.array();//储存喜欢列表信息
        QJsonArray Like_Root = Temp_Like_Json.array();//储存播放列表信息

        QJsonObject Add_Music = Like_Root.at(ui->Like_Play_List->currentRow()).toObject();//储存需要添加的Json歌曲对象

        bool Find_Music = true;//查看喜欢列表是否有相同歌曲

        for(int i = 0; i < Play_Root.count(); i ++)//遍历喜欢列表
        {
            if(Play_Root.at(i).toObject() == Add_Music)//判断是否相同
            {
                Change_Music_Number(i);
                Find_Music = false;
                break;
            }
        }

        if(Find_Music == true)//如果没有相同歌曲就把Add_Music添加到喜欢列表
        {
            Play_Json->open(QFile::WriteOnly);
            QJsonArray Root = Temp_Play_Json.array();
            Root.append(Add_Music);
            Temp_Play_Json.setArray(Root);
            Play_Json->write(QByteArray(Temp_Play_Json.toJson()));
            Play_Json->close();

            Update_Music(false);

            Change_Music_Number(Root.count() - 1);
        }
    }
}

void PRIMARY::Server_Send()//服务器发送信息槽函数
{
    ui->Message_List->addItem(Server->Data.data());//服务器发送信息给客户端
}

void PRIMARY::Lyrics_Show()//显示歌词槽函数
{
    ui->Lyrics->setVisible(true);//设置歌词列表窗体可用性
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
}

void PRIMARY::Search_Button_clicked(int Platform,QString Text)//搜索按钮点击槽函数
{
    Search_Platform = Platform;
    ui->Search_Music_List->clear();//清空列表信息
    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(true);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(false);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性

    switch(Search_Platform)
    {
        case 0://网易云
        {
            Cloud->Get_Search_Data(Cloud_Search,Text,"10");
            for(int i = 0; i < Music_Max_Number;i++)
            {
                QListWidgetItem *Item = new QListWidgetItem;
                Item->setSizeHint(QSize(1160,50));//设置每行宽高
                Item->setText(Cloud_Search[i].Music_Name+"      "+Cloud_Search[i].Singer_Name);//设置文本
                ui->Search_Music_List->addItem(Item);//添加至列表
            }
            break;
        }
        case 1://酷狗
        {
            KuGou->Get_Search_Data(KuGou_Search,Text,"10");
            for(int i = 0; i < Music_Max_Number;i++)
            {
                QListWidgetItem *Item = new QListWidgetItem;
                Item->setSizeHint(QSize(1160,50));//设置每行宽高
                Item->setText(KuGou_Search[i].Music_Name+"      "+KuGou_Search[i].Singer_Name);//设置文本
                ui->Search_Music_List->addItem(Item);//添加至列表
            }
            break;
        }
        case 2://QQ
        {
            break;
        }
    }
}

void PRIMARY::Back_Button_clicked()//点击返回主页槽函数
{
    ui->Lyrics->setVisible(false);//设置歌词列表窗体可用性
    ui->Play_Like->setVisible(false);//设置喜欢列表播放列表窗体可用性
    ui->Search_Music_List->setVisible(false);//设置搜索列表窗体可用性
    ui->Recommended_Playlist->setVisible(true);//设置推荐歌单窗体可用性
    ui->Chat_Room->setVisible(false);//设置聊天室窗体可用性
}

void PRIMARY::Lyrics_Change(Music_Info Info)//歌词更新槽函数
{
    ui->Lyrics_List->clear();

    int Count = 0;//循环计数

    if(Info.Platform == "W")//判断音乐平台
    {
        ui->Image->setIcon(QIcon(".\\Image\\Cloud\\" + Info.Music_Id + ".png"));
        ui->Music_Info->setText(Info.Music_Name + " - " + Info.Singer_Name);

        QTextStream Lyrics(Info.Music_Lyrics);

        while(true)
        {
            QString Data = Lyrics.readLine();
            if(Data.isEmpty())
            {
                break;
            }
            else
            {
                Lyrics_Data[Count].Time = Data.mid(1,Data.lastIndexOf("]")-1);
                Data.remove(0,Data.lastIndexOf("]")+1);
                Lyrics_Data[Count].Lyrics = Data;

                QListWidgetItem *Item = new QListWidgetItem; 
                Item->setSizeHint(QSize(800,40));//设置每行宽高
                Item->setTextAlignment(Qt::AlignCenter);//设置文本居中
                Item->setText(Data);//设置文本
                ui->Lyrics_List->addItem(Item);
                Count++;
            }
        }
    }
    else if(Info.Platform == "K")
    {
        ui->Image->setIcon(QIcon(".\\Image\\KuGou\\" + Info.Music_Id + ".png"));
        ui->Music_Info->setText(Info.Music_Name + " - " + Info.Singer_Name);

        QTextStream Lyrics(Info.Music_Lyrics);

        while(true)
        {
            QString Data = Lyrics.readLine();
            if(Data.isEmpty())
            {
                break;
            }
            else
            {
                Lyrics_Data[Count].Time = Data.mid(1,Data.lastIndexOf("]")-1);
                Data.remove(0,Data.lastIndexOf("]")+1);
                Lyrics_Data[Count].Lyrics = Data;

                QListWidgetItem *Item = new QListWidgetItem;
                Item->setSizeHint(QSize(800,40));//设置每行宽高
                Item->setTextAlignment(Qt::AlignCenter);//设置文本居中
                Item->setText(Data);//设置文本
                ui->Lyrics_List->addItem(Item);
                Count++;
            }
        }
    }
    else if(Info.Platform == "Q")
    {

    }
}

void PRIMARY::Set_Recommended_Playlist()//设置歌单
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    ui->List_0->setIcon(QIcon(".\\Image\\List\\" + Root.at(0).toObject().value("Id").toString() + ".png"));

    ui->List_0->setToolTip(Root.at(0).toObject().value("Name").toString());

    ui->List_1->setIcon(QIcon(".\\Image\\List\\" + Root.at(1).toObject().value("Id").toString() + ".png"));

    ui->List_1->setToolTip(Root.at(1).toObject().value("Name").toString());

    ui->List_2->setIcon(QIcon(".\\Image\\List\\" + Root.at(2).toObject().value("Id").toString() + ".png"));

    ui->List_2->setToolTip(Root.at(2).toObject().value("Name").toString());

    ui->List_3->setIcon(QIcon(".\\Image\\List\\" + Root.at(3).toObject().value("Id").toString() + ".png"));

    ui->List_3->setToolTip(Root.at(3).toObject().value("Name").toString());

    ui->List_4->setIcon(QIcon(".\\Image\\List\\" + Root.at(4).toObject().value("Id").toString() + ".png"));

    ui->List_4->setToolTip(Root.at(4).toObject().value("Name").toString());

    ui->List_5->setIcon(QIcon(".\\Image\\List\\" + Root.at(5).toObject().value("Id").toString() + ".png"));

    ui->List_5->setToolTip(Root.at(5).toObject().value("Name").toString());

    ui->List_6->setIcon(QIcon(".\\Image\\List\\" + Root.at(6).toObject().value("Id").toString() + ".png"));

    ui->List_6->setToolTip(Root.at(6).toObject().value("Name").toString());

    ui->List_7->setIcon(QIcon(".\\Image\\List\\" + Root.at(7).toObject().value("Id").toString() + ".png"));

    ui->List_7->setToolTip(Root.at(7).toObject().value("Name").toString());

    ui->List_8->setIcon(QIcon(".\\Image\\List\\" + Root.at(8).toObject().value("Id").toString() + ".png"));

    ui->List_8->setToolTip(Root.at(8).toObject().value("Name").toString());

    ui->List_9->setIcon(QIcon(".\\Image\\List\\" + Root.at(9).toObject().value("Id").toString() + ".png"));

    ui->List_9->setToolTip(Root.at(9).toObject().value("Name").toString());
}


void PRIMARY::on_List_0_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(0).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_1_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(1).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_2_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(2).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_3_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(3).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_4_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(4).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_5_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(5).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_6_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(6).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_7_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(7).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_8_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(8).toObject().value("Id").toString());

    Update_Music(true);
}


void PRIMARY::on_List_9_clicked()
{
    List_Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(List_Json->readAll()));

    List_Json->close();

    QJsonArray Root = Temp_Json.array();

    Cloud->Get_Playlist_Details(Root.at(9).toObject().value("Id").toString());

    Update_Music(true);
}

