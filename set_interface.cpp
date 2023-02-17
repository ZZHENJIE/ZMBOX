#include "set_interface.h"
#include "ui_set_interface.h"

Set_Interface::Set_Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Set_Interface)
{
    ui->setupUi(this);
    this->move(100,90);
    this->show();

    UI_Init();

    connect(ui->Set_Background_Button,&QPushButton::clicked,this,&Set_Interface::Set_Background);
    connect(ui->Confirm_Color,&QPushButton::clicked,this,&Set_Interface::Set_Theme);
    connect(ui->Repair,&QPushButton::clicked,this,&Set_Interface::Repair);
}

void Set_Interface::Set_Background()
{
    QString Image_Url = QFileDialog::getOpenFileName(nullptr,"选择图片","C://","*.png");

    if(!Image_Url.isEmpty())
    {
        Change_Background(Image_Url);

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

    QJsonDocument Data_Doc;

    Data_Doc.setObject(Data);

    Data_Json.write(Data_Doc.toJson());

    Data_Json.close();
}

void Set_Interface::Set_Theme()
{
    if(ui->R->text().toInt() <= 255 && ui->G->text().toInt() <= 255 && ui->B->text().toInt() <= 255 && ui->A->text().toInt() <= 255)
    {
        Change_Theme(ui->R->text() + "," + ui->G->text() + "," + ui->B->text() + "," + ui->A->text());

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

void Set_Interface::UI_Init(QString Color_Info)
{
    ui->Set_Background_Button->setToolTip("选择背景图片");
    ui->Confirm_Color->setToolTip("应用颜色");
    ui->Repair->setToolTip("修复应用");

    ui->Set_Background_Button->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Confirm_Color->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->Repair->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->R->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->G->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->B->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
    ui->A->setStyleSheet("background-color: rgba(" + Color_Info + ");border-radius: 5px;");
}

Set_Interface::~Set_Interface()
{
    delete ui;
}
