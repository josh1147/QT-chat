#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    QString present_id;
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_loginbtn_clicked();

    void on_registerbtn_clicked();

private:
    Ui::login *ui;


};

#endif // LOGIN_H
