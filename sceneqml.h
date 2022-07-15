#ifndef SCENEQML_H
#define SCENEQML_H

#include <QWidget>
#include <Qt3DQuickExtras/qt3dquickwindow.h>
#include <QQuickView>
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

namespace Ui {
class SceneQml;
}

class SceneQml : public QWidget
{
    Q_OBJECT

public:
    explicit SceneQml(QWidget *parent = nullptr);
    ~SceneQml();

private:
    Ui::SceneQml *ui;

    Qt3DExtras::Quick::Qt3DQuickWindow *view; //普通2D视图
    Qt3DExtras::Qt3DWindow *views;

};

#endif // SCENEQML_H
