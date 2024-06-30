#include "dialog.h"
#include "login.h"
#include "widget.h"
#include "choose.h"
#include <QApplication>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include <QFile>
// QString loadQSS() {
//     QFile file(":/style.qss");
//     file.open(QFile::ReadOnly);
//     QString style = file.readAll();
//     file.close();
//     return style;
// }

QSqlDatabase db;
void setupDatabase() {
    // 添加 SQLite 数据库驱动并设置数据库名
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/54259/Desktop/QT-chat-master/client/database.db");

    // 尝试打开数据库连接
    if (!db.open()) {
        qDebug() << "Database Error: " << db.lastError().text();
        return;
    }

    // 创建表
    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS user_table ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "name TEXT NOT NULL, "
                               "password TEXT NOT NULL)";
    if (!query.exec(createTableQuery)) {
        qDebug() << "Create Table Error: " << query.lastError().text();
    } else {
        qDebug() << "Table created successfully!";
    }

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setupDatabase();

    // QString qss;
    // QFile file(":/style.qss");
    // file.open(QFile::ReadOnly);
    // qss=file.readAll();
    // a.setStyleSheet(qss);
    // file.close();

   login dlg ;
   if(dlg.exec()==QDialog::Accepted){
       QString id = dlg.present_id;
       choose w(id) ;
       w.show();
       return a.exec();
   }
   else return 0;
}
