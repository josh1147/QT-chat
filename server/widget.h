#ifndef WIDGET_H
#define WIDGET_H
#include<QTcpServer>
#include <QWidget>
#include<QTcpSocket>

#include <QSqlDatabase>//
#include <QSqlQuery>//
#include <QSqlError>//

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(const QString &number,QWidget *parent = nullptr);
    ~Widget();

private slots:
    //void on_btn_listen_clicked();

    void on_btn_server_clicked();

    void saveChatData(const QString &message);//
    void on_btn_query_clicked();//

private:
    Ui::Widget *ui;
    QTcpServer* server;
    QTcpSocket* socket;
    QTcpSocket* tes[123];
    QString id[123];
    int num;
    void ClientConnect();
    void ReadData1();

    QSqlDatabase db;//
    void openDatabase();//
    void createTable();//
    void clearChatHistory(); // 清空聊天记录
};
#endif // WIDGET_H
