/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *Main;
    QLabel *Background;
    QWidget *Pushbutton;
    QPushButton *Room;
    QPushButton *Set;
    QPushButton *Like;
    QPushButton *List;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1280, 720);
        MainWindow->setMinimumSize(QSize(1280, 720));
        MainWindow->setMaximumSize(QSize(1280, 720));
        Main = new QWidget(MainWindow);
        Main->setObjectName(QString::fromUtf8("Main"));
        Main->setMinimumSize(QSize(1280, 720));
        Main->setMaximumSize(QSize(1280, 720));
        Background = new QLabel(Main);
        Background->setObjectName(QString::fromUtf8("Background"));
        Background->setGeometry(QRect(0, 0, 1280, 720));
        Background->setMinimumSize(QSize(1280, 720));
        Background->setMaximumSize(QSize(1280, 720));
        Background->setPixmap(QPixmap(QString::fromUtf8(":/Resource/Background.png")));
        Background->setScaledContents(true);
        Pushbutton = new QWidget(Main);
        Pushbutton->setObjectName(QString::fromUtf8("Pushbutton"));
        Pushbutton->setGeometry(QRect(0, 0, 100, 100));
        Room = new QPushButton(Pushbutton);
        Room->setObjectName(QString::fromUtf8("Room"));
        Room->setGeometry(QRect(0, 0, 50, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resource/Chat_Room.png"), QSize(), QIcon::Normal, QIcon::Off);
        Room->setIcon(icon);
        Room->setIconSize(QSize(45, 45));
        Room->setFlat(true);
        Set = new QPushButton(Pushbutton);
        Set->setObjectName(QString::fromUtf8("Set"));
        Set->setGeometry(QRect(50, 0, 50, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resource/Set.png"), QSize(), QIcon::Normal, QIcon::Off);
        Set->setIcon(icon1);
        Set->setIconSize(QSize(45, 45));
        Set->setFlat(true);
        Like = new QPushButton(Pushbutton);
        Like->setObjectName(QString::fromUtf8("Like"));
        Like->setGeometry(QRect(0, 50, 50, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resource/Like.png"), QSize(), QIcon::Normal, QIcon::Off);
        Like->setIcon(icon2);
        Like->setIconSize(QSize(45, 45));
        Like->setFlat(true);
        List = new QPushButton(Pushbutton);
        List->setObjectName(QString::fromUtf8("List"));
        List->setGeometry(QRect(50, 50, 50, 50));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Resource/Play_List.png"), QSize(), QIcon::Normal, QIcon::Off);
        List->setIcon(icon3);
        List->setIconSize(QSize(45, 45));
        List->setFlat(true);
        line = new QFrame(Main);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 600, 1280, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(Main);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(100, 0, 1, 600));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(Main);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Background->setText(QString());
        Room->setText(QString());
        Set->setText(QString());
        Like->setText(QString());
        List->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
