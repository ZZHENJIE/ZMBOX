#ifndef SEARCH_INTERFACE_H
#define SEARCH_INTERFACE_H


#include "other.h"

namespace Ui {
class Search_Interface;
}

class Search_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Search_Interface(QWidget *parent = nullptr);
    ~Search_Interface();

    void UI_Init(QFont Font,QString Color_Info = "255,255,255,255");

public Q_SLOTS:


Q_SIGNALS:

    void Search(QString KeyWord,int MusicPlatform);

    void Back();

private:
    Ui::Search_Interface *ui;
};

#endif // SEARCH_INTERFACE_H
