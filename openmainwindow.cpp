#include "openmainwindow.h"
#include "ui_openmainwindow.h"

OpenMainWindow::OpenMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpenMainWindow)
{
    ui->setupUi(this);
}

OpenMainWindow::~OpenMainWindow()
{
    delete ui;
}
