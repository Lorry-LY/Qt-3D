#ifndef SCENE_H
#define SCENE_H

#include "scenemodifier.h"

#include <QWidget>
#include <QGuiApplication>

#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QCommandLinkButton>
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
#include <Qt3DExtras/qorbitcameracontroller.h>

namespace Ui {
class Scene;
}

class Scene : public QWidget
{
    Q_OBJECT

public:
    explicit Scene(QWidget *parent = nullptr);
    ~Scene();

    //entity
    Qt3DCore::QEntity* getEntity(int index);
    void setEntity(int index,Qt3DCore::QEntity *input);

    Qt3DCore::QTransform* getTransform(int index);
    void setTransform(int index,Qt3DCore::QTransform* input);

    void setRotation(int index,QQuaternion q);

    Qt3DExtras::QPhongMaterial* getMaterial(int index);
    void setMaterial(int index,Qt3DExtras::QPhongMaterial* input);

    void setScale(int index,float scale);

    QString getObject(int index);
    void setObject(int index,QString objectname);

    int getObjectNumber();

    //camera
    //void setPerspectiveProjection();
    void setPosition(QVector3D point);
    void setUpVector(QVector3D point);
    void setViewCenter(QVector3D point);
    QVector3D getPosition();
    QVector3D getUpVector();
    QVector3D getViewCenter();

    SceneModifier* getModifier();


signals:
    void positionChanged(QVector3D position);
    void viewVectorChanged(QVector3D upVector);
    void sendMessage(int,QString str);



private slots:
    void dealPositionChanged(const QVector3D &position);
    void dealViewVectorChanged(const QVector3D &position);
    void dealSendMessage(int i,QString str);

private:
    Ui::Scene *ui;
    Qt3DExtras::Qt3DWindow *centerView;
//    Qt3DExtras::Qt3DWindow *topView;
//    Qt3DExtras::Qt3DWindow *frontView;
//    Qt3DExtras::Qt3DWindow *sideView;

    //camera
    Qt3DRender::QCamera* centerCameraEntity;

    Qt3DCore::QEntity* centerEntity;

    Qt3DCore::QEntity *centerlightEntity;
//    Qt3DCore::QEntity topEntity;
//    Qt3DCore::QEntity sideEntity;
//    Qt3DCore::QEntity frontEntity;

    SceneModifier *modifier;

};

#endif // SCENE_H
