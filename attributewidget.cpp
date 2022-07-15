#include "attributewidget.h"
#include "ui_attributewidget.h"
#include <QTableWidget>
#include <QColorDialog>
#include <complex>

AttributeWidget::AttributeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AttributeWidget)
{
    ui->setupUi(this);
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->tableWidget->item(0,1)->setFlags(Qt::NoItemFlags);
    //    ui->tableWidget->setRowCount(7);
    //    ui->tableWidget->setColumnCount(2);
//    qDebug()<<ui->tableWidget->rowCount()<<ui->tableWidget->columnCount();

    connect(ui->tableWidget,&QTableWidget::itemClicked,[=](QTableWidgetItem *item){
        //        qDebug()<<item->row()<<item->column();
        if(item->row()==6 && item->column() == 1)
        {
            QColor color= QColorDialog::getColor(Qt::white,this,"颜色选择器");
            item->setBackground(QBrush(color));
        }
    });
    connect(ui->tableWidget,&QTableWidget::itemChanged,[=](QTableWidgetItem *item){
//        qDebug()<<item->row()<<item->column()<<item->text();
        if(item->column()==1 && state == 1)
        {
            if(0<=item->row()&&item->row()<3)
            {
                Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
                transform->setTranslation(QVector3D(ui->tableWidget->item(0,1)->text().toFloat(),
                                                    ui->tableWidget->item(1,1)->text().toFloat(),
                                                    ui->tableWidget->item(2,1)->text().toFloat()));
//                transform->setRotation(QQuaternion::fromAxisAndAngle(
//                                           QVector3D(ui->tableWidget->item(3,1)->text().toFloat(),
//                                                     ui->tableWidget->item(4,1)->text().toFloat(),
//                                                     ui->tableWidget->item(5,1)->text().toFloat()),180));
//                Qt3DCore::QTransform::rotateAround();
//                transform->setRotationX(ui->tableWidget->item(3,1)->text().toFloat());
//                transform->setRotationY(ui->tableWidget->item(4,1)->text().toFloat());
//                transform->setRotationZ(ui->tableWidget->item(5,1)->text().toFloat());
//                qDebug()<<transform->translation()<<transform->rotation();
                emit sendTransform(transform);
            }
            else if(item->row()>=3&&item->row()<6)
            {
                QQuaternion q;
                QQuaternion qx;
                double anglex = ui->tableWidget->item(3,1)->text().toDouble();
                qx.setScalar(cos((anglex/2)*3.14/180));
                double aixx = sin((anglex/2)*3.14/180);
                qx.setVector(QVector3D(aixx,0,0));
                QQuaternion qy;
                double angley = ui->tableWidget->item(4,1)->text().toDouble();
                qy.setScalar(cos((angley/2)*3.14/180));
                double aixy = sin((angley/2)*3.14/180);
                qy.setVector(QVector3D(0,aixy,0));
                QQuaternion qz;
                double anglez = ui->tableWidget->item(4,1)->text().toDouble();
                qz.setScalar(cos((anglez/2)*3.14/180));
                double aixz = sin((anglez/2)*3.14/180);
                qz.setVector(QVector3D(0,0,aixz));
                q= qx*qy*qz;
                emit sendRotation(q);
            }
            else if(item->row()==6)
            {
                Qt3DExtras::QPhongMaterial *phongMaterial = new Qt3DExtras::QPhongMaterial();
                phongMaterial->setAmbient(QColor(13,13,13));
                phongMaterial->setDiffuse(ui->tableWidget->item(6,1)->background().color());
                emit sendPhongMaterial(phongMaterial);
            }
        }
    });

    state = 1;
}

AttributeWidget::~AttributeWidget()
{
    delete ui;
}

void AttributeWidget::refreshAttribute(Qt3DCore::QTransform *transform, Qt3DExtras::QPhongMaterial *phongMaterial)
{
    state = 0;
//    qDebug()<<transform->translation()<<transform->rotation();
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("%1").arg(transform->translation().x(),0,'f',4)));
    ui->tableWidget->setItem(1,1,new QTableWidgetItem(QString("%1").arg(transform->translation().y(),0,'f',4)));
    ui->tableWidget->setItem(2,1,new QTableWidgetItem(QString("%1").arg(transform->translation().z(),0,'f',4)));
    ui->tableWidget->setItem(3,1,new QTableWidgetItem(QString("%1").arg(transform->rotationX(),0,'f',4)));
    ui->tableWidget->setItem(4,1,new QTableWidgetItem(QString("%1").arg(transform->rotationY(),0,'f',4)));
    ui->tableWidget->setItem(5,1,new QTableWidgetItem(QString("%1").arg(transform->rotationZ(),0,'f',4)));
    QTableWidgetItem* color = new QTableWidgetItem("");
    color->setBackground(phongMaterial->diffuse());
    ui->tableWidget->setItem(6,1,color);
    state = 1;
//    qDebug()<<"End refresh";
}
