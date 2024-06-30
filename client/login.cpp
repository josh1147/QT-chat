#include "login.h"
#include "ui_login.h"
#include "dialog.h"
#include <QMessageBox>
#include <QSqlQuery>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_loginbtn_clicked()
{
    QString user ;
    QString pwd  ;
    user = ui->userline->text();
    pwd  = ui->pwdline->text();
    if(user=="")
        QMessageBox::warning(this,"","用户名不能为空");
    else if(pwd=="")
            QMessageBox::warning(this,"","密码不能为空");
    else{
        //QString S = QString(“select * from user_table where name=’%1’ and password=’%2’”).arg(user).arg(pwd);
        QString S = QString("SELECT * FROM user_table WHERE name='%1' AND password='%2'").arg(user).arg(pwd);
        QSqlQuery query ;
        if(query.exec(S)){
            QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
            present_id = user ;
            accept();
        }
        else
            QMessageBox::warning(this,"error","用户名或者密码错误！！");

        ui->userline->clear();
        ui->pwdline->clear();
        ui->userline->setFocus();
    }
}

void login::on_registerbtn_clicked()
{
    Dialog dlg ;
    dlg.exec();
}
