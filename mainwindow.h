#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include "function_interface.h"
#include "player_interface.h"
#include "search_interface.h"
#include "set_interface.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UI_Init();

public Q_SLOTS:

    void Change_Background(QString Image_Url);

    void Change_Theme(QString Color_Info);

Q_SIGNALS:

private:
    Ui::MainWindow *ui;
    Function_Interface *FunctionInterface;
    Player_Interface *PlayerInterface;
    Search_Interface *SearchInterface;
    Set_Interface *SetInterface;
};
#endif // MAINWINDOW_H
