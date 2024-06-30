#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_registerbtn_clicked()
{
    QString user = ui->userline->text();
    QString pwd = ui->pwdline->text();

    if (user.isEmpty()) {
        QMessageBox::warning(this, "", "用户名不能为空");
        return;
    }

    if (pwd.isEmpty()) {
        QMessageBox::warning(this, "", "密码不能为空");
        return;
    }

    QSqlQuery query;
    QString s = QString("select * from user_table where name = :username");
    query.prepare(s);
    query.bindValue(":username", user);

    if (!query.exec()) {
        QMessageBox::warning(this, "ERROR", "查询失败，请重试！！");
        qDebug() << "Query Error:" << query.lastError().text();
        return;
    }

    if (query.first()) {
        QMessageBox::warning(this, "ERROR", "用户名重复");
        return;
    }

    QString i = QString("insert into user_table (name, password) values (:username, :password)");
    query.prepare(i);
    query.bindValue(":username", user);
    query.bindValue(":password", pwd);

    if (query.exec()) {
        QMessageBox::information(this, "提示", "注册成功！！", QMessageBox::Yes);
        accept();
    } else {
        QMessageBox::warning(this, "ERROR", "注册失败，请重试！！");
        qDebug() << "Insert Error:" << query.lastError().text();
    }
}

