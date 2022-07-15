#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    db = QSqlDatabase::database();
//    qDebug()<<"2";
    setWindowTitle("智见未来-口腔美学及健康管理软件");
    setAutoFillBackground(true);
    QPalette pal = this->palette();
    //    pal.setColor(QPalette::Background, QColor(19, 54, 118));
    pal.setBrush(backgroundRole(), QPixmap(":/image/image/background.jpg"));
    setPalette(pal);

//    qDebug()<<"3";
    ui->label_index->setHidden(true);
    //    ui->tableWidget_teeth->setAl

    connect(ui->widget_main,&Scene::positionChanged,this,&MainWindow::dealCameraPositionChanged);
    connect(ui->widget_main,&Scene::viewVectorChanged,this,&MainWindow::dealCameraViewVectorChanged);

    connect(ui->attribute,&AttributeWidget::sendTransform,this,&MainWindow::setTransform);
    connect(ui->attribute,&AttributeWidget::sendPhongMaterial,this,&MainWindow::setPhongMaterial);
    connect(ui->attribute,&AttributeWidget::sendRotation,this,&MainWindow::setRotation);

    connect(ui->treeWidget_object,&QTreeWidget::itemClicked,this,&MainWindow::refreshAttribute);
    connect(ui->treeWidget_object,&QTreeWidget::itemChanged,this,&MainWindow::refreshInformation);
    connect(ui->widget_main,&Scene::sendMessage,this,&MainWindow::dealSendMessage);
//    qDebug()<<"6";
    refreshObject();
//    qDebug()<<"4";


    QList<QSlider*> sliders = ui->tab->findChildren<QSlider*>();
    QList<QLabel*> edits = ui->tab->findChildren<QLabel*>();
    for (int i=0;i<sliders.size();i++) {
        if(i<6)
        {
            sliders[i]->setMinimum(-2000);
            sliders[i]->setMaximum(2000);
        }
        else
        {
            sliders[i]->setMinimum(-1800);
            sliders[i]->setMaximum(1800);
        }

        connect(sliders[i],&QSlider::valueChanged,[=](int value){
            double length = ui->horizontalSlider_1->value()/1.0/100;
            double topRadius = ui->horizontalSlider_2->value()/1.0/100;
            double bottomRadius = ui->horizontalSlider_3->value()/1.0/100;
            double x = ui->horizontalSlider_4->value()/1.0/10;
            double y = ui->horizontalSlider_5->value()/1.0/10;
            double z = ui->horizontalSlider_6->value()/1.0/10;
            double X = ui->horizontalSlider_7->value()/1.0/10;
            double Y = ui->horizontalSlider_8->value()/1.0/10;
            double Z = ui->horizontalSlider_9->value()/1.0/10;
            edits[i]->setText(QString("%1").arg(value/1.0/10));
            Qt3DCore::QTransform *transform = new Qt3DCore::QTransform();
            transform->setTranslation(QVector3D(x,y,z));
            transform->setRotationX(X);
            transform->setRotationY(Y);
            transform->setRotationZ(Z);
            ui->widget_main->getModifier()->setTransform(transform);
            ui->widget_main->getModifier()->setLength(length);
            ui->widget_main->getModifier()->setTop(topRadius);
            ui->widget_main->getModifier()->setBottom(bottomRadius);
        });
    }

//    qDebug()<<"5";

    QSqlQuery query = QSqlQuery(db);
    query.exec("select x,y,z,xx,yy,zz from Color");
    for(int i=0;i<ui->tableWidget->columnCount();i++)
    {
        query.next();
        for(int j=0;j<ui->tableWidget->rowCount();j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(query.value(j).toString());
            item->setTextAlignment(Qt::AlignHCenter);
            ui->tableWidget->setItem(j,i,item);
        }
    }

//    qDebug()<<"1";
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_topCamera_released()
{
    ui->widget_main->setPosition(QVector3D(0,30,100));
    ui->widget_main->setViewCenter(QVector3D(0,30,0));
    ui->widget_main->setUpVector(QVector3D(1,0,0));
}

void MainWindow::on_pushButton_frontCamera_released()
{
    ui->widget_main->setPosition(QVector3D(0,135,-5));
    ui->widget_main->setViewCenter(QVector3D(0,0,0));
    ui->widget_main->setUpVector(QVector3D(0,0,1));

}

void MainWindow::on_pushButton_sideCamera_released()
{
    ui->widget_main->setPosition(QVector3D(91,30,0));
    ui->widget_main->setViewCenter(QVector3D(0,30,0));
    ui->widget_main->setUpVector(QVector3D(0,1,0));
}

