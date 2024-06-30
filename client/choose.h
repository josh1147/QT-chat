#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>
#include "widget.h"
namespace Ui {
class choose;
}

class choose : public QDialog
{
    Q_OBJECT

public:
    explicit choose(const QString &name,QWidget *parent = nullptr);
    ~choose();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::choose *ui;
    QString id;
    Widget w1,w2,w3,w4;
};

#endif // CHOOSE_H
