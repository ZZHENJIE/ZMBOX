#ifndef PLAY_INTERFACE_H
#define PLAY_INTERFACE_H

#include <QWidget>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QAudioOutput>
#include <QMediaPlayer>
#include <QTimer>
#include <QtCore/QObject>
#include "mthread.h"

namespace Ui {
class PLAY_INTERFACE;
}

class PLAY_INTERFACE : public QWidget
{
    Q_OBJECT

public:
    explicit PLAY_INTERFACE(QWidget *parent = nullptr);
    ~PLAY_INTERFACE();
    void Set_Theme_Color(QString Color);
    void Play_State(int State);

private slots:
    void GetDuration();

    void ON_Time_Out();

    void on_Back_clicked();

    void on_Play_clicked();

    void on_Next_clicked();

    void on_Audio_clicked();

    void on_Image_clicked();

private:
    QAudioOutput Audio_OP;
    QMediaPlayer Music_Media;

    Ui::PLAY_INTERFACE *ui;
    MThread *Download = new MThread();
    QFile *Play_Json = new QFile("./Data/Play.json");
    bool Save_While_Listening = false;

    QJsonArray Play_List;
    QTimer Time;
    int Play_Number = 0;
    qint64 Muisc_Max_Leng = 0;

    void Change_Music();
};

#endif // PLAY_INTERFACE_H