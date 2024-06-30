#include "choose.h"
#include "ui_choose.h"
#include "widget.h"
choose::choose(const QString &name,QWidget *parent) :
    QDialog(parent),

    ui(new Ui::choose),
    id(name),
    w1(name,111),
    w2(name,222),
    w3(name,333),
    w4(name,444)
{
    ui->setupUi(this);
    this->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(173,216,230, 200),"
        " stop:1 rgba(10,65,128, 210));");

    ui->pushButton->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: black;"
                                 "background-color: rgb(135,206,235);"
                                 "border: none;border-radius:15px;}"
                                 "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                 "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_2->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: black;"
                                  "background-color: rgb(135,206,235);"
                                  "border: none;border-radius:15px;}"
                                  "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                  "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_3->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: black;"
                                  "background-color: rgb(135,206,235);"
                                  "border: none;border-radius:15px;}"
                                  "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                  "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->pushButton_4->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: black;"
                                  "background-color: rgb(135,206,235);"
                                  "border: none;border-radius:15px;}"
                                  "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                  "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->label->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");


}

choose::~choose()
{
    delete ui;
}

void choose::on_pushButton_clicked()
{
        w1.show();
}

void choose::on_pushButton_2_clicked()
{
    w2.show();
}


void choose::on_pushButton_3_clicked()
{
    w3.show();
}

void choose::on_pushButton_4_clicked()
{
    w4.show();
}
