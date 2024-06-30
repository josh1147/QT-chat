#include "widget.h"
#include "ui_widget.h"

Widget::Widget(const QString &name,const int &port,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) , id(name)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    ui->your_id->setText(name);
    ui->room_label->setText(QString("%1号大厅").arg(port/100));
    openDatabase();//
    createTable();//
    clearChatHistory(); // 清空聊天记录
    QString ip = QString("127.0.0.1");
    socket->abort();
    socket->connectToHost(ip,port);
    bool isconnect = socket->waitForConnected();
    if(isconnect){
        ui->textEdit->append("The connection wal successful!");
        ui->btn_push->setEnabled(true);

        QByteArray tmp = QString("#%1").arg(id).toUtf8();
        socket->write(tmp);
        connect(socket,&QTcpSocket::readyRead,this,&Widget::ReadData);

    }
    else{
        ui->textEdit->append("The connection failed");
    }
}

Widget::~Widget()
{
    delete this->socket;
    delete ui;
    db.close(); // 关闭数据库连接
}

void Widget::ReadData(){
    QByteArray buf = socket->readAll();
    ui->textEdit->append(buf);
    saveChatData(QString(buf)); // 存储聊天记录到数据库
}

void Widget::on_btn_push_clicked()
{
    QString target = ui->target_line->text();
    QString tmp = QString("$%1$[用户名:%2]").arg(target).arg(id);
    QByteArray data =(tmp+ui->lineEdit_3->text()) .toUtf8();
    ui->lineEdit_3->clear();
    ui->target_line->clear();
    socket->write(data);
    saveChatData(tmp); // 存储聊天记录到数据库
}

//***************
void Widget::openDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("chat_history.db");
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database." << db.lastError();
    }
}

void Widget::createTable()
{
    QSqlQuery query;
    QString create_sql = "create table if not exists chat_history (id INTEGER PRIMARY KEY AUTOINCREMENT, message TEXT)";
    if (!query.exec(create_sql)) {
        qDebug() << "Error: Failed to create table." << query.lastError();
    }
}

void Widget::clearChatHistory()
{
    QSqlQuery query;
    QString clear_sql = "DELETE FROM chat_history";
    if (!query.exec(clear_sql)) {
        qDebug() << "Error: Failed to clear chat history." << query.lastError();
    }
}


void Widget::saveChatData(const QString &message)
{
    QSqlQuery query;
    query.prepare("INSERT INTO chat_history (message) VALUES (:message)");
    query.bindValue(":message", message);
    if (!query.exec()) {
        qDebug() << "Error: Failed to insert data." << query.lastError();
    }
}
//************

void Widget::on_search1_clicked()
{
    // this->close();
    searchwidget *sch = new searchwidget();
    sch->show();

}

