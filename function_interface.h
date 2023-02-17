#ifndef FUNCTION_INTERFACE_H
#define FUNCTION_INTERFACE_H

#include <QtWidgets/QWidget>

namespace Ui {
class Function_Interface;
}

class Function_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Function_Interface(QWidget *parent = nullptr);
    ~Function_Interface();

    void UI_Init(QString Color_Info = "255,255,255,255");

private:
    Ui::Function_Interface *ui;
};

#endif // FUNCTION_INTERFACE_H
