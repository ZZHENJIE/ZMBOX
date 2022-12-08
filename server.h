#ifndef SERVER_H
#define SERVER_H

#define SERVER_IP      "1.1.1.1"      //服务器IP地址
#define SERVER_PORT    0000           //服务器端口号

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
        SERVER();
        ~SERVER();
        QByteArray Data;
        void Client_Send(QString Message_Data);
    private:
        QString User_Name;
        QTcpSocket *Server;
    private slots:
        void Server_Send();
    signals:
        void Server_Send_Signals();
}; 

#endif // SERVER_H
