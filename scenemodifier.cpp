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

#include "scenemodifier.h"
//#include "orbittransformcontroller.h"
#include "orbittransroracontroller.h"

#include <QtCore/QDebug>
#include <math.h>
#include <QQuaternion>
#include <QPropertyAnimation>
#include <QVariant>


SceneModifier::SceneModifier(Qt3DCore::QEntity *rootEntity)
    : m_rootEntity(rootEntity)
{
    initMap();

    db = QSqlDatabase::database();


    QVector<QString>filelist;
    QString fileDir = "./model/teeth";
    QDir dirPath(fileDir);
    QList<QFileInfo> file(dirPath.entryInfoList());
    for(auto it = file.begin();it !=file.end();it++)
    {
        //qDebug()<<it->fileName();
        if(it->isFile())
        {
            filelist.push_back(it->fileName());
            //qDebug()<<filelist.back();
        }
    }    
    QString qrcDir = "qrc:/model/model/teeth";   

    for(int i=0;i<filelist.length();i++)
    {
        Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
//        QString color = QString("#%1%2").arg((i*7),2,16,QLatin1Char('0')).arg((255-i*7),2,16,QLatin1Char('0'))+"88";
        QSqlQuery query = QSqlQuery(db);
        QString str1 = QString("select color,x,y,z,xx,yy,zz from Color where name = '%1'")
                .arg(map[filelist[i]]);
//        qDebug()<<str1;
        query.exec(str1);
        query.next();
        QString color = query.value("color").toString();
        sphereMaterial->setDiffuse(QColor(color));
        sphereMaterial->setAmbient(QColor(13,13,13));
        //sphereMaterial->setSpecular(QColor("#f00"));

        Qt3DCore::QTransform * Transform = new Qt3DCore::QTransform();
        Transform->setScale(1.0f);
        //模型的缩放，我加载的模型比较大，这里要缩小显示
//        qDebug()<<query.value("x").toDouble()<<query.value("y").toDouble()<<query.value("z").toDouble()
//               <<query.value("xx").toDouble()<<query.value("yy").toDouble()<<query.value("zz").toDouble();
        centerPoint[i] = QVector3D(query.value("x").toDouble(),query.value("y").toDouble(),query.value("z").toDouble());
        rotationPoint[i] = QVector3D(query.value("xx").toDouble(),query.value("yy").toDouble(),query.value("zz").toDouble());
//        Transform->setTranslation(QVector3D(query.value("x").toDouble(),query.value("y").toDouble(),query.value("z").toDouble()));
//        Transform->setRotationX(query.value("xx").toDouble());
//        Transform->setRotationY(query.value("yy").toDouble());
//        Transform->setRotationZ(query.value("zz").toDouble());
//        qDebug()<<Transform->translation()<<Transform->rotation();
//        QMatrix4x4 form = Qt3DCore::QTransform::rotateAround(QVector3D(query.value("x").toDouble(),query.value("y").toDouble(),query.value("z").toDouble())
//                                           ,0,QVector3D(query.value("xx").toDouble(),query.value("yy").toDouble(),query.value("zz").toDouble()));
//        Transform->setMatrix(form);

        m_object[i] = new Qt3DCore::QEntity(rootEntity);
        mesh[i]= new Qt3DRender::QMesh();
        //qDebug()<<"." + fileDir + "/" +filelist[0];
        //qDebug()<<QString::number(i) + qrcDir + "/" +filelist[i];
        mesh[i]->setSource(QUrl(qrcDir + "/" +filelist[i]));
        m_object[i]->addComponent(sphereMaterial);
        m_object[i]->addComponent(Transform);
        m_object[i]->addComponent(mesh[i]);

        m_material[i] = sphereMaterial;
        m_transform[i] = Transform;
        object[i] = "牙齿";
        entityName.push_back(map[filelist[i]]);
        m_object[i]->setObjectName(map[filelist[i]]);

        QString str = QString("information : 打开文件:%1/%2").arg(fileDir).arg(filelist[i]);
        emit sendMessage(1,str);
    }

    filelist.clear();
    fileDir = "./model/bone";
    QDir boneDirPath(fileDir);
    QList<QFileInfo> files(boneDirPath.entryInfoList());
    for(auto it = files.begin();it !=files.end();it++)
    {
        //qDebug()<<it->fileName();
        if(it->isFile())
        {
            filelist.push_back(it->fileName());
            //qDebug()<<filelist.back();
        }
    }
    qrcDir = "qrc:/model/model/bone";
    int k = entityName.length();
    for(int i=0;i<filelist.length();i++)
    {
        Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
//        QString color = QString("#bea4%1").arg((i*50),2,16,QLatin1Char('0'));
        //qDebug()<<color;
        QSqlQuery query = QSqlQuery(db);
        QString str1 = QString("select color from Color where name = '%1'")
                .arg(map[filelist[i]]);
        query.exec(str1);
        query.next();
        QString color = query.value("color").toString();
        sphereMaterial->setDiffuse(QColor(color));

        Qt3DCore::QTransform * Transform = new Qt3DCore::QTransform();
        Transform->setScale(1.0f);
        //模型的缩放，我加载的模型比较大，这里要缩小显示
        Transform->setTranslation(QVector3D(0,0,0));

        m_object[i+k] = new Qt3DCore::QEntity(rootEntity);
        mesh[i+k]= new Qt3DRender::QMesh();
        //qDebug()<<"." + fileDir + "/" +filelist[0];
        //qDebug()<<qrcDir + "/" +filelist[i];
        mesh[i+k]->setSource(QUrl(qrcDir + "/" +filelist[i]));
        m_object[i+k]->addComponent(sphereMaterial);
        m_object[i+k]->addComponent(Transform);
        m_object[i+k]->addComponent(mesh[i+k]);

        m_material[i+k] = sphereMaterial;
        m_transform[i+k] = Transform;
        object[i+k] = "骨骼";
        entityName.push_back(map[filelist[i]]);
        m_object[i+k]->setObjectName(map[filelist[i]]);

        QString str = QString("information : 打开文件:%1/%2").arg(fileDir).arg(filelist[i]);
        emit sendMessage(1,str);
    }

    Qt3DCore::QTransform * Transform = new Qt3DCore::QTransform();
    Transform->setScale(1.0f);
    //模型的缩放，我加载的模型比较大，这里要缩小显示
    Transform->setTranslation(QVector3D(0,0,0));

    cone = new Qt3DCore::QEntity(rootEntity);
    coneMesh = new Qt3DExtras::QConeMesh();
    Qt3DExtras::QPhongMaterial *sphereMaterial = new Qt3DExtras::QPhongMaterial();
    sphereMaterial->setDiffuse(QColor(45,230,12));
    coneMesh->setLength(0);
    coneMesh->setBottomRadius(2.0);
    coneMesh->setTopRadius(1.0);
    cone->addComponent(coneMesh);
    cone->addComponent(sphereMaterial);
    cone->addComponent(Transform);

}

