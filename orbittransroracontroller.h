#ifndef ORBITTRANSFORMCONTROLLER_H
#define ORBITTRANSFORMCONTROLLER_H

#include <QObject>
#include <QMatrix4x4>
#include <QVector3D>

namespace Qt3DCore {
class QTransform;
}

class OrbitTransRoraController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Qt3DCore::QTransform* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QVector3D translation READ translation WRITE setTranslation NOTIFY translationChanged)
    Q_PROPERTY(QQuaternion roration READ roration WRITE setRoration NOTIFY rorationChanged)
    Q_PROPERTY(QMatrix4x4 matrix READ matrix WRITE setMatrix NOTIFY matrixChanged)
    //Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(float scale READ scale WRITE setScale NOTIFY scaleChanged)


public:
    OrbitTransRoraController(QObject *parent = nullptr);

    void setTarget(Qt3DCore::QTransform *target);
    Qt3DCore::QTransform *target() const;

    void setTranslation(QVector3D translation);
    QVector3D translation() const;

    void setRoration(QQuaternion roration);
    QQuaternion roration() const;

    void setMatrix(QMatrix4x4 matrix);
    QMatrix4x4 matrix() const;

//    void setColor(QColor color);
//    QColor color() const;

    void setScale(float scale);
    float scale() const;

signals:
    void targetChanged();
    void translationChanged();
    void rorationChanged();
    void scaleChanged();
    void matrixChanged();

protected:
    void updateTranslation();
    void updateRoration();
    void updateScale();
    void updateMatrix();


private:
    Qt3DCore::QTransform *m_target;
    QVector3D m_translation;
    QQuaternion m_roration;
    float m_scale;
    QMatrix4x4 m_matrix;
    QVector3D c_translation;
    QQuaternion c_roration;
    float c_scale;
    QMatrix4x4 c_matrix;
//    QVector3D centerPoint;
};


#endif // ORBITTRANSFORMCONTROLLER_H
