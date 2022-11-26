#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "set.h"
#include "play_interface.h"
#include "search.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Set_clicked();

private:
    Ui::MainWindow *ui;
    SEARCH *Search;
    PLAY_INTERFACE *Play_Interface;
    SET *Set;
    void Set_Theme_Color(QString Color);
};
#endif // MAINWINDOW_H
