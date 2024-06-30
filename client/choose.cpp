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
