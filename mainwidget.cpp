#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QRegExp>
#include <QQuickWidget>
#include <QInputDialog>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("project.db");
    if(!db.open())
    {
        QMessageBox::critical(this,"数据库打开失败",db.lastError().text());
    }

    tcpServer = new QTcpServer(this);
    connect(tcpServer,&QTcpServer::newConnection,this,&MainWidget::dealNewConnection);
    connect(tcpServer,&QTcpServer::acceptError,this,&MainWidget::dealAcceptError);
    if(!tcpServer->listen(QHostAddress::Any, 8888)){
        QMessageBox::warning(this,"警告","网络连接失败。");
    }

    newPatient = new NewPatient();
    patientWidget = new PatientWidget();
    searchPatient = new SearchPatient();
    connect(newPatient,&NewPatient::createFinished,[=](QString str){
        newPatient->close();
        addPatientItem(str);
    });
    connect(ui->treeWidget_actors,&QTreeWidget::doubleClicked,this,&MainWidget::dealOpenPatient);
    connect(searchPatient,&SearchPatient::newPatient,this,&MainWidget::on_pushButton_newPatient_released);
    connect(searchPatient,&SearchPatient::changeToPatientWidget,this,&MainWidget::dealChangeToPatientWidget);
    //connect(ui->quickWidget,)

    QList<QPushButton*> buttons_add = ui->tab_addMedical->findChildren<QPushButton*>();
    while (!buttons_add.empty()) {
        QPushButton* button = buttons_add.back();
        buttons_add.pop_back();
        connect(button,&QPushButton::released,[=](){
            QString s1 = button->objectName();
            //qDebug()<<s1;
            QRegExp rx1("add[a-zA-Z]{1,}");
            rx1.indexIn(s1);
            QString tableName = rx1.capturedTexts().at(0).mid(3);
            bool ok = false;
            QString text = QInputDialog::getText(this,"内容添加","请输入要添加的内容",QLineEdit::Normal,"",&ok);
            if(ok&&text!=""){
                QSqlQuery query = QSqlQuery(db);
                QString str = QString("insert into %1(ID,name) values(null,'%2')")
                        .arg(tableName).arg(text);
                //qDebug()<<str;
                if(query.exec(str)){
                    QMessageBox::warning(this,"成功","添加信息成功。");
                }else{
                    QMessageBox::warning(this,"失败","信息已存在。");
                }
            }
        });
    }



}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_newPatient_released()
{
    newPatient->init();
    newPatient->show();
}

void MainWidget::dealOpenPatient(const QModelIndex &index)
{
    QString s1 = index.data().toString();
    QRegExp rx1("([(]\\d{1,18}[)])");
    rx1.indexIn(s1);
    QString ID = rx1.capturedTexts().at(0);
    QRegExp rx2("(\\d{1,18})");
    rx2.indexIn(ID);
    ID = rx2.capturedTexts().at(0);
    patientWidget->init(ID);
    patientWidget->show();


}

void MainWidget::dealChangeToPatientWidget(QString str)
{
    searchPatient->close();
    addPatientItem(str);
}

void MainWidget::on_pushButton_searchPatient_released()
{
    searchPatient->init();
    searchPatient->show();
}

