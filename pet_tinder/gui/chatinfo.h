#ifndef CHATINFO_H
#define CHATINFO_H

#include <QWidget>
#include "petlist.h"

namespace Ui {
class ChatInfo;
}

class PetList;

class ChatInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ChatInfo(QWidget *parent = 0);
    ~ChatInfo();

    PetList* petListWindow;

    void display(bool isPet);

private slots:
    void on_backButton_clicked();

private:
    Ui::ChatInfo *ui;
};

#endif // CHATINFO_H
