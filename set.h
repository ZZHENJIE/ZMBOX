#ifndef SET_H
#define SET_H

#include <QMainWindow>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QFile>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QPixmap>
#include <QMessageBox>
#include <QDir>
#include <QDesktopServices>
#include <QJsonValueRef>
#include <QFileDialog>

namespace Ui {
class Set;
}

class SET : public QMainWindow
{
    Q_OBJECT

public:
    explicit SET(QWidget *parent = nullptr);
    ~SET();

private slots:
    void on_Select_Background_clicked();

    void on_Open_Dir_clicked();

    void on_Log_Pushbutton_clicked();

    void on_Exit_Log_clicked();

    void on_Open_clicked();

    void on_Close_clicked();

    void on_pushButton_clicked();

private:
    QFile* Json = new QFile("./Data/Data.json");
    Ui::Set *ui;
};

#endif // SET_H
