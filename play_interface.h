#ifndef PLAY_INTERFACE_H
#define PLAY_INTERFACE_H

#include <QWidget>

namespace Ui {
class PLAY_INTERFACE;
}

class PLAY_INTERFACE : public QWidget
{
    Q_OBJECT

public:
    explicit PLAY_INTERFACE(QWidget *parent = nullptr);
    ~PLAY_INTERFACE();
    void Set_Theme_Color(QString Color);

private slots:
    void on_Back_clicked();

    void on_Play_clicked();

    void on_Next_clicked();

    void on_Audio_clicked();

    void on_Image_clicked();

private:
    Ui::PLAY_INTERFACE *ui;
};

#endif // PLAY_INTERFACE_H
