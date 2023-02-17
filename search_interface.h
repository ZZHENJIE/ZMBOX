#ifndef SEARCH_INTERFACE_H
#define SEARCH_INTERFACE_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QAbstractItemView>

namespace Ui {
class Search_Interface;
}

class Search_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Search_Interface(QWidget *parent = nullptr);
    ~Search_Interface();

    void UI_Init(QString Color_Info = "255,255,255,255");

private:
    Ui::Search_Interface *ui;
};

#endif // SEARCH_INTERFACE_H
