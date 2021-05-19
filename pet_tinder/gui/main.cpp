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
    cout << w.petWindow->petIndex << endl;
    /*while(true) {
        cout << "test" << endl;
        HomeScreen s;
        if(w.petWindow->loggingOut || s.petWindow->loggingOut) {
            s.show();
        } else {
            break;
        }
    }*/

    return a.exec();
}
