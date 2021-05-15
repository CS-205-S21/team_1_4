#ifndef ADDACCOUNT_H
#define ADDACCOUNT_H

#include <QWidget>
#include <string>
#include "petfinder.h"

namespace Ui {
class AddAccount;
}
class PetFinder;
class AddAccount : public QWidget
{
    Q_OBJECT

public:
    explicit AddAccount(QWidget *parent = 0);
    ~AddAccount();
    PetFinder *PfPnter;
    QString username;
    QString password;
    QString confirmPassword;
    int role;

private slots:
    void on_cancelbutton_clicked();
    void on_saveNewAccount_clicked();
    bool validate();
    void on_newUsernameInput_textChanged(const QString &arg1);

    void on_newPasswordInput_textChanged(const QString &arg1);

    void on_newConfirmPasswordInput_textChanged(const QString &arg1);

    void on_roleChooser_currentIndexChanged(int index);

private:
    Ui::AddAccount *ui;
};

#endif // ADDACCOUNT_H
