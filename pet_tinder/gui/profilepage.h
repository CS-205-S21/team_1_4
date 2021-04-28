#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include "screen.h"

namespace Ui {
class profilePage;
}

class profilePage : public QWidget
{
    Q_OBJECT

public:
    explicit profilePage(QWidget *parent = 0);
    ~profilePage();

signals:

public slots:

private:
    Ui::profilePage *ui;
};

#endif // PROFILEPAGE_H
