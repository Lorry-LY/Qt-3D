#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = nullptr);
    ~Order();

    void update();
    void init();

private slots:
    void on_pushButton_sureOrder_released();

    void on_pushButton_sureOrder_3_released();

    void on_pushButton_cancelOrder_released();

    void on_pushButton_cancelOrder_3_released();

private:
    Ui::Order *ui;
    QSqlDatabase db;
};

#endif // ORDER_H
