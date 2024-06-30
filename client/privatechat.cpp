#include "privatechat.h"
#include "ui_privatechat.h"

privatechat::privatechat(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::privatechat)
{
    ui->setupUi(this);
}

privatechat::~privatechat()
{
    delete ui;
}

void privatechat::on_return1_clicked()
{
    this->close();
}


void privatechat::on_btn_push_clicked()
{
    // QString target = ui->target_line->text();
    // QString tmp = QString("$%1$[用户名:%2]").arg(target).arg(id);
    // QByteArray data =(tmp+ui->lineEdit_3->text()) .toUtf8();
    // ui->lineEdit_3->clear();
    // ui->target_line->clear();
    // socket->write(data);
    // saveChatData(tmp); // 存储聊天记录到数据库
}

