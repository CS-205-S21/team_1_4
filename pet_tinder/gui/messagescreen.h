#ifndef MESSAGESCREEN_H
#define MESSAGESCREEN_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"
#include "messagescreen.h"

namespace Ui {
class MessageScreen;
}

class PetFinder;
class PetList;

class MessageScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MessageScreen(QWidget *parent = nullptr);
    ~MessageScreen();

    PetList *plptr;

signals:

public slots:

private slots:

    void on_backButton_clicked();

private:
    Ui::MessageScreen *ui;
};

#endif // MESSAGESCREEN_H


