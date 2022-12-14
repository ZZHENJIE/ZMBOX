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
#include <QMessageBox>
#include <QFileInfo>
#include "cloud_music.h"
#include "kugou_music.h"
#include "struct.h"

namespace Ui {
class PLAY;
}

class PLAY : public QWidget
{
    Q_OBJECT

public:
    explicit PLAY(QWidget *parent = nullptr);//构造函数

    ~PLAY();//析构函数
    
    void Set_Theme_Color(QString Color);//设置主题颜色

private slots:
    void GetDuration();//获取歌曲总时长

    void ON_Time_Out();//播放歌曲计时器调用槽函数

    void on_Back_clicked();//上一曲按钮槽函数

    void on_Play_clicked();//播放或暂停按钮槽函数

    void on_Next_clicked();//下一首按钮槽函数

    void on_Audio_clicked();//音量大小按钮槽函数

    void on_Image_clicked();//歌曲图片按钮槽函数

    void on_Music_Pos_sliderReleased();//音乐播放时间进度调整槽函数

    void on_Audio_Size_sliderReleased();//音量大小调整槽函数

    void Play_Number_Update(bool Delete);//播放歌曲序号更新槽函数

    void Play_Number_Init();//播放歌曲序号初始化槽函数

    void Change_Music_Play(int Number);//播放歌曲改变

signals:
    void Clicked_Music_Icon();//点击歌曲图片信号

    void Lyrics_Change(Music_Info Info);//歌词界面改变

private:
    QAudioOutput *Audio_OP = new QAudioOutput();//音乐输出设备

    QMediaPlayer *Music_Media = new QMediaPlayer();//储存音乐信息

    Ui::PLAY *ui;

    QFile *Play_Json = new QFile("./Data/Play.json");//播放列表文件
    
    QJsonArray Play_List;//储存播放列表内歌曲信息

    QTimer *Time = new QTimer();//计时器

    Cloud_Music *Cloud;//网易云音乐类

    KuGou_Music *KuGou;//酷狗音乐类

    MThread *Image;//下载图片线程

    qint64 Muisc_Max_Leng = 0;//音乐时长

    bool Save_While_Listening = false;//是否开启边听边存功能

    int Play_Number = 0;//播放音乐序号

    void Change_Music();//音乐改变函数

    void Preload_Image();//预加载图片函数

    void Music_Info_Pack();//歌曲信息打包
};

#endif // PLAY_INTERFACE_H
