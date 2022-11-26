#ifndef PLAY_INTERFACE_H
#define PLAY_INTERFACE_H

#include <QWidget>

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

private:
    Ui::PLAY_INTERFACE *ui;
};

#endif // PLAY_INTERFACE_H
