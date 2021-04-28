#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "screen.h"
#include "petlist.h"

namespace Ui {
class petList;
}

class Screen;
class profilePage;

class petList : public QWidget
{
    Q_OBJECT

public:
    explicit petList(QWidget *parent = nullptr);
    ~petList();

    Screen *scrptr;
    profilePage *ppptr;

signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_profileButton_clicked();

private:
    Ui::petList *ui;
};

#endif // PETLIST_H
