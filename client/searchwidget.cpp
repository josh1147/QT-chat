#include "searchwidget.h"
#include "ui_searchwidget.h"

#include <QDebug>
searchwidget::searchwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::searchwidget)
{
    ui->setupUi(this);
}

searchwidget::~searchwidget()
{
    delete ui;
}


void searchwidget::on_return1_clicked()
{
    // Widget *father = new Widget();
    this->close();
    // father->show();
}

//***************************
void searchwidget::on_btn_query_clicked()
{
    QString queryText = ui->lineEdit_query->text();
    QSqlQuery query;
    query.prepare("SELECT message FROM chat_history WHERE message LIKE :queryText");
    query.bindValue(":queryText", "%" + queryText + "%"); // 使用 LIKE 进行模糊查询
    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query." << query.lastError();
        return;
    }

    ui->textEdit_show->clear(); // 清空显示历史记录的文本框内容

    while (query.next()) {
        QString message = query.value(0).toString();
        ui->textEdit_show->append(message); // 在lineEdit_show中显示查询结果
    }
}


