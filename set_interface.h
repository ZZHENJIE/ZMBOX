#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H

#include "other.h"

namespace Ui {
class Set_Interface;
}

class Set_Interface : public QWidget
{
    Q_OBJECT

public:
    explicit Set_Interface(QWidget *parent = nullptr);
    ~Set_Interface();

    void UI_Init(QFont Font,QString Color_Info = "255,255,255,255");

public Q_SLOTS:

    void Set_Background();

    void Set_Theme();

    void Repair();

    void Net_Log_In();

    void Net_Log_Out();

    void Updata_Info();

Q_SIGNALS:

    void Change_Theme(QString Color_Info);

    void Change_Background(QString Image_Url);

    void ReBoot_Nodejs();

private:
    Ui::Set_Interface *ui;
};

#endif // SET_INTERFACE_H
