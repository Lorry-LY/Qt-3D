#include "lockerwidget.h"
#include "ui_lockerwidget.h"

#include <QLineEdit>
#include <QDoubleValidator>
#include <QPixmap>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDoubleSpinBox>

LockerWidget::LockerWidget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::LockerWidget)
{
    ui->setupUi(this);

    top = 0;
    side = 0;
    front = 0;

    ui->lockerButton_top->setText("俯视角");
    ui->lockerButton_top->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
    ui->lockerButton_top->setStyleSheet("#LockerButton{background-color:transparent}"
        "#LockerButton:hover{background-color:rgba(195,195,195,0.4)}"
        "#LockerButton:pressed{background-color:rgba(127,127,127,0.4)}"
        "LockerButton{border: none}");
    ui->lockerButton_side->setText("左视角");
    ui->lockerButton_side->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
    ui->lockerButton_side->setStyleSheet("#LockerButton{background-color:transparent}"
        "#LockerButton:hover{background-color:rgba(195,195,195,0.4)}"
        "#LockerButton:pressed{background-color:rgba(127,127,127,0.4)}"
        "LockerButton{border: none}");
    ui->lockerButton_front->setText("前视角");
    ui->lockerButton_front->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
    ui->lockerButton_front->setStyleSheet("#LockerButton{background-color:transparent}"
        "#LockerButton:hover{background-color:rgba(195,195,195,0.4)}"
        "#LockerButton:pressed{background-color:rgba(127,127,127,0.4)}"
        "LockerButton{border: none}");

    ui->widget_top->setVisible(false);
    ui->widget_side->setVisible(false);
    ui->widget_front->setVisible(false);


    connect(ui->lockerButton_top,&LockerButton::released,[=](){
        if(top++ % 2)
        {
            ui->lockerButton_top->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
            ui->widget_top->setVisible(false);
        }
        else
        {
            ui->lockerButton_top->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_show.png"));
            ui->widget_top->setVisible(true);
        }
    });

    connect(ui->lockerButton_side,&LockerButton::released,[=](){
        if(side++ % 2)
        {
            ui->lockerButton_side->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
            ui->widget_side->setVisible(false);
        }
        else
        {
            ui->lockerButton_side->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_show.png"));
            ui->widget_side->setVisible(true);
        }
    });

    connect(ui->lockerButton_front,&LockerButton::released,[=](){
        if(front++ % 2)
        {
            ui->lockerButton_front->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_hide.png"));
            ui->widget_front->setVisible(false);
        }
        else
        {
            ui->lockerButton_front->SetImageLabel(QPixmap(":/lockButton/image/lockerButton_show.png"));
            ui->widget_front->setVisible(true);
        }
    });

}

LockerWidget::~LockerWidget()
{
    delete ui;
}
