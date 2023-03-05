#ifndef FUNCTION_INTERFACE_H
#define FUNCTION_INTERFACE_H

#include "other.h"

namespace Ui {
class Function_Interface;
}

class Function_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Function_Interface(QWidget *parent = nullptr);
    ~Function_Interface();

    void UI_Init(QFont Font,QString Color_Info = "255,255,255,255");

public Q_SLOTS:
    
Q_SIGNALS:

    void Set();

    void Play();

    void Like();

private:
    Ui::Function_Interface *ui;
};

#endif // FUNCTION_INTERFACE_H
