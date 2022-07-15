#include "orbittransroracontroller.h"

#include <Qt3DCore/qtransform.h>

OrbitTransRoraController::OrbitTransRoraController(QObject *parent)
    : QObject(parent)
    , m_target(nullptr)
    , m_translation()
    , m_roration()
    , m_scale(1)
    , m_matrix()
    , c_translation(QVector3D(0,0,0))
    , c_roration(QQuaternion())
    , c_scale(1)
    , c_matrix(QMatrix4x4())
{
}

void OrbitTransRoraController::setTarget(Qt3DCore::QTransform *target)
{
    if (m_target != target) {
        m_target = target;
        emit targetChanged();
    }
}

Qt3DCore::QTransform *OrbitTransRoraController::target() const
{
    return m_target;
}

void OrbitTransRoraController::setTranslation(QVector3D translation)
{
    if (m_translation != translation) {
        m_translation = translation;
        updateTranslation();
        emit translationChanged();
    }
}

QVector3D OrbitTransRoraController::translation() const
{
    return m_translation;
}

void OrbitTransRoraController::setRoration(QQuaternion roration)
{
    if (m_roration != roration) {
        m_roration = roration;
        updateRoration();
        emit rorationChanged();
    }
}

QQuaternion OrbitTransRoraController::roration() const
{
    return m_roration;
}

void OrbitTransRoraController::setMatrix(QMatrix4x4 matrix)
{
    if(m_matrix != matrix){
        m_matrix = matrix;
        updateMatrix();
        emit matrixChanged();
    }
}

QMatrix4x4 OrbitTransRoraController::matrix() const
{
    return m_matrix;
}

void OrbitTransRoraController::setScale(float scale)
{
    if(!qFuzzyCompare(m_scale,scale))
    {
        m_scale = scale;
        updateScale();
        emit scaleChanged();
    }
}

float OrbitTransRoraController::scale() const
{
    return m_scale;
}

void OrbitTransRoraController::updateTranslation()
{
    c_translation = m_translation;
    m_target->setTranslation(c_translation);
}

void OrbitTransRoraController::updateRoration()
{
    c_roration = m_roration;
    m_target->setRotation(m_roration);
}

void OrbitTransRoraController::updateScale()
{
    c_scale = m_scale;
    m_target->setScale(c_scale);
}

void OrbitTransRoraController::updateMatrix()
{
    qDebug()<<c_matrix;
    c_matrix = m_matrix;
    m_target->setMatrix(c_matrix);
}

