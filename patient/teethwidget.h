#ifndef TEETHWIDGET_H
#define TEETHWIDGET_H

#include <QWidget>

namespace Ui {
class TeethWidget;
}

class TeethWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeethWidget(QWidget *parent = nullptr);
    ~TeethWidget();

private:
    Ui::TeethWidget *ui;
};

#endif // TEETHWIDGET_H
