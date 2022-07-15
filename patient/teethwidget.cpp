#include "teethwidget.h"
#include "ui_teethwidget.h"

TeethWidget::TeethWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeethWidget)
{
    ui->setupUi(this);
}

TeethWidget::~TeethWidget()
{
    delete ui;
}
