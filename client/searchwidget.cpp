#include "searchwidget.h"
#include "ui_searchwidget.h"

#include <QDebug>
searchwidget::searchwidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::searchwidget)
{
    ui->setupUi(this);
    ui->lineEdit_query->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                               "color: rgb(31,31,31);"		//字体颜色
                               "padding-left:20px;"       //内边距-字体缩进
                               "background-color: rgb(255, 255, 255);" //背景颜色
                               "border:2px solid rgb(20,196,188);border-radius:15px;");//边框粗细-颜色-圆角设置
    ui->textEdit_show->setStyleSheet("font: 25 14pt '微软雅黑 Light';" //字体
                                "color: rgb(31,31,31);"		//字体颜色
                                "padding-left:20px;"       //内边距-字体缩进
                                "background-color: rgb(255, 255, 255);" //背景颜色
                                "border:2px solid rgb(20,196,188);border-radius:15px;}");//边框粗细-颜色-圆角设置

    ui->return1->setStyleSheet("color : rgb(0,100,255);""background-color:rgba(255,255,255,10)") ;
    this->setStyleSheet(
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(255,165,0, 210) ,"
        " stop:1 rgba(255,255,0, 230) );");

    ui->btn_query->setStyleSheet("QPushButton{font: 25 10pt '微软雅黑 Light';color: black;"
                                "background-color: rgb(135,206,235);"
                                "border: none;border-radius:15px;}"
                                "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    ui->label->setStyleSheet("font: 25 12pt '微软雅黑 Light';" "background-color:rgba(255,255,255,0)");

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


