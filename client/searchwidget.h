#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

#include "widget.h"

#include <QSqlDatabase>//
#include <QSqlQuery>//
#include <QSqlError>//


namespace Ui {
class searchwidget;
}

class searchwidget : public QWidget
{
    Q_OBJECT

public:
    explicit searchwidget(QWidget *parent = nullptr);
    ~searchwidget();

private slots:
    void on_return1_clicked();

    void on_btn_query_clicked();

private:
    Ui::searchwidget *ui;

    QSqlDatabase db;//
};

#endif // SEARCHWIDGET_H
