#ifndef MLISTWIDGETITEM_H
#define MLISTWIDGETITEM_H

#include "other.h"
#include "netmusic.h"
#include "spotifymusic.h"

class MListWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit MListWidgetItem(QWidget *parent = nullptr);

    ~MListWidgetItem();

    void Search(Song_Info Data);

    void Play_Like_List(Song_Info Data,short SerialNumber);

    void Song_List(Song_List_Info Data);

public Q_SLOTS:

    void Clear_Item();

Q_SIGNALS:

    void Play_Select_Song(short SerialNumber);

    void Delete_Song(short SerialNumber);

    void Add_Play(Song_Info Data);

    void Add_Like(Song_Info Data);

private:
    QPushButton * Button_1;
    QPushButton * Button_2;
    QPushButton * Button_3;
    QLabel * Text;

    short List_SerialNumber = 0;

    Song_Info Info;
    
    Song_List_Info List_Info;
};

#endif // MLISTWIDGETITEM_H
