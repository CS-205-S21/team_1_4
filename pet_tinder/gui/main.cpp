#include "screen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screen w;
    w.initialize();
    w.showMaximized();
    //w.show();

    return a.exec();
}
