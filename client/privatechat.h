#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QWidget>

namespace Ui {
class privatechat;
}

class privatechat : public QWidget
{
    Q_OBJECT

public:
    explicit privatechat(QWidget *parent = nullptr);
    ~privatechat();

// public:
//     QString gettext();

private slots:
    void on_return1_clicked();

    void on_btn_push_clicked();

private:
    Ui::privatechat *ui;
    // QString id;
};

#endif // PRIVATECHAT_H
