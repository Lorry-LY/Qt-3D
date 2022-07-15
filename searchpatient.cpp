#include "searchpatient.h"
#include "ui_searchpatient.h"

#include <QMessageBox>
#include <QDebug>
#include <QTableWidget>

SearchPatient::SearchPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchPatient)
{
    ui->setupUi(this);

    db=QSqlDatabase::database();//说明数据库名称
    //QString dbPath=QCoreApplication::applicationDirPath()+"//program.db";
//    db.setDatabaseName("project.db");//打开数据库
//    if(!db.open())
//    {
//        QMessageBox::warning(this,"错误","数据库打开失败！！！");
//        close();
//    }

    connect(ui->tableView_result,&QTableView::doubleClicked,this,&SearchPatient::dealDoubleClicked);


}

SearchPatient::~SearchPatient()
{
    delete ui;
}

void SearchPatient::init()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_phone->clear();
    ui->lineEdit_IDCard->clear();
    ui->lineEdit_doctor->clear();
    ui->comboBox_sex->setCurrentIndex(0);
    ui->dateEdit_outDate->setDate(QDate::currentDate());
    ui->tableView_result->clearSpans();
    ui->comboBox_mainAppeal->addItem("");

    QSqlQuery query = QSqlQuery(db);
    query.prepare("select name from MainAppeal");
    query.exec();
    while (query.next())
    {
        QString name = query.value(0).toString();
        ui->comboBox_mainAppeal->addItem(name);
    }

}

void SearchPatient::on_pushButton_search_released()
{
    QString str = "select p.ID,p.name,p.sex,p.birthday,p.telephone,o.outPatientID,o.date,d.name,d.department,m.name"
            " from Outpatient o,Doctor d,Patient p,MainAppeal m"
            " where p.ID=o.patientID and d.ID=o.doctorID and m.ID=o.mainAppealID";
    if(""!=ui->lineEdit_name->text()){
        str+=" and p.name like '%"+ui->lineEdit_name->text()+"%'";
    }
    if(""!=ui->lineEdit_phone->text()){
        str+=" and p.telephone='"+ui->lineEdit_phone->text()+"'";
    }
    if(""!=ui->lineEdit_IDCard->text()){
        str+=" and p.IDCard='"+ui->lineEdit_IDCard->text()+"'";
    }
    if(""!=ui->lineEdit_doctor->text()){
        str+=" and d.name='"+ui->lineEdit_doctor->text()+"'";
    }
    if(""!=ui->comboBox_sex->currentText()){
        str+=" and p.sex='"+ui->comboBox_sex->currentText()+"'";
    }
    if(""!=ui->comboBox_mainAppeal->currentText()){
        str+=" and m.name='"+ui->comboBox_mainAppeal->currentText()+"'";
    }
    if(ui->dateEdit_outDate->date()!=QDate::currentDate()){
        str+=" and o.date='"+ui->dateEdit_outDate->date().toString()+"'";
    }

    //qDebug()<<str;

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(str);
    model->setHeaderData(0,Qt::Horizontal,"患者ID");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"性别");
    model->setHeaderData(3,Qt::Horizontal,"出生年月");
    model->setHeaderData(4,Qt::Horizontal,"联系电话");
    model->setHeaderData(5,Qt::Horizontal,"门诊单号");
    model->setHeaderData(6,Qt::Horizontal,"就诊日期");
    model->setHeaderData(7,Qt::Horizontal,"主治医师");
    model->setHeaderData(8,Qt::Horizontal,"科室");
    model->setHeaderData(9,Qt::Horizontal,"主治内容");
    ui->tableView_result->setModel(model);
    ui->tableView_result->setAlternatingRowColors(true);

    ui->tableView_result->show();
}

void SearchPatient::on_pushButton_newPatient_released()
{
    emit newPatient();
}

void SearchPatient::dealDoubleClicked(const QModelIndex &index)
{
    //QTableWidget *widget = new QTableWidget();
    QString ID = ui->tableView_result->model()->index(index.row(),0).data().toString();
    QString name = ui->tableView_result->model()->index(index.row(),1).data().toString();
    QString str = name + " (" + ID +")";

    //qDebug()<<str;
    emit changeToPatientWidget(str);
}
