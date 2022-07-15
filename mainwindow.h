#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scenemodifier.h"

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
#include <QColumnView>
#include <QTreeWidget>
#include <QtGui/QScreen>

#include <Qt3DExtras/qtorusmesh.h>
#include <Qt3DRender/qmesh.h>
#include <Qt3DRender/qtechnique.h>
#include <Qt3DRender/qmaterial.h>
#include <Qt3DRender/qeffect.h>
#include <Qt3DRender/qtexture.h>
#include <Qt3DRender/qrenderpass.h>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DRender/qpointlight.h>

#include <Qt3DCore/qtransform.h>
#include <Qt3DCore/qaspectengine.h>

#include <Qt3DRender/qrenderaspect.h>
#include <Qt3DExtras/qforwardrenderer.h>

#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/qfirstpersoncameracontroller.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_topCamera_released();

    void on_pushButton_frontCamera_released();

    void on_pushButton_sideCamera_released();

    void dealCameraPositionChanged(QVector3D position);
    void dealCameraViewVectorChanged(QVector3D upVector);

    void setCameraPosition();
    void setCameraViewVector();

    void refreshObject();
    void refreshAttribute(QTreeWidgetItem *current, int column);

    void refreshInformation(QTreeWidgetItem *item, int column);

    void setTransform(Qt3DCore::QTransform *transform);
    void setRotation(QQuaternion q);
    void setPhongMaterial(Qt3DExtras::QPhongMaterial *phongMaterial);
    void setScale(float scale);

    void dealSendMessage(int i,QString str);


    void on_lineEdit_px_editingFinished();

    void on_lineEdit_py_editingFinished();

    void on_lineEdit_pz_editingFinished();

    void on_lineEdit_vx_editingFinished();

    void on_lineEdit_vy_editingFinished();

    void on_lineEdit_vz_editingFinished();

    void on_actionWhite_triggered();

    void on_actionBlack_triggered();

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

//    Qt3DExtras::Qt3DWindow *centerView;
//    Qt3DCore::QEntity centerEntity;

};
#endif // MAINWINDOW_H
