#include "patientwidget.h"
#include "ui_patientwidget.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>

PatientWidget::PatientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientWidget)
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

}

PatientWidget::~PatientWidget()
{
    delete ui;
}

void PatientWidget::init(QString ID)
{
    //qDebug()<<ID;
    QSqlQuery query = QSqlQuery(db);
    query.prepare("select name,sex,birthday,telephone,address from Patient where ID=:ID");
    query.bindValue(":ID",ID);
    if(!query.exec()){
        QMessageBox::warning(this,"警告","未找到患者数据。");
        close();
    }
    query.next();
    QString name = query.value(0).toString();
    QString sex = query.value(1).toString();
    QDate birthday = query.value(2).toDate();
    QString telephone = query.value(3).toString();
    QString address = query.value(4).toString();
    ui->label_ID->setText(ID);
    //qDebug()<<QDate::currentDate().year();
    //qDebug()<<birthday;
    //qDebug()<<birthday.year();
    int old = (QDate::currentDate().year()-birthday.year());
    ui->label_old->setText(QString::number(old));
    ui->label_sex->setText(sex);
    ui->label_name->setText(name);
    ui->label_phone->setText(telephone);
    ui->label_address->setText(address);
    ui->label_description->clear();

    QString description;

    query.prepare("select h.name,p.remark from Patient_Allergic p,AllergicHistory h where p.ID=h.ID and p.patientID = :ID order by h.ID");
    query.bindValue(":ID",ID);
    query.exec();
    QStringList allergic;
    while(query.next())
    {
        if(query.value(0).toString() == "其他"){
            allergic.push_back(query.value(1).toString());
        }else{
            allergic.push_back(query.value(0).toString());
        }
    }
    while(!allergic.empty()){
        description+=allergic.back()+" ";
        allergic.pop_back();
    }
    description+="\n";

    query.prepare("select h.name,p.remark from Patient_PastMedical p,PastMedicalHistory h where p.ID=h.ID and p.patientID = :ID order by h.ID");
    query.bindValue(":ID",ID);
    query.exec();
    QStringList pastMedical;
    while(query.next())
    {
        if(query.value(0).toString() == "其他"){
            pastMedical.push_back(query.value(1).toString());
        }else{
            pastMedical.push_back(query.value(0).toString());
        }
    }
    while(!pastMedical.empty()){
        description+=pastMedical.back()+" ";
        pastMedical.pop_back();
    }
    description+="\n";

    query.prepare("select h.name,p.remark from Patient_Pharmaco p,Pharmacohistory h where p.ID=h.ID and p.patientID = :ID order by h.ID");
    query.bindValue(":ID",ID);
    query.exec();
    QStringList pharmaco;
    while(query.next())
    {
        if(query.value(0).toString() == "其他"){
            pharmaco.push_back(query.value(1).toString());
        }else{
            pharmaco.push_back(query.value(0).toString());
        }
    }
    while(!pharmaco.empty()){
        description+=pharmaco.back()+" ";
        pharmaco.pop_back();
    }
    description+="\n";

    ui->label_description->setText(description);


}
