#ifndef SET_INTERFACE_H
#define SET_INTERFACE_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtWidgets/QMessageBox>
#include <QDesktopServices>
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

    void UI_Init(QString Color_Info = "255,255,255,255");

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

private:
    Ui::Set_Interface *ui;
};

#endif // SET_INTERFACE_H
