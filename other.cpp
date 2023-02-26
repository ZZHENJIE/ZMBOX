#include "other.h"

QByteArray Other::GetUrlData(QString Url)
{
    QEventLoop Loop;

    QNetworkAccessManager Manager;

    QNetworkReply *Reply = Manager.get(QNetworkRequest(QUrl(Url)));

    connect(&Manager,&QNetworkAccessManager::finished,&Loop,&QEventLoop::quit);

    Loop.exec();

    return Reply->readAll();
}

QPixmap Other::UrlToPixmap(QString Url)
{
    QPixmap Ret;

    Ret.loadFromData(Other::GetUrlData(Url));

    return Ret;
}
