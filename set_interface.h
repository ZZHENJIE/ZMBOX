#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H

#include <QtWidgets/QWidget>

namespace Ui {
class Set_Interface;
}

class Set_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Set_Interface(QWidget *parent = nullptr);
    ~Set_Interface();

    void UI_Init();

public Q_SLOTS:

Q_SIGNALS:

    void Change_Background();

private:
    Ui::Set_Interface *ui;
};

#endif // SET_INTERFACE_H
