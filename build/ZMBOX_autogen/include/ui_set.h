/********************************************************************************
** Form generated from reading UI file 'set.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SET_H
#define UI_SET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Set
{
public:
    QWidget *Main;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *SetBackground;
    QLabel *SetBackgroundText;
    QPushButton *Select_Background;
    QLabel *Background_Image;
    QFrame *line_1;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *Save_While_Listening;
    QLabel *Save_While_Listening_Text;
    QRadioButton *Open;
    QRadioButton *Close;
    QPushButton *Open_Dir;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *QQ_Text;
    QWidget *Log;
    QLabel *Image;
    QLabel *Name;
    QPushButton *Exit_Log;
    QWidget *Not_Log;
    QPushButton *Log_Pushbutton;
    QLineEdit *Input_Number;

    void setupUi(QMainWindow *Set)
    {
        if (Set->objectName().isEmpty())
            Set->setObjectName(QString::fromUtf8("Set"));
        Set->resize(400, 500);
        Main = new QWidget(Set);
        Main->setObjectName(QString::fromUtf8("Main"));
        horizontalLayoutWidget = new QWidget(Main);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 401, 51));
        SetBackground = new QHBoxLayout(horizontalLayoutWidget);
        SetBackground->setObjectName(QString::fromUtf8("SetBackground"));
        SetBackground->setContentsMargins(0, 0, 5, 0);
        SetBackgroundText = new QLabel(horizontalLayoutWidget);
        SetBackgroundText->setObjectName(QString::fromUtf8("SetBackgroundText"));
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(14);
        SetBackgroundText->setFont(font);
        SetBackgroundText->setAlignment(Qt::AlignCenter);

        SetBackground->addWidget(SetBackgroundText);

        Select_Background = new QPushButton(horizontalLayoutWidget);
        Select_Background->setObjectName(QString::fromUtf8("Select_Background"));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font1.setPointSize(10);
        Select_Background->setFont(font1);
        Select_Background->setFlat(false);

        SetBackground->addWidget(Select_Background);

        Background_Image = new QLabel(horizontalLayoutWidget);
        Background_Image->setObjectName(QString::fromUtf8("Background_Image"));
        Background_Image->setMaximumSize(QSize(80, 45));

        SetBackground->addWidget(Background_Image);

        line_1 = new QFrame(Main);
        line_1->setObjectName(QString::fromUtf8("line_1"));
        line_1->setGeometry(QRect(0, 50, 400, 15));
        line_1->setFrameShape(QFrame::HLine);
        line_1->setFrameShadow(QFrame::Sunken);
        horizontalLayoutWidget_2 = new QWidget(Main);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 60, 401, 41));
        Save_While_Listening = new QHBoxLayout(horizontalLayoutWidget_2);
        Save_While_Listening->setObjectName(QString::fromUtf8("Save_While_Listening"));
        Save_While_Listening->setContentsMargins(0, 0, 5, 0);
        Save_While_Listening_Text = new QLabel(horizontalLayoutWidget_2);
        Save_While_Listening_Text->setObjectName(QString::fromUtf8("Save_While_Listening_Text"));
        Save_While_Listening_Text->setFont(font);
        Save_While_Listening_Text->setAlignment(Qt::AlignCenter);

        Save_While_Listening->addWidget(Save_While_Listening_Text);

        Open = new QRadioButton(horizontalLayoutWidget_2);
        Open->setObjectName(QString::fromUtf8("Open"));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font2.setPointSize(12);
        Open->setFont(font2);

        Save_While_Listening->addWidget(Open);

        Close = new QRadioButton(horizontalLayoutWidget_2);
        Close->setObjectName(QString::fromUtf8("Close"));
        Close->setFont(font2);

        Save_While_Listening->addWidget(Close);

        Open_Dir = new QPushButton(horizontalLayoutWidget_2);
        Open_Dir->setObjectName(QString::fromUtf8("Open_Dir"));
        Open_Dir->setFont(font1);
        Open_Dir->setFlat(false);

        Save_While_Listening->addWidget(Open_Dir);

        line_2 = new QFrame(Main);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 100, 400, 15));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(Main);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 350, 400, 15));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        QQ_Text = new QLabel(Main);
        QQ_Text->setObjectName(QString::fromUtf8("QQ_Text"));
        QQ_Text->setGeometry(QRect(0, 110, 400, 50));
        QQ_Text->setFont(font2);
        QQ_Text->setAlignment(Qt::AlignCenter);
        Log = new QWidget(Main);
        Log->setObjectName(QString::fromUtf8("Log"));
        Log->setGeometry(QRect(0, 160, 400, 190));
        Image = new QLabel(Log);
        Image->setObjectName(QString::fromUtf8("Image"));
        Image->setGeometry(QRect(20, 10, 150, 150));
        Image->setMinimumSize(QSize(150, 150));
        Image->setMaximumSize(QSize(150, 150));
        Name = new QLabel(Log);
        Name->setObjectName(QString::fromUtf8("Name"));
        Name->setGeometry(QRect(200, 10, 150, 150));
        Name->setMinimumSize(QSize(150, 150));
        Name->setMaximumSize(QSize(150, 150));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(20);
        Name->setFont(font3);
        Name->setAlignment(Qt::AlignCenter);
        Exit_Log = new QPushButton(Log);
        Exit_Log->setObjectName(QString::fromUtf8("Exit_Log"));
        Exit_Log->setGeometry(QRect(200, 160, 150, 30));
        Exit_Log->setMaximumSize(QSize(150, 30));
        Exit_Log->setFont(font3);
        Not_Log = new QWidget(Main);
        Not_Log->setObjectName(QString::fromUtf8("Not_Log"));
        Not_Log->setGeometry(QRect(0, 160, 400, 190));
        Log_Pushbutton = new QPushButton(Not_Log);
        Log_Pushbutton->setObjectName(QString::fromUtf8("Log_Pushbutton"));
        Log_Pushbutton->setGeometry(QRect(0, 130, 400, 35));
        Log_Pushbutton->setFont(font3);
        Input_Number = new QLineEdit(Not_Log);
        Input_Number->setObjectName(QString::fromUtf8("Input_Number"));
        Input_Number->setGeometry(QRect(0, 40, 400, 40));
        Input_Number->setFont(font3);
        Input_Number->setMaxLength(20);
        Set->setCentralWidget(Main);

        retranslateUi(Set);

        QMetaObject::connectSlotsByName(Set);
    } // setupUi

    void retranslateUi(QMainWindow *Set)
    {
        Set->setWindowTitle(QCoreApplication::translate("Set", "MainWindow", nullptr));
        SetBackgroundText->setText(QCoreApplication::translate("Set", "\350\256\276\347\275\256\350\203\214\346\231\257\345\233\276\347\211\207", nullptr));
        Select_Background->setText(QCoreApplication::translate("Set", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        Background_Image->setText(QString());
        Save_While_Listening_Text->setText(QCoreApplication::translate("Set", "\350\276\271\345\220\254\350\276\271\345\255\230", nullptr));
        Open->setText(QCoreApplication::translate("Set", "\345\274\200\345\220\257", nullptr));
        Close->setText(QCoreApplication::translate("Set", "\345\205\263\351\227\255", nullptr));
        Open_Dir->setText(QCoreApplication::translate("Set", "\346\211\223\345\274\200\350\265\204\346\272\220\347\256\241\347\220\206\345\231\250", nullptr));
        QQ_Text->setText(QCoreApplication::translate("Set", "\346\234\254\347\231\273\345\205\245\345\217\252\344\270\272\344\274\252\347\231\273\345\205\245,\345\217\252\344\274\232\350\216\267\345\217\226\345\244\264\345\203\217\345\215\263\345\220\215\347\247\260,\344\270\215\344\274\232\346\263\204\346\274\217QQ\345\217\267", nullptr));
        Image->setText(QString());
        Name->setText(QString());
        Exit_Log->setText(QCoreApplication::translate("Set", "\351\200\200\345\207\272", nullptr));
        Log_Pushbutton->setText(QCoreApplication::translate("Set", "\347\231\273\345\205\245", nullptr));
        Input_Number->setPlaceholderText(QCoreApplication::translate("Set", "\350\257\267\350\276\223\345\205\245QQ\345\217\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Set: public Ui_Set {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_H
