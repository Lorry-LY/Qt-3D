#include "order.h"
#include "ui_order.h"
#include <QDate>
#include <QDebug>
#include <QMessageBox>

Order::Order(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Order)
{
    ui->setupUi(this);

    db = QSqlDatabase::database();

    ui->label_ID->hide();
    ui->label_ID_3->hide();

    ui->calendarWidget->setGridVisible(true);
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui->calendarWidget->setDateEditEnabled(false);
    connect(ui->calendarWidget,&QCalendarWidget::selectionChanged,this,&Order::update);
}

Order::~Order()
{
    delete ui;
}

void Order::update()
{
    QString curDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
    QSqlQuery query = QSqlQuery(db);
    QString str = QString("select count(*) from 'Order' where date = '%1' ").arg(curDate);
    query.exec(str);
    query.next();
    ui->label_name->setText("无");
    ui->label_name_3->setText("无");
    ui->widget_time->hide();
    ui->widget_time_3->hide();
    if(query.value(0).toInt() != 0){
        str = QString("select p.ID,p.name,p.sex,p.birthday,p.telephone,o.mainAppeal,o.time,o.isFirst,p.address "
                      "from 'Order' o,Patient p where o.date = '%1' and o.patientID = p.ID").arg(curDate);
        query.exec(str);
        while(query.next()){
            QString ID = query.value("ID").toString();
            int time = query.value("time").toInt();
            QString name = query.value("name").toString();
            QString sex = query.value("sex").toString();
            QDate birthday = query.value("birthday").toDate();
            QString telephone = query.value("telephone").toString();
            QString mainAppeal = query.value("mainAppeal").toString();
            QString address = query.value("address").toString();
            QString isFirst = query.value("isFirst").toString();
            if(time == 1){
                ui->label_ID->setText(ID);
                ui->label_name->setText(name);
                ui->label_sex->setText(sex);
                ui->label_age->setText(QString::number(QDateTime::currentDateTime().date().year()-birthday.year()));
                ui->label_phone->setText(telephone);
                ui->label_mainAppeal->setText(mainAppeal);
                ui->label_address->setText(address);
                ui->label_state->setText(isFirst);
                ui->widget_time->show();
            }
            if(time == 2){
                ui->label_ID_3->setText(ID);
                ui->label_name_3->setText(name);
                ui->label_sex_3->setText(sex);
                ui->label_age_3->setText(QString::number(QDateTime::currentDateTime().date().year()-birthday.year()));
                ui->label_phone_3->setText(telephone);
                ui->label_mainAppeal_3->setText(mainAppeal);
                ui->label_address_3->setText(address);
                ui->label_state_3->setText(isFirst);
                ui->widget_time_3->show();
            }
        }
    }
}

void Order::init()
{

}

void Order::on_pushButton_sureOrder_released()
{
    int ret = QMessageBox::question(this,"确认","确认就诊？");
    if(ret == QMessageBox::Ok){
        QString ID = ui->label_ID->text();
    }
}

void Order::on_pushButton_sureOrder_3_released()
{
    int ret = QMessageBox::question(this,"确认","确认就诊？");
    if(ret == QMessageBox::Ok){
        QString ID = ui->label_ID_3->text();
    }
}

void Order::on_pushButton_cancelOrder_released()
{
    int ret = QMessageBox::question(this,"确认","确认取消该患者预约？");
    if(ret == QMessageBox::Ok){
        QString ID = ui->label_ID->text();
    }
}

void Order::on_pushButton_cancelOrder_3_released()
{
    int ret = QMessageBox::question(this,"确认","确认取消该患者预约？");
    if(ret == QMessageBox::Ok){
        QString ID = ui->label_ID_3->text();
    }
}