SceneModifier::~SceneModifier()
{
}

Qt3DCore::QEntity* SceneModifier::getEntity(int index)
{
    return m_object[index];
}

void SceneModifier::setEntity(int index, Qt3DCore::QEntity *input)
{
    m_object[index] = input;
}

Qt3DCore::QTransform *SceneModifier::getTransform(int index)
{
    Qt3DCore::QTransform* newform = new Qt3DCore::QTransform();
    newform->setTranslation(m_transform[index]->translation()+centerPoint[index]);
    return newform;
}

void SceneModifier::setTransform(int index, Qt3DCore::QTransform *input)
{
    input->setTranslation(input->translation()-centerPoint[index]);
    OrbitTransRoraController *controller = new OrbitTransRoraController(m_transform[index]);
    controller->setTarget(m_transform[index]);
    QPropertyAnimation *animation_translation = new QPropertyAnimation(m_transform[index]);
    animation_translation->setTargetObject(controller);
    animation_translation->setPropertyName("translation");
    animation_translation->setStartValue(m_transform[index]->translation());
//    qDebug()<<m_transform[index]->matrix();
    Qt3DCore::QTransform* transform = new Qt3DCore::QTransform();
    input->setTranslation(input->translation()-m_transform[index]->translation());
    transform->setMatrix(input->matrix()*m_transform[index]->matrix());
    animation_translation->setEndValue(transform->translation());
    animation_translation->setDuration(3000);
    animation_translation->setLoopCount(1);
    animation_translation->start();
    delete transform;

//    QPropertyAnimation *animation_translation = new QPropertyAnimation(m_transform[index]);
//    animation_translation->setTargetObject(controller);
//    animation_translation->setPropertyName("matrix");
//    animation_translation->setStartValue(m_transform[index]->matrix());
////    qDebug()<<m_transform[index]->matrix();
////    qDebug()<<m_transform[index]->translation();
//    Qt3DCore::QTransform* matrix = new Qt3DCore::QTransform();
//    matrix->setMatrix(input->matrix()*m_transform[index]->matrix());
////    qDebug()<<matrix->matrix();
////    qDebug()<<matrix->translation();
//    animation_translation->setEndValue(matrix->matrix());
//    animation_translation->setDuration(3000);
//    animation_translation->setLoopCount(1);
//    animation_translation->start();
//    delete matrix;


}

