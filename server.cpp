#include "server.h"

SERVER::SERVER()
{
    Server = new QTcpSocket();

    Server->connectToHost(SERVER_IP,SERVER_PORT);

    if(Server->waitForConnected() == false)
    {
        QMessageBox::information(0,"提示","连接聊天室服务器失败!!!");
    }

    connect(Server,SIGNAL(readyRead()),this,SLOT(Server_Send()));


    QFile *Json = new QFile("./Data/Data.json");
    Json->open(QFile::ReadOnly);
    QJsonDocument Temp_Json = QJsonDocument::fromJson(QByteArray(Json->readAll()));
    Json->close();
    User_Name = Temp_Json.object().value("QQ_Name").toString();
}


SERVER::~SERVER()
{
    Server->close();
    delete Server;
}

void SERVER::Server_Send()
{
    Data = Server->readAll();
    Server_Send_Signals();
}


void SERVER::Client_Send(QString Message_Data)
{
    QString Message = User_Name + " : " + Message_Data;
    Server->write(Message.toUtf8());
}