void MainWindow::dealCameraPositionChanged(QVector3D position)
{
    ui->lineEdit_px->setText(QString::number(position.x(),'f',2));
    ui->lineEdit_py->setText(QString::number(position.y(),'f',2));
    ui->lineEdit_pz->setText(QString::number(position.z(),'f',2));
}

void MainWindow::dealCameraViewVectorChanged(QVector3D upVector)
{
    ui->lineEdit_vx->setText(QString::number(upVector.x(),'f',2));
    ui->lineEdit_vy->setText(QString::number(upVector.y(),'f',2));
    ui->lineEdit_vz->setText(QString::number(upVector.z(),'f',2));
}

void MainWindow::setCameraPosition()
{
    ui->widget_main->setPosition(QVector3D(ui->lineEdit_px->text().toFloat(),ui->lineEdit_py->text().toFloat(),ui->lineEdit_pz->text().toFloat()));
}

void MainWindow::setCameraViewVector()
{
    ui->widget_main->setViewCenter(QVector3D(ui->lineEdit_vx->text().toFloat(),ui->lineEdit_vy->text().toFloat(),ui->lineEdit_vz->text().toFloat()));
}

void MainWindow::refreshObject()
{
//    qDebug()<<"7";
    //Sleep(5000);
    int i=0;
    ui->treeWidget_object->setColumnCount(3);//设置列
    ui->treeWidget_object->setHeaderLabels(QStringList()<<"index"<<"对象"<<"类");//设置标题
    QList<QTreeWidgetItem*> items;
    int number = ui->widget_main->getObjectNumber();
    //qDebug()<<number;
    while (i < number) {
        //Qt3DCore::QEntity *temp = ui->widget_main->getEntity(i);
        QTreeWidgetItem *Item = new QTreeWidgetItem();
        //        Item->setBackgroundColor(2,ui->widget_main->getMaterial(i)->diffuse());
        Item->setText(0,QString::number(i));
        Item->setText(1,ui->widget_main->getEntity(i)->objectName());
        Item->setText(2,ui->widget_main->getObject(i));
        Item->setFlags(Item->flags()|Qt::ItemIsEditable);
        items.append(Item);
        Item->setHidden(false);//设置隐藏
        i++;
    }
    ui->treeWidget_object->insertTopLevelItems(0, items);
    ui->treeWidget_object->hideColumn(0);
//    qDebug()<<"8";
    refreshAttribute(ui->treeWidget_object->itemAt(0,0),0);

}

void MainWindow::refreshAttribute(QTreeWidgetItem *current, int column)
{
//    qDebug()<<"13";
    int index = current->text(0).toInt();
    //    qDebug()<<"hello2";
    ui->label_index->setNum(index);
//    qDebug()<<"12";
    QString title = ui->widget_main->getEntity(index)->objectName();
    title.append(':');
    title += ui->widget_main->getObject(index);
    ui->label_attribute->setText(title);
//    qDebug()<<"10";
    Qt3DCore::QTransform *transform = ui->widget_main->getTransform(index);
    Qt3DExtras::QPhongMaterial *material = ui->widget_main->getMaterial(index);
//    qDebug()<<"11";
    setScale(1.2);
//    qDebug()<<"9";
    ui->attribute->refreshAttribute(transform,material);

}

void MainWindow::refreshInformation(QTreeWidgetItem *item, int column)
{
    int index = item->text(0).toInt();
    if(column == 2)
    {
        ui->widget_main->setObject(index,item->text(column));
    }
    if(column == 1)
    {
        Qt3DCore::QEntity* temp = ui->widget_main->getEntity(index);
        temp->setObjectName(item->text(column));
        ui->widget_main->setEntity(index,temp);
    }
    refreshAttribute(item,column);
}

void MainWindow::setTransform(Qt3DCore::QTransform *transform)
{
    //    qDebug()<<transform->translation();
    ui->widget_main->setTransform(ui->label_index->text().toFloat(),transform);
}

void MainWindow::setRotation(QQuaternion q)
{
    ui->widget_main->setRotation(ui->label_index->text().toFloat(),q);
}

void MainWindow::setPhongMaterial(Qt3DExtras::QPhongMaterial *phongMaterial)
{
    ui->widget_main->setMaterial(ui->label_index->text().toInt(),phongMaterial);
}

void MainWindow::setScale(float scale)
{
    ui->widget_main->setScale(ui->label_index->text().toInt(),scale);
}

void MainWindow::dealSendMessage(int i, QString str)
{
    if(1 == i)
    {
        ui->listWidget_system->addItem(str);
    }

    //ui->tabWidget_bottom->setTabText(i,str);
}

