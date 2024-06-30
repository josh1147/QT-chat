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

    ui->pwdline->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                               "color: rgb(31,31,31);"		//字体颜色
                               "padding-left:20px;"       //内边距-字体缩进
                               "background-color: rgb(255, 255, 255);" //背景颜色
                               "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->userline->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                "color: rgb(31,31,31);"		//字体颜色
                                "padding-left:20px;"       //内边距-字体缩进
                                "background-color: rgb(255, 255, 255);" //背景颜色
                                "border:2px solid rgb(20,196,188);border-radius:15px;}");//边框粗细-颜色-圆角设置

    // ui->loginbtn->setStyleSheet("color : yellow;" "width : 50px;") ;
    this->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200),"
        " stop:1 rgba(20,196,188, 210));");
    ui->registerbtn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: yellow;"
                                   "background-color: rgb(20,196,188);"
                                   "border: none;border-radius:15px;}"
                                   "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                   "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed

    ui->label->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");
    ui->label_2->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");
    ui->label_3->setStyleSheet("font: 25 15pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");

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

