#include "petfinder.h"
#include "homescreen.h"
#include <QApplication>
#include "adopteeaddpet.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeScreen w;
    //w.initialize();
    //w.showMaximized();
    w.show();

    return a.exec();
}