void MainWindow::on_lineEdit_px_editingFinished()
{
    setCameraPosition();
}


void MainWindow::on_lineEdit_py_editingFinished()
{
    setCameraPosition();
}

void MainWindow::on_lineEdit_pz_editingFinished()
{
    setCameraPosition();
}

void MainWindow::on_lineEdit_vx_editingFinished()
{
    setCameraViewVector();
}

void MainWindow::on_lineEdit_vy_editingFinished()
{
    setCameraViewVector();
}

void MainWindow::on_lineEdit_vz_editingFinished()
{
    setCameraViewVector();
}

void MainWindow::on_actionWhite_triggered()
{
    //    ui->widget->setStyleSheet("QWidget{background-color: rgb(250, 255, 244);}");
    //    ui->widget_center->setStyleSheet("QWidget{background-color: rgb(245, 245, 255);}");
    //    ui->widget_object->setStyleSheet("QWidget{background-color: rgb(240, 245, 241);}");
    //    ui->widget_attribute->setStyleSheet("QWidget{background-color: rgb(255, 244, 229);}");
    //    ui->widget_topbar->setStyleSheet("QWidget{background-color: qlineargradient(spread:reflect, x1:1, y1:0.295, x2:1, y2:1, stop:0 rgba(119, 158, 255, 255), stop:1 rgba(255, 255, 255, 255));}");
    //    ui->widget_bottom->setStyleSheet("QWidget{background-color: rgb(240, 235, 255);border-color: rgb(16, 97, 147);}");
    //    ui->labeltitle->setStyleSheet("QLabel{background-color: rgb(240, 235, 255);color: rgb(85, 170, 255);}");

}

void MainWindow::on_actionBlack_triggered()
{
    //    ui->tabWidget->setStyleSheet("QTabBar::tab{width:80}QTabBar::tab{height:50}QTabBar::tab:selected{background-color: qlineargradient(spread:reflect, x1:1, y1:0.295, x2:1, y2:1, stop:0 rgba(119, 158, 255, 255), stop:1 rgba(255, 255, 255, 255))}QTabBar::tab:!selected{background-color: rgb(127, 127, 127)}QTabBar::tab{border-top-left-radius: 8px;border-top-right-radius: 8px}");
    //    ui->widget->setStyleSheet("QWidget{background-color: rgb(65, 85, 98);}");
    //    ui->widget_center->setStyleSheet("QWidget{background-color: rgb(39,40,34);border-color: rgb(170, 255, 255);border-color: qconicalgradient(cx:0.5, cy:0.5, angle:0, stop:0 rgba(35, 40, 3, 255), stop:0.16 rgba(136, 106, 22, 255), stop:0.225 rgba(166, 140, 41, 255), stop:0.285 rgba(204, 181, 74, 255), stop:0.345 rgba(235, 219, 102, 255), stop:0.415 rgba(245, 236, 112, 255), stop:0.52 rgba(209, 190, 76, 255), stop:0.57 rgba(187, 156, 51, 255), stop:0.635 rgba(168, 142, 42, 255), stop:0.695 rgba(202, 174, 68, 255), stop:0.75 rgba(218, 202, 86, 255), stop:0.815 rgba(208, 187, 73, 255), stop:0.88 rgba(187, 156, 51, 255), stop:0.935 rgba(137, 108, 26, 255), stop:1 rgba(35, 40, 3, 255));}");
    //    ui->tabWidget_bottom->setStyleSheet("QTabBar::tab{width:60}QTabBar::tab{height:30}QTabBar::tab:selected{background-color: qlineargradient(spread:reflect, x1:1, y1:0.295, x2:1, y2:1, stop:0 rgba(119, 158, 255, 255), stop:1 rgba(255, 255, 255, 255))}QTabBar::tab:!selected{background-color: rgb(127, 127, 127)}QTabBar::tab{border-top-left-radius: 20px;border-top-right-radius: 5px}");
    //    ui->widget_object->setStyleSheet("QWidget{background-color: rgb(67,67,67);}");
    //    ui->widget_attribute->setStyleSheet("QWidget{background-color: rgb(57,67,67);}");
    //    ui->widget_topbar->setStyleSheet("QWidget{background-color: qlineargradient(spread:pad, x1:0.385042, y1:0.5, x2:0.390833, y2:0.04, stop:0.40625 rgba(0, 0, 0, 255), stop:1 rgba(92, 92, 92, 255));}");
    //    ui->widget_bottom->setStyleSheet("QWidget{background-color: rgb(38, 42, 37);}");
    //    ui->labeltitle->setStyleSheet("QLabel{background-color: rgb(38, 42, 37);color: rgb(85, 170, 255);}");
}
