#ifndef LOCKER_WIDGET_H
#define LOCKER_WIDGET_H

#include "lockerbutton.h"

#include <QWidget>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class LockerWidget; }
QT_END_NAMESPACE

class LockerWidget : public QWidget
{
    Q_OBJECT
public:
    /// @brief 构造方法
    explicit LockerWidget(QWidget* parent = nullptr);
    ~LockerWidget();

private:
    quint8 top;
    quint8 side;
    quint8 front;

    Ui::LockerWidget *ui;
};

#endif // LOCKER_WIDGET_H
