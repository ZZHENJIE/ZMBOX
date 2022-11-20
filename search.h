#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>

namespace Ui {
class SEARCH;
}

class SEARCH : public QWidget
{
    Q_OBJECT

public:
    explicit SEARCH(QWidget *parent = nullptr);
    ~SEARCH();

private slots:
    void on_PushButton_clicked();

private:
    Ui::SEARCH *ui;
};

#endif // SEARCH_H
