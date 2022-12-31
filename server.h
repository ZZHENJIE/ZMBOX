#ifndef SERVER_H
#define SERVER_H

#define SERVER_IP      "47.113.221.13"      //服务器IP地址
#define SERVER_PORT    2005           //服务器端口号

#include <QObject>
#include <QMessageBox>
#include <QByteArray>
#include <QTcpSocket>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class SERVER : public QObject
{
    Q_OBJECT
public:
    SERVER();//构造函数

    ~SERVER();//析构函数
    
    QByteArray Data;//储存服务器发送数据

    QString User_Name;//用户名

    void Client_Send(QString Message_Data);//客户端发送信息
private:
    QTcpSocket *Server = new QTcpSocket();//服务器套接字
private slots:
    void Server_Send();//服务器发送信息槽函数
signals:
    void Server_Send_Signals();//服务器发送信息信号
}; 

#endif // SERVER_H
