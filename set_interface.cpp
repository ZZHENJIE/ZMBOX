#include "set_interface.h"
#include "ui_set_interface.h"

Set_Interface::Set_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_Interface)
{
    ui->setupUi(this);
    this->move(100,90);
    this->show();

    connect(ui->Set_Background_Button,&QPushButton::clicked,this,&Set_Interface::Set_Background);
    connect(ui->Confirm_Color,&QPushButton::clicked,this,&Set_Interface::Set_Theme);
    connect(ui->Repair,&QPushButton::clicked,this,&Set_Interface::Repair);
    connect(ui->Net_Log_In,&QPushButton::clicked,this,&Set_Interface::Net_Log_In);
    connect(ui->Net_Log_Out,&QPushButton::clicked,this,&Set_Interface::Net_Log_Out);
    connect(ui->Updata_Info,&QPushButton::clicked,this,&Set_Interface::Updata_Info);
}

void Set_Interface::Net_Log_In()
{
    QDesktopServices::openUrl(QUrl("http://127.0.0.1:8385/qrlogin.html"));
    if(QMessageBox::question(0,"提示","是否登入成功!",QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes)
    {
        emit ReBoot_Nodejs();
    }
}

void Set_Interface::Net_Log_Out()
{
    Other::GetUrlData("http://127.0.0.1:8385/logout");
    ui->Net_Name->setText("未登入");
    ui->Net_Image->setPixmap(QPixmap(":/Resource/Cloud.png"));
    emit ReBoot_Nodejs();
}

void Set_Interface::Updata_Info()
{
    QJsonDocument Json_Doc = QJsonDocument::fromJson(Other::GetUrlData("http://127.0.0.1:8385/login/status"));

    QJsonObject Root = Json_Doc.object();

    Root = Root.value("data").toObject();

    if(Root.value("profile").isNull() == false)
    {
        Root = Root.value("profile").toObject();

        ui->Net_Image->setPixmap(Other::UrlToPixmap(Root.value("avatarUrl").toString()));

        ui->Net_Name->setText(Root.value("nickname").toString());

        QFile Data_Json(".//Data//Set.json");

        Data_Json.open(QFile::ReadOnly);

        QJsonDocument Data_Doc = QJsonDocument::fromJson(Data_Json.readAll());

        Data_Json.close();

        Data_Json.open(QFile::WriteOnly);

        QJsonObject Data = Data_Doc.object();

        QJsonValueRef Ref = Data.find("Net_Music_User_Id").value();

        Ref = QJsonValue(QString::number(Root.value("userId").toInt()));

        Data_Doc.setObject(Data);

        Data_Json.write(Data_Doc.toJson());

        Data_Json.close();
    }
    else
    {
        emit ReBoot_Nodejs();
        QMessageBox::information(0,"提示","获取用户数据失败!");
    }
}

void Set_Interface::Set_Background()
{
    QString Image_Url = QFileDialog::getOpenFileName(nullptr,"选择图片","C://","*.png");

    if(!Image_Url.isEmpty())
    {
        emit Change_Background(Image_Url);

        QFile Data_Json(".//Data//Set.json");

        Data_Json.open(QFile::ReadOnly);

        QJsonDocument Data_Doc = QJsonDocument::fromJson(Data_Json.readAll());

        Data_Json.close();

        Data_Json.open(QFile::WriteOnly);

        QJsonObject Data = Data_Doc.object();

        QJsonValueRef Ref = Data.find("Background").value();

        Ref = QJsonValue(Image_Url);

        Data_Doc.setObject(Data);

        Data_Json.write(Data_Doc.toJson());

        Data_Json.close();
    }
}

void Set_Interface::Repair()
{
    QDir Dir;
    Dir.mkdir(".//Data");

    QFile Data_Json(".//Data//Set.json");
    Data_Json.open(QFile::WriteOnly);

    QJsonObject Data;

    Data.insert("Background",":/Resource/Background.png");
    Data.insert("Theme","200,200,200,200");
    Data.insert("Net_Music_User_Id","null");

    QJsonDocument Data_Doc;

    Data_Doc.setObject(Data);

    Data_Json.write(Data_Doc.toJson());

    Data_Json.close();

    Data_Json.setFileName(".//Data//Play.json");
    Data_Json.open(QFile::WriteOnly);
    Data_Json.close();

    Data_Json.setFileName(".//Data//Play.json");
    Data_Json.open(QFile::WriteOnly);
    Data_Json.close();
}

void Set_Interface::Set_Theme()
{
    if(ui->R->text().toInt() <= 255 && ui->G->text().toInt() <= 255 && ui->B->text().toInt() <= 255 && ui->A->text().toInt() <= 255)
    {
        emit Change_Theme(ui->R->text() + "," + ui->G->text() + "," + ui->B->text() + "," + ui->A->text());

        QFile Data_Json(".//Data//Set.json");

        Data_Json.open(QFile::ReadOnly);

        QJsonDocument Data_Doc = QJsonDocument::fromJson(Data_Json.readAll());

        Data_Json.close();

        Data_Json.open(QFile::WriteOnly);

        QJsonObject Data = Data_Doc.object();

        QJsonValueRef Ref = Data.find("Theme").value();

        Ref = QJsonValue(ui->R->text() + "," + ui->G->text() + "," + ui->B->text() + "," + ui->A->text());

        Data_Doc.setObject(Data);

        Data_Json.write(Data_Doc.toJson());

        Data_Json.close();
    }
    else
    {
        QMessageBox::information(0,"提示","数值错误");
    }
}

void Set_Interface::UI_Init(QFont Font,QString Color_Info)
{
    ui->Set_Background_Button->setToolTip("选择背景图片");
    ui->Confirm_Color->setToolTip("应用颜色");
    ui->Repair->setToolTip("修复应用");
    ui->Net_Log_In->setToolTip("网易云音乐登入");
    ui->Net_Log_Out->setToolTip("网易云音乐退出");
    ui->Updata_Info->setToolTip("刷新登入信息");

    ui->Set_Background_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Net_Log_In->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Updata_Info->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Net_Log_Out->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Confirm_Color->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Repair->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->R->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->G->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->B->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->A->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");

    ui->Set_Background_Text->setFont(Font);
    ui->Repair->setFont(Font);
    ui->Set_Background_Button->setFont(Font);
    ui->Set_Background_Text_2->setFont(Font);
    ui->R->setFont(Font);
    ui->G->setFont(Font);
    ui->B->setFont(Font);
    ui->A->setFont(Font);
    ui->Confirm_Color->setFont(Font);
    ui->Log_In_Text->setFont(Font);
    ui->Updata_Info->setFont(Font);
    ui->Net_Name->setFont(Font);
    ui->Net_Log_In->setFont(Font);
    ui->Net_Log_Out->setFont(Font);
}

Set_Interface::~Set_Interface()
{
    delete ui;
}
