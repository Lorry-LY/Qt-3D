#ifndef OPENMAINWINDOW_H
#define OPENMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class OpenMainWindow;
}

class OpenMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenMainWindow(QWidget *parent = nullptr);
    ~OpenMainWindow();

private:
    Ui::OpenMainWindow *ui;
};

#endif // OPENMAINWINDOW_H
