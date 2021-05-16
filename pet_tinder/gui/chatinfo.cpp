#include "chatinfo.h"
#include "ui_chatinfo.h"

ChatInfo::ChatInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatInfo)
{
    ui->setupUi(this);
}

ChatInfo::~ChatInfo()
{
    delete ui;
}