void SceneModifier::setRotation(int index,QQuaternion q)
{
    qDebug()<<"q"<<q;
    QMatrix4x4 matrix = Qt3DCore::QTransform::rotateAround(centerPoint[index],q.scalar(),q.vector());
    Qt3DCore::QTransform* input = new Qt3DCore::QTransform();
    input->setMatrix(matrix);
    qDebug()<<"input"<<input->rotation();

    input->setMatrix(m_transform[index]->matrix()*matrix);

    OrbitTransRoraController *controller = new OrbitTransRoraController(m_transform[index]);
    controller->setTarget(m_transform[index]);
    QPropertyAnimation *animation_roration = new QPropertyAnimation(m_transform[index]);
    animation_roration->setTargetObject(controller);
    animation_roration->setPropertyName("roration");
    //qDebug()<<"old"<<m_transform[index]->rotation();
    animation_roration->setStartValue(m_transform[index]->rotation());
    animation_roration->setEndValue(input->rotation());
    animation_roration->setDuration(3000);
    animation_roration->setLoopCount(1);
    animation_roration->start();

    delete input;

//    m_transform[index]->setMatrix(input);
////    m_transform[index]->setRotation(q);
//    m_object[index]->addComponent(m_transform[index]);
}

Qt3DExtras::QPhongMaterial *SceneModifier::getMaterial(int index)
{
    return m_material[index];
}

void SceneModifier::setMaterial(int index, Qt3DExtras::QPhongMaterial *input)
{
    m_material[index] = input;
    m_object[index]->addComponent(input);
    QRgb mRgb = qRgb(input->diffuse().red(),input->diffuse().green(),input->diffuse().blue());
    QString mRgbStr="#";
    mRgbStr += QString::number(mRgb,16);
    QSqlQuery query = QSqlQuery(db);
    QString str1 = QString("update Color set color = '%1' where name = '%2'")
            .arg(mRgbStr).arg(entityName[index]);
    query.exec(str1);
}

void SceneModifier::setScale(int index, float scale)
{
    //m_transform[index]->setScale(scale);
    //m_object[index]->addComponent(m_transform[index]);

    OrbitTransRoraController *controller = new OrbitTransRoraController(m_transform[index]);
    controller->setTarget(m_transform[index]);
    QPropertyAnimation *animation = new QPropertyAnimation(m_transform[index]);
    animation->setTargetObject(controller);
    animation->setPropertyName("scale");
    animation->setStartValue(1);
    animation->setKeyValueAt(0.5,scale);
    animation->setEndValue(1);
    animation->setDuration(1000);
    animation->setLoopCount(1);
    animation->start();

    m_object[index]->addComponent(m_transform[index]);
}

