#include "scene.h"
#include "ui_scene.h"

Scene::Scene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Scene)
{
    ui->setupUi(this);

    centerView = new Qt3DExtras::Qt3DWindow();
    centerView->defaultFrameGraph()->setClearColor(QColor(QRgb(0x594d4f)));

    QWidget *centerContainer = QWidget::createWindowContainer(centerView);
    centerContainer->setMinimumSize(QSize(200, 100));
    centerContainer->setMaximumSize(centerView->screen()->size());

    QHBoxLayout *centerLayout = new QHBoxLayout(this);
    centerLayout->addWidget(centerContainer);

    // Root entity
    centerEntity = new Qt3DCore::QEntity();
    // Camera
    centerCameraEntity = centerView->camera();
    centerCameraEntity->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    centerCameraEntity->setPosition(QVector3D(0, 135, -5));
    centerCameraEntity->setUpVector(QVector3D(0, 0, 1));
    centerCameraEntity->setViewCenter(QVector3D(0, 0, 0));
    connect(centerCameraEntity,&Qt3DRender::QCamera::positionChanged,this,&Scene::dealPositionChanged);
    connect(centerCameraEntity,&Qt3DRender::QCamera::viewVectorChanged,this,&Scene::dealViewVectorChanged);
    //light
    centerlightEntity = new Qt3DCore::QEntity(centerEntity);
    Qt3DRender::QPointLight *centerlight = new Qt3DRender::QPointLight(centerlightEntity);
    centerlight->setColor("white");
    centerlight->setIntensity(1);
    centerlightEntity->addComponent(centerlight);
    Qt3DCore::QTransform *centerlightTransform = new Qt3DCore::QTransform(centerlightEntity);
    centerlightTransform->setTranslation(centerCameraEntity->position());
    centerlightEntity->addComponent(centerlightTransform);

    // For camera controls
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(centerEntity);
    camController->setCamera(centerCameraEntity);

    // Scenemodifier
    modifier = new SceneModifier(centerEntity);
    connect(modifier,&SceneModifier::sendMessage,this,&Scene::dealSendMessage);

    centerView->setRootEntity(centerEntity);
}

Scene::~Scene()
{
    //    delete topView;
    //    delete sideView;
    //    delete frontView;
    //    delete centerView;
    delete ui;
}

Qt3DCore::QEntity *Scene::getEntity(int index)
{
    return modifier->getEntity(index);
}

void Scene::setEntity(int index, Qt3DCore::QEntity *input)
{
    modifier->setEntity(index,input);
}

Qt3DCore::QTransform *Scene::getTransform(int index)
{
    return modifier->getTransform(index);
}

void Scene::setTransform(int index, Qt3DCore::QTransform *input)
{
    modifier->setTransform(index,input);
}

void Scene::setRotation(int index, QQuaternion q)
{
    modifier->setRotation(index,q);
}

Qt3DExtras::QPhongMaterial *Scene::getMaterial(int index)
{
    return modifier->getMaterial(index);
}

void Scene::setMaterial(int index, Qt3DExtras::QPhongMaterial *input)
{
    modifier->setMaterial(index,input);
}

void Scene::setScale(int index, float scale)
{
    modifier->setScale(index,scale);
}

QString Scene::getObject(int index)
{
    return modifier->getObject(index);
}

void Scene::setObject(int index, QString objectname)
{
    modifier->setObject(index,objectname);
}

int Scene::getObjectNumber()
{
    return modifier->getNumber();
}

void Scene::setPosition(QVector3D point)
{
    centerCameraEntity->setPosition(point);
}

void Scene::setUpVector(QVector3D point)
{
    centerCameraEntity->setUpVector(point);
}

void Scene::setViewCenter(QVector3D point)
{
    centerCameraEntity->setViewCenter(point);
}

QVector3D Scene::getPosition()
{
    return centerCameraEntity->position();
}

QVector3D Scene::getUpVector()
{
    return centerCameraEntity->upVector();
}

QVector3D Scene::getViewCenter()
{
    return centerCameraEntity->viewCenter();
}

SceneModifier *Scene::getModifier()
{
    return modifier;
}

void Scene::dealPositionChanged(const QVector3D &position)
{
    Qt3DCore::QTransform *centerlightTransform = new Qt3DCore::QTransform(centerlightEntity);
    centerlightTransform->setTranslation(centerCameraEntity->position());
    centerlightEntity->addComponent(centerlightTransform);
    emit positionChanged(position);
}

void Scene::dealViewVectorChanged(const QVector3D &position)
{
    emit viewVectorChanged(position);
}

void Scene::dealSendMessage(int i, QString str)
{
    emit sendMessage(i,str);
}
