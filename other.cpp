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

QString Other::MsToSec(qint64 Ms)
{
    short Min = Ms/60000;

    short Ten_Sec = (Ms - Min * 60000) / 10000;

    short Sec = (Ms - (Min * 60000 + Ten_Sec * 10000)) / 1000;

    return QString::number(Min) + ":" + QString::number(Ten_Sec) + QString::number(Sec);
}