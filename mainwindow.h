#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "other.h"
#include "function_interface.h"
#include "player_interface.h"
#include "search_interface.h"
#include "set_interface.h"
#include "list_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UI_Init();

public Q_SLOTS:

    void Change_Background(QString Image_Url);

    void Change_Theme(QString Color_Info);

    void Search(QString KeyWord,int MusicPlatform);

Q_SIGNALS:

private:
    Ui::MainWindow *ui;

    QProcess * Net_Music;
    QProcess * Spotify_KuGou;

    QFont * Font;

    Function_Interface *FunctionInterface;
    Player_Interface *PlayerInterface;
    Search_Interface *SearchInterface;
    Set_Interface *SetInterface;
    List_Interface *ListInterface;
};
#endif // MAINWINDOW_H
