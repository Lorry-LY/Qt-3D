/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SCENEMODIFIER_H
#define SCENEMODIFIER_H

#include <QtCore/QObject>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <Qt3DCore/qentity.h>
#include <Qt3DCore/qtransform.h>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DExtras/QCuboidMesh>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QSphereMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPhongAlphaMaterial>
#include <Qt3DAnimation>

class SceneModifier : public QObject
{
    Q_OBJECT

public:
    explicit SceneModifier(Qt3DCore::QEntity *rootEntity);
    ~SceneModifier();

public slots:
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

    int getNumber();

    void setLength(float length);
    void setBottom(float radius);
    void setTop(float radius);
    void setTransform(Qt3DCore::QTransform* transform);

//    void getCenterPoint();

signals:
    void sendMessage(int,QString);

private:
    void initMap();

private:
    Qt3DCore::QEntity *m_rootEntity;
    Qt3DCore::QEntity *m_object[37];
    Qt3DRender::QMesh *mesh[37];
    QString object[37];
    QVector<QString>entityName;
    Qt3DCore::QTransform *m_transform[37];
    Qt3DExtras::QPhongMaterial *m_material[37];
    QSqlDatabase db;
    QMap<QString,QString>map;

    QVector3D centerPoint[32];
    QVector3D rotationPoint[32];

    Qt3DCore::QEntity* cone;
    Qt3DExtras::QConeMesh* coneMesh;


};

#endif // SCENEMODIFIER_H

