#include "set.h"
#include "ui_set.h"

SET::SET(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Set)
{
    ui->setupUi(this);
    this->setFixedSize(geometry().size());//设置窗口无法调整大小
    this->setWindowTitle("设置");//设置窗口标题
    this->setWindowIcon(QIcon(":/Resource/Set.png"));//设置窗口图标
    
    if(!QDir("./Data").exists())//如果没有文件夹返回真
    {
        QDir Temp_Dir;
        Temp_Dir.mkdir("./Data");//创建文件夹

        QFile Temp_File("./Data/Like.json");//创建喜欢列表文件
        Temp_File.open(QFile::WriteOnly);
        Temp_File.close();
        Temp_File.setFileName("./Data/Play_List.json");//创建播放列表文件
        Temp_File.open(QFile::WriteOnly);
        Temp_File.close();
        
        Json->open(QFile::WriteOnly);

        QJsonObject Root;//写入Data文件的值
        Root.insert("QQ_Logged",false);
        Root.insert("QQ_Number"," ");
        Root.insert("QQ_Image_Url"," ");
        Root.insert("QQ_Name"," ");
        Root.insert("Background_Dir",":/Resource/Background.png");
        Root.insert("Save_While_Listening",false);
        Root.insert("Theme_Color","96,111,228,150");

        QJsonDocument Temp_Json;
        Temp_Json.setObject(Root);
        Json->write(QByteArray(Temp_Json.toJson()));

        Json->close();
    }
    Json->open(QFile::ReadOnly);

    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    QJsonObject Root = Temp_Json.object();
    ui->Background_Image->setPixmap(QPixmap(Root.value("Background_Dir").toString()));//预览背景图片
    ui->Color->setStyleSheet("background-color: rgba(" + Root.value("Theme_Color").toString() + ")");//预览主题颜色

    if(Root.value("Save_While_Listening").toBool())//检查边听边存功能
    {
        ui->Open->setChecked(true);
        ui->Close->setChecked(false);
    }
    else
    {
        ui->Open->setChecked(false);
        ui->Close->setChecked(true);
        ui->Open_Dir->setVisible(false);
    }

    if(Root.value("QQ_Logged").toBool())//检查QQ登入功能
    {
        ui->Image->setPixmap(QPixmap("./Data/Image.png"));
        ui->Name->setText(Root.value("QQ_Name").toString());
        ui->Log->setVisible(true);
        ui->Not_Log->setVisible(false);
    }
    else
    {
        ui->Log->setVisible(false);
        ui->Not_Log->setVisible(true);
    }

    Json->close();
}

SET::~SET()
{
    delete ui;
}

void SET::on_Select_Background_clicked()
{
    QString Image_Url = QFileDialog::getOpenFileName(this,"选择图片","c://",tr("*png;"));
    if(!Image_Url.isEmpty())
    {
        Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
        Json->close();
        Json->open(QFile::WriteOnly);
        QJsonObject Root = Temp_Json.object();

        QJsonValueRef Value = Root.find("Background_Dir").value();
        Value = QJsonValue(Image_Url);

        Temp_Json.setObject(Root);
        Json->write(QByteArray(Temp_Json.toJson()));

        Json->close();

        QMessageBox::information(0,"提示","修改背景后需要重新启动软件");
        this->close();
    }
}


void SET::on_Open_Dir_clicked()
{
    QDesktopServices::openUrl(QUrl("Music",QUrl::TolerantMode));
}


