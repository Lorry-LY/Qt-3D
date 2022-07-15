#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QWidget>
#include <Qt3DRender/qcamera.h>
#include <Qt3DCore/qentity.h>
#include <Qt3DRender/qcameralens.h>
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
#include <QPhongMaterial>

namespace Ui {
class AttributeWidget;
}

class AttributeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AttributeWidget(QWidget *parent = nullptr);
    ~AttributeWidget();

    void refreshAttribute(Qt3DCore::QTransform *transform,Qt3DExtras::QPhongMaterial *phongMaterial);

signals:
    void sendTransform(Qt3DCore::QTransform *transform);
    void sendPhongMaterial(Qt3DExtras::QPhongMaterial *phongMaterial);
    void sendRotation(QQuaternion q);

private:
    Ui::AttributeWidget *ui;
    int state;
};

#endif // ATTRIBUTEWIDGET_H