void MainWidget::addPatientItem(QString str)
{
    //qDebug()<<ui->treeWidget_actors->topLevelItemCount();
    for(int i=0;i<ui->treeWidget_actors->topLevelItemCount();i++)
    {
        if(str == ui->treeWidget_actors->topLevelItem(i)->text(0))return;
    }
    QTreeWidgetItem* patient = new QTreeWidgetItem(ui->treeWidget_actors);
    patient->setText(0,str);
    patient->setFlags(Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    ui->treeWidget_actors->addTopLevelItem(patient);
}


void MainWidget::on_pushButton_checkOrder_released()
{
    Order* order = new Order();
    order->setObjectName("order");
    order->setAttribute(Qt::WA_DeleteOnClose,true);
    order->init();
    order->update();
    order->show();
    //    connect(order,SIGNAL(Order::close()),order,SLOT(Order::deleteLater()));

}

void MainWidget::dealNewConnection()
{
    //取出建立好链接的套接字
    QTcpSocket* tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,&QTcpSocket::readyRead,[=](){
        //从通信套接字中取出内容。
        QByteArray array= tcpSocket->readAll();
        QString str = QString::fromStdString(array.toStdString());
        qDebug()<<str;
        QStringList list = str.split(' ');
        int command = list[0].toInt();
        list.pop_front();
        switch (command) {
        case 101:{
            QString name = list[0];
            list.pop_front();
            QString IDCard = list[0];
            list.pop_front();
            QString password = list[0];
            list.pop_front();
            QString str = QString("select ID,name,IDCard,password from Patient "
                                  "where name='%1' and IDCard='%2' and password='%3'")
                    .arg(name).arg(IDCard).arg(password);
            QSqlQuery query = QSqlQuery(db);
            query.exec(str);
            if(query.next()){
                QString ID = query.value("ID").toString();
                QString data = "101 "+ID+" ";
                tcpSocket->write(data.toStdString().data());
            }else{
                QString message = QString("账户或密码错误");
                QString data = "102 "+message;
                tcpSocket->write(data.toStdString().data());
            }
            break;
        }
        case 181:{
            QString name = list[0];
            list.pop_front();
            QString IDCard = list[0];
            list.pop_front();
            QString phone = list[0];
            list.pop_front();
            QString str = QString("select name,IDCard,phone from Visitor "
                                  "where name='%1' and IDCard='%2' and phone='%3'")
                    .arg(name).arg(IDCard).arg(phone);
            QSqlQuery query = QSqlQuery(db);
            query.exec(str);
            if(query.next()){
                QString IDCard = query.value("IDCard").toString();
                QString data = "181 "+IDCard;
                tcpSocket->write(data.toStdString().data());
            }else{
                QString str = QString("insert into Visitor(IDCard,name,phone) "
                                      "values(%1,'%2','%3')")
                        .arg(IDCard).arg(IDCard).arg(phone);
                QSqlQuery query = QSqlQuery(db);
                if(query.exec(str)){
                    QString data = "181 "+IDCard;
                    tcpSocket->write(data.toStdString().data());
                }else{
                    QString message = "服务器出错，暂时无法登录。";
                    QString data = "182 "+message;
                    tcpSocket->write(data.toStdString().data());
                }

            }
            break;
        }
        case 301:{
            QStringList list;
            QString str = QString("select date,time from 'Order'");
            QSqlQuery query = QSqlQuery(db);
            if(query.exec(str)){
                while (query.next()) {
                    list.append(QString("%1,%2")
                                .arg(query.value("date").toString())
                                .arg(query.value("time").toString()));
                }
                QString data = "301 "+list.join(" ");
                tcpSocket->write(data.toStdString().data());
            }else{
                QString message = "服务器出错，暂时无法登录。";
                QString data = "302 "+message;
                tcpSocket->write(data.toStdString().data());
            }
            break;
        }
        case 303:{
            QString ID = list[0];
            list.pop_front();
            QString dateTime = list[0];
            QStringList dt = dateTime.split(",");
            list.pop_front();
            QString mainAppeal = list[0];
            list.pop_front();
            QString isFirst = list[0];
            list.pop_front();

            QSqlQuery query = QSqlQuery(db);
            QString str = QString("select * from 'Order' "
                                  "where date = '%1' and time = '%2' ")
                    .arg(dt[0]).arg(dt[1]);
            query.exec(str);
            if(query.next()){
                tcpSocket->write("306");
            }else{
                str = QString("insert into 'Order'(ID,visitorIDCard,date,time,isFirst,mainAppeal) "
                              "values(null,'%1','%2',%3,'%4','%5')")
                        .arg(ID).arg(dt[0]).arg(dt[1]).arg(isFirst).arg(mainAppeal);
                if(query.exec(str)){
                    tcpSocket->write("305");
                }else{
                    tcpSocket->write("302");
                }
            }
            break;
        }
        case 304:{
            QString ID = list[0];
            list.pop_front();
            QString dateTime = list[0];
            QStringList dt = dateTime.split(",");
            list.pop_front();
            QString mainAppeal = list[0];
            list.pop_front();
            QString isFirst = list[0];
            list.pop_front();

            QSqlQuery query = QSqlQuery(db);
            QString str = QString("select * from 'Order' "
                                  "where date = '%1' and time = '%2' ")
                    .arg(dt[0]).arg(dt[1]);
            query.exec(str);
            if(query.next()){
                tcpSocket->write("306");
            }else{
                str = QString("insert into 'Order'(ID,patientID,date,time,isFirst,mainAppeal) "
                              "values(null,%1,'%2',%3,'%4','%5')")
                        .arg(ID).arg(dt[0]).arg(dt[1]).arg(isFirst).arg(mainAppeal);
                if(query.exec(str)){
                    tcpSocket->write("305");
                }else{
                    tcpSocket->write("302");
                }
            }
            break;
        }
        default:
            break;
        }
    });
}

void MainWidget::dealAcceptError(QAbstractSocket::SocketError socketError)
{
    qDebug()<<socketError;
}
