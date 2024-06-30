#include "widget.h"
#include "ui_widget.h"
#include <QDebug>//*********
Widget::Widget(const QString &number,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget) ,num(0)
{
    ui->setupUi(this);
    server = new QTcpServer(this);
    connect(server,&QTcpServer::newConnection,this,&Widget::ClientConnect);
    openDatabase();//
    createTable();//
    clearChatHistory(); // 清空聊天记录
    ui->room_number->setText(QString("%1号大厅").arg(number));
    int port ;
    if(number=="1") port = 111 ;
    if(number=="2") port = 222 ;
    if(number=="3") port = 333 ;
    if(number=="4") port = 444 ;
    if(!server->listen(QHostAddress::Any,port))
        qDebug()<<server->errorString();

}

Widget::~Widget()
{
    delete ui;
    server->deleteLater();
    db.close(); // 关闭数据库连接
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


void Widget::ClientConnect(){
    while(server->hasPendingConnections()){
        socket = server->nextPendingConnection();
        QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        //提示连接成功
        ui->textEdit->append(str+"Connect to the server");
        ui->comboBox->addItem(str);
        tes[++num]=socket;
        //id[num] = QString(tes[num]->readAll() );
        //ui->textEdit->append(id[num]);
        connect(tes[num],&QTcpSocket::readyRead,this,&Widget::ReadData1);
    }
}
void Widget::ReadData1(){
    QByteArray buf /*= socket->readAll()*/;//readAll最多接收65532的数据
    for(int i=1;i<=num;i++)
           if(tes[i]->bytesAvailable()>0)
               buf = tes[i]->readAll();
    //QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress().toString()).arg(socket->peerPort());
    QString tmp = QString(buf) ;
    if(tmp[0]=='#'){
        id[num]=tmp.mid(1);
        ui->textEdit->append(QString("用户名:%1").arg(id[num]));
        return;
    }
    int r = 1 ;
    while(tmp[r]!='$') r++ ;
    QString content = tmp.mid(r+1);
    if(r==1){
        ui->textEdit->append(QString("target:所有人"));
        ui->textEdit->append(/*str +*/content);
        for(int i=1;i<=num;i++)
            tes[i]->write((/*str+*/content).toUtf8());

    }
    else{
        QString tar = tmp.mid(1,r-1);
        ui->textEdit->append(QString("target:%1").arg(tar));
        ui->textEdit->append(/*str +*/content);
        for(int i=1;i<=num;i++)
            if(id[i]==tar)
                tes[i]->write((/*str+*/content).toUtf8());
    }




    saveChatData(/*str +*/content); // 存储聊天记录到数据库
}
void Widget::on_btn_server_clicked()
{
    if(ui->comboBox->count()==0) return;
    //QTcpSocket* skt = qvariant_cast<QTcpSocket*>(ui->comboBox->itemData(ui->comboBox->currentIndex()));
    for(int i=1;i<=num;i++)
        tes[i]->write(ui->lineEdit_2->text().toUtf8());
    ui->lineEdit_2->clear();
}

//***************************
void Widget::on_btn_query_clicked()
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
