#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "screen.h"

namespace Ui {
class petList;
}

class petList : public QWidget
{
    Q_OBJECT

public:
    explicit petList(QWidget *parent = nullptr);
    ~petList();

signals:

public slots:

private:
    Ui::petList *ui;
};

#endif // PETLIST_H
