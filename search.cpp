#include "search.h"
#include "ui_search.h"

SEARCH::SEARCH(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SEARCH)
{
    ui->setupUi(this);
    this->move(100,0);
    ui->Music_List->setVisible(false);
}

SEARCH::~SEARCH()
{
    delete Data_Json;
    delete Like_Json;
    delete Play_List_Json;
    delete ui;
}

void SEARCH::on_PushButton_clicked()
{
    if(!ui->Text->text().isEmpty())
    {
        ui->Music_List->clear();
        ui->Music_List->setVisible(true);
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
    Data_Json->open(QFile::ReadOnly);
    Json_File_Temp = QJsonDocument::fromJson(QByteArray(Data_Json->readAll()));
    QJsonObject Data_File_Root = Json_File_Temp.object();

    for(int i = 0; i < Music_Max_Number; i++)
    {
        if(item->text() == Music_Name[i]+"       "+Singer_Name[i])
        {
            if(Data_File_Root.value("Save_While_Listening").toBool())
            {

            }
            else
            {
                switch(ui->Select->currentIndex())
                {
                    case 0://网易云音乐
                    {
                        //获取音乐下载json
                        QNetworkAccessManager *Manager = new QNetworkAccessManager();
                        QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("http://music.163.com/api/song/enhance/player/url?id=" + Cloud_Music_Id[i] + "&ids=[" + Cloud_Music_Id[i] + "]&br=3200000")));
                        QEventLoop EventLoop;
                        connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
                        EventLoop.exec();

                        //解析json
                        QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
                        QJsonObject Root = Temp.object();
                        QJsonValue Value_1 = Root.value("data");
                        QJsonObject Value_2 = Value_1.toArray().at(0).toObject();

                        if(!Value_2.value("url").isNull())//判断音乐神佛可下载
                        {
                            //Test Play
                            QMediaPlayer *player = new QMediaPlayer();
                            QAudioOutput *audioOutput = new QAudioOutput();
                            player->setAudioOutput(audioOutput);
                            connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
                            player->setSource(QUrl::fromLocalFile(Value_2.value("url").toString()));
                            audioOutput->setVolume(50);
                            player->play();
                        }
                        break;
                    }
                    case 1://QQ音乐
                    {

                        break;
                    }
                    case 2://酷狗音乐
                    {
                        
                        break;
                    }
                }
            }
        }
    }

    Data_Json->close();
}

void SEARCH::Set_Theme_Color(QString Color)
{
    ui->PushButton->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
    ui->Text->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;color:white;");
    ui->Music_List->setStyleSheet("background-color: rgba(" + Color + ");border-radius: 10px;");
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
}