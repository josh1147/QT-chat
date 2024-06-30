#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpSocket>

#include <QSqlDatabase>//
#include <QSqlQuery>//
#include <QSqlError>//

#include <searchwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(const QString &name,const int &port,QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket* socket;
    QString id;

    // void ReadData1();//

    QSqlDatabase db;//
    void openDatabase();//
    void createTable();//
    void clearChatHistory(); // 清空聊天记录

private slots:
    // void on_btn_connect_clicked();
    void ReadData();
    void on_btn_push_clicked();

    void saveChatData(const QString &message);//

    // void paintEvent(QPaintEvent* event);

    void on_search1_clicked();//


};
#endif // WIDGET_H