QString SceneModifier::getObject(int index)
{
    return object[index];
}

void SceneModifier::setObject(int index, QString objectname)
{
    object[index] = objectname;
}

int SceneModifier::getNumber()
{
    //qDebug()<<entityName.length();
    return entityName.length();
}

void SceneModifier::setLength(float length)
{
    coneMesh->setLength(length);
}

void SceneModifier::setBottom(float radius)
{
    coneMesh->setBottomRadius(radius);
}

void SceneModifier::setTop(float radius)
{
    coneMesh->setTopRadius(radius);
}

void SceneModifier::setTransform(Qt3DCore::QTransform *transform)
{
    cone->addComponent(transform);
}

void SceneModifier::initMap()
{
    map.insert("Right_maxillary_cusp.obj","右上颌尖牙");
    map.insert("Right_maxillary_first_premolar.obj","右上颌第一前磨牙");
    map.insert("Right_upper_second_premolar.obj","右上颌第二前磨牙");
    map.insert("Right_maxillary_first_molar.obj","右上颌第一磨牙");
    map.insert("Right_maxillary_second_molar.obj","右上颌第二磨牙");
    map.insert("Right_upper_third_molar.obj","右上颌第三磨牙");
    map.insert("Left_maxillary_central_incisor.obj","左上颌中切牙");
    map.insert("Left_maxillary_lateral_incisor.obj","左上颌侧切牙");
    map.insert("Left_maxillary_cusp.obj","左上颌尖牙");
    map.insert("Left_maxillary_first_premolar.obj","左上颌第一前磨牙");
    map.insert("Left_maxillary_second_premolar.obj","左上颌第二前磨牙");
    map.insert("Left_maxillary_first_molar.obj","左上颌第一磨牙");
    map.insert("Left_maxillary_second_molar.obj","左上颌第二磨牙");
    map.insert("Left_upper_third_molar.obj","左上颌第三磨牙");
    map.insert("Left_mandibular_central_incisor.obj","左下颌中切牙");
    map.insert("Left_mandibular_lateral_incisor.obj","左下颌侧切牙");
    map.insert("Left_mandibular_cusp.obj","左下颌尖牙");
    map.insert("Left_mandibular_first_premolar.obj","左下颌第一前磨牙");
    map.insert("Left_mandibular_second_premolar.obj","左下颌第二前磨牙");
    map.insert("Left_mandibular_first_molar.obj","左下颌第一磨牙");
    map.insert("Left_mandibular_second_molar.obj","左下颌第二磨牙");
    map.insert("Left_mandibular_third_molar.obj","左下颌第三磨牙");
    map.insert("Right_mandibular_central_incisor.obj","右下颌中切牙");
    map.insert("Right_mandibular_lateral_incisor.obj","右下颌侧切牙");
    map.insert("Right_mandibular_cusp.obj","右下颌尖牙");
    map.insert("Right_mandibular_first_premolar.obj","右下颌第一前磨牙");
    map.insert("Right_mandibular_second_premolar.obj","右下颌第二前磨牙");
    map.insert("Right_mandibular_first_molar.obj","右下颌第一磨牙");
    map.insert("Right_mandibular_second_molar.obj","右下颌第二磨牙");
    map.insert("Third_molar_of_the_right_lower_jaw.obj","右下颌第三磨牙");
    map.insert("Right_maxillary_central_incisor.obj","右上颌中切牙");
    map.insert("Right_lateral_maxillary_incisor.obj","右上颌侧切牙");
    map.insert("Lower_jaw_bone.obj","下颚骨");
    map.insert("Maxillary_sinus.obj","上颌窦");
    map.insert("The_left_side_of_the_temporal_bone.obj","左颞骨");
    map.insert("The_right_side_of_the_temporal_bone.obj","右颞骨");
    map.insert("Upper_jaw_bone.obj","上颌骨");
}

//! [4]
