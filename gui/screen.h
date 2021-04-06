#ifndef SCREEN_H
#define SCREEN_H

#include <QMainWindow>

namespace Ui {
class screen;
}

class screen : public QMainWindow
{
    Q_OBJECT

public:
    explicit screen(QWidget *parent = 0);
    ~screen();

private:
    Ui::screen *ui;
};

#endif // SCREEN_H
