#include "server.h"

SERVER::SERVER()//构造函数
{
    Server = new QTcpSocket();

    Server->connectToHost(SERVER_IP,SERVER_PORT);//连接服务器

    if(Server->waitForConnected() == false)//查看是否连接成功
    {
        QMessageBox::information(0,"提示","连接聊天室服务器失败!!!");
    }

    connect(Server,SIGNAL(readyRead()),this,SLOT(Server_Send()));//服务器发送数据信号 服务器发送信息槽函数
}


SERVER::~SERVER()//析构函数
{
    Server->close();//关闭与服务器连接
    delete Server;
}

void SERVER::Client_Send(QString Message_Data)//客户端发送信息
{
    QString Message = User_Name + " : " + Message_Data;//拼接发送信息
    Server->write(Message.toUtf8());//发送信息给服务器
}

void SERVER::Server_Send()//服务器发送信息槽函数
{
    Data = Server->readAll();//储存服务器发送信息
    Server_Send_Signals();
}