void SET::on_Log_Pushbutton_clicked()
{
    QNetworkAccessManager *Manager = new QNetworkAccessManager();
    QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl("https://api.leafone.cn/api/qq?qq=" + ui->Input_Number->text())));
    QEventLoop EventLoop;
    connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
    EventLoop.exec();

    //解析json
    QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
    QJsonObject Return_Root = Temp.object();

    if(Return_Root.value("msg").toString() == "获取用户信息失败,可能是该QQ不存在" || ui->Input_Number->text().isEmpty())//判断QQ号有无错误
    {
        QMessageBox Temp;
        Temp.setText("QQ不存在,或QQ号输入错误");
        Temp.exec();
    }
    else
    {
        Return_Root = Return_Root.value("data").toObject();
        Json->open(QFile::ReadOnly);
        QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
        Json->close();
        Json->open(QFile::WriteOnly);
        QJsonObject Root = Temp_Json.object();

        QJsonValueRef Logged = Root.find("QQ_Logged").value();
        Logged = QJsonValue(true);

        QJsonValueRef Number = Root.find("QQ_Number").value();
        Number = QJsonValue(ui->Input_Number->text());

        QJsonValueRef Image_Url = Root.find("QQ_Image_Url").value();
        Image_Url = QJsonValue(Return_Root.value("img").toString());

        QJsonValueRef Name = Root.find("QQ_Name").value();
        Name = QJsonValue(Return_Root.value("name").toString());

        Temp_Json.setObject(Root);
        Json->write(QByteArray(Temp_Json.toJson()));
        Json->close();

        //下载Image
        Reply = Manager->get(QNetworkRequest(QUrl(Return_Root.value("img").toString())));
        connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
        EventLoop.exec();

        //保存Image
        QFile Image(".\\Data\\Image.png");
        Image.open(QFile::WriteOnly);
        Image.write(Reply->readAll());
        Image.close();

        QMessageBox::information(0,"提示","登入成功,重新打开设置显示");
        this->close();
    }
}


void SET::on_Exit_Log_clicked()
{
    Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    Json->close();
    Json->open(QFile::WriteOnly);
    QJsonObject Root = Temp_Json.object();

    QJsonValueRef Value = Root.find("QQ_Logged").value();
    Value = QJsonValue(false);

    Temp_Json.setObject(Root);
    Json->write(QByteArray(Temp_Json.toJson()));
    Json->close();

    QMessageBox::information(0,"提示","退出成功,重新打开设置显示");
    this->close();
}


void SET::on_Open_clicked()
{
    Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    Json->close();
    Json->open(QFile::WriteOnly);
    QJsonObject Root = Temp_Json.object();

    QJsonValueRef Value = Root.find("Save_While_Listening").value();
    Value = QJsonValue(true);

    Temp_Json.setObject(Root);
    Json->write(QByteArray(Temp_Json.toJson()));

    Json->close();

    ui->Open_Dir->setVisible(false);

    if(!QDir("./Music").exists())
    {
        QDir Temp_Dir;
        Temp_Dir.mkdir("./Music");
    }

    QMessageBox::information(0,"提示","开启成功,重新打开设置显示开启");

    this->close();
}


void SET::on_Close_clicked()
{
    Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    Json->close();
    Json->open(QFile::WriteOnly);
    QJsonObject Root = Temp_Json.object();

    QJsonValueRef Value = Root.find("Save_While_Listening").value();
    Value = QJsonValue(false);

    Temp_Json.setObject(Root);
    Json->write(QByteArray(Temp_Json.toJson()));

    Json->close();

    ui->Open_Dir->setVisible(true);
    QMessageBox::information(0,"提示","关闭成功,重新打开设置显示关闭");

    this->close();
}


void SET::on_pushButton_clicked()
{
    Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    Json->close();
    Json->open(QFile::WriteOnly);
    QJsonObject Root = Temp_Json.object();

    QJsonValueRef Value = Root.find("Theme_Color").value();
    Value = QJsonValue(ui->R->text() + "," + ui->G->text() + "," + ui->B->text() + "," + "150");

    Temp_Json.setObject(Root);
    Json->write(QByteArray(Temp_Json.toJson()));

    Json->close();

    QMessageBox::information(0,"提示","修改主题颜色后需要重新启动软件");

    this->close();
}

