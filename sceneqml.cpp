#include "sceneqml.h"
#include "ui_sceneqml.h"
#include <QHBoxLayout>

SceneQml::SceneQml(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SceneQml)
{
    ui->setupUi(this);

    //view.setParent(this);
    view = new Qt3DExtras::Quick::Qt3DQuickWindow();
    view->setSource(QUrl("qrc:/qml/main.qml"));
    QHBoxLayout *layout = new QHBoxLayout(ui->quickWidget);
    QWidget *centerContainer = QWidget::createWindowContainer(view);
    layout->addWidget(centerContainer);
}

SceneQml::~SceneQml()
{
    delete ui;
}
