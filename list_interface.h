#ifndef LIST_INTERFACE_H
#define LIST_INTERFACE_H

#include "netmusic.h"
#include "spotifymusic.h"
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class List_Interface;
}

class List_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit List_Interface(QWidget *parent = nullptr);
    ~List_Interface();

    void UI_Init(QString Color_Info = "255,255,255,255");

public Q_SLOTS:

    void Search(QString KeyWord,int MusicPlatform);

    void GetTheRecommendedPlaylist(int MusicPlatform);

private:
    Ui::List_Interface *ui;
};

#endif // LIST_INTERFACE_H
