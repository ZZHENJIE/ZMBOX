#include "mthread.h"

void MThread::run(QString Download_Url,int Platform,QString Music_Name,QString Singer_Name)
{
    switch(Platform)//判断音乐平台
    {
        case 0:
        {
            QNetworkAccessManager *Manager = new QNetworkAccessManager();
            QNetworkReply *Reply = Manager->get(QNetworkRequest(QUrl(Download_Url)));
            QEventLoop EventLoop;
            connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
            EventLoop.exec();

            //解析json
            QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
            QJsonObject Root = Temp.object();
            QJsonValue Value_1 = Root.value("data");
            QJsonObject Value_2 = Value_1.toArray().at(0).toObject();

            if(Value_2.value("url").isNull() == false)//判断音乐神佛可下载
            {
                Reply = Manager->get(QNetworkRequest(QUrl(Value_2.value("url").toString())));
                EventLoop.exec();

                //保存音乐
                QFile Music(".\\Music\\0-" + Music_Name + "-" + Singer_Name + ".mp3");
                Music.open(QFile::WriteOnly);
                Music.write(Reply->readAll());
                Music.close();
            }
            else
            {
                QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到下载问题");
            }
            break;
        }
        case 1:
        {
            QNetworkRequest Url;
            Url.setUrl(QUrl(Download_Url));
            Url.setRawHeader("cookie",QByteArray("kg_mid=1"));
            //获取音乐下载json
            QNetworkAccessManager *Manager = new QNetworkAccessManager();
            QNetworkReply *Reply = Manager->get(Url);
            QEventLoop EventLoop;
            connect(Manager, SIGNAL(finished(QNetworkReply*)), &EventLoop, SLOT(quit()));
            EventLoop.exec();

            //解析json
            QJsonDocument Temp = QJsonDocument::fromJson(Reply->readAll());
            QJsonObject Root = Temp.object();

            if(Root.value("status").toInt() == 1)
            {
                //下载歌曲
                Reply = Manager->get(QNetworkRequest(QUrl(Root.value("data").toObject().value("play_url").toString())));
                EventLoop.exec();

                //保存音乐
                QFile Music(".\\Music\\1-" + Music_Name + "-" + Singer_Name + ".mp3");
                Music.open(QFile::WriteOnly);
                Music.write(Reply->readAll());
                Music.close();
            }
            else
            {
                QMessageBox::information(0,"提示","选择歌曲可能需要VIP或遇到下载问题");
            }
            break;
        }
        case 2:
        {
            break;
        }
    }
    quit();
}