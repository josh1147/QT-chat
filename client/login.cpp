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


    // this->setStyleSheet("background-color: red;");
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

    ui->loginbtn->setStyleSheet("color : yellow;" "width : 50px;") ;
    this->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(251,102,102, 200),"
        " stop:1 rgba(20,196,188, 210));");
    ui->registerbtn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: yellow;"
                                "background-color: rgb(20,196,188);"
                                "border: none;border-radius:15px;}"
                                "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->loginbtn->setStyleSheet("QPushButton{font: 25 14pt '微软雅黑 Light';color: yellow;"
                                   "background-color: rgb(20,196,188);"
                                   "border: none;border-radius:15px;}"
                                   "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                   "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->label->setStyleSheet("font: 25 15pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");
    ui->label_2->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");
    ui->label_3->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");


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
