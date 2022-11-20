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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *Main;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *Title_Button;
    QPushButton *Room;
    QPushButton *Set;
    QLabel *Background;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        MainWindow->setMaximumSize(QSize(1000, 600));
        Main = new QWidget(MainWindow);
        Main->setObjectName(QString::fromUtf8("Main"));
        Main->setMaximumSize(QSize(1000, 600));
        horizontalLayoutWidget = new QWidget(Main);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 122, 53));
        Title_Button = new QHBoxLayout(horizontalLayoutWidget);
        Title_Button->setObjectName(QString::fromUtf8("Title_Button"));
        Title_Button->setContentsMargins(0, 0, 0, 0);
        Room = new QPushButton(horizontalLayoutWidget);
        Room->setObjectName(QString::fromUtf8("Room"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resource/Chat_Room.png"), QSize(), QIcon::Normal, QIcon::Off);
        Room->setIcon(icon);
        Room->setIconSize(QSize(45, 45));
        Room->setFlat(true);

        Title_Button->addWidget(Room);

        Set = new QPushButton(horizontalLayoutWidget);
        Set->setObjectName(QString::fromUtf8("Set"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resource/Set.png"), QSize(), QIcon::Normal, QIcon::Off);
        Set->setIcon(icon1);
        Set->setIconSize(QSize(45, 45));
        Set->setFlat(true);

        Title_Button->addWidget(Set);

        Background = new QLabel(Main);
        Background->setObjectName(QString::fromUtf8("Background"));
        Background->setGeometry(QRect(0, 0, 1000, 600));
        Background->setPixmap(QPixmap(QString::fromUtf8(":/Resource/Background.png")));
        MainWindow->setCentralWidget(Main);
        Background->raise();
        horizontalLayoutWidget->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Room->setText(QString());
        Set->setText(QString());
        Background->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
