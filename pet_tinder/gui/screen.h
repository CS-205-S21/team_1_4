#ifndef SCREEN_H
#define SCREEN_H

#include "homescreen.h"
#include <QMainWindow>

namespace Ui {
class Screen;
}

class Screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit Screen(QWidget *parent = 0);
    ~Screen();
    void initialize();

private slots:

private:
    Ui::Screen *ui;
};

#endif // SCREEN_H
