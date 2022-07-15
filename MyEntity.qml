import QtQuick 2.0
import Qt3D.Render 2.14
import Qt3D.Extras 2.14
import Qt3D.Core 2.14
import QtQuick 2.0 as QQ2

import QtQuick3D 1.14 as Q3D


Entity{

    PhongMaterial {
        id: material
        ambient: Qt.rgba( 0.02, 0.02, 0.02, 1.0 )
        diffuse: Qt.rgba( 0.8, 0.0, 0.0, 1.0 )
        specular: Qt.rgba( 0.8, 0.0, 0.0, 1.0 )
        shininess: 1.0
    }

    Mesh {
        id: torusMesh
        source: "qrc:/model/model/bone/Lower_jaw_bone.obj"
    }

    Transform {
        id: torusTransform
        translation: Qt.vector3d(0, 0, 0)
        //rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 45)
    }

    Entity {
        id: torusEntity
        components: [ torusMesh, material, torusTransform ]
    }

    //    PhongMaterial {
    //        id: material2
    //    }

    //    Transform {
    //        id: torusTransform2
    //        scale3D: Qt.vector3d(1.5, 1, 0.5)
    //        rotation: fromAxisAndAngle(Qt.vector3d(1, 0, 0), 45)
    //    }

    //    Mesh{
    //        id: topplaneMesh
    //        source: "qrc:/obj/ball.obj"
    //    }

    //    Entity{
    //        id: topplane
    //        components: [topplaneMesh,material2,torusTransform2 ]
    //    }

    //    SphereMesh {
    //        id: sphereMesh
    //        radius: 3
    //    }

    //    Transform {
    //        id: sphereTransform
    //        property real userAngle: 0.0
    //        matrix: {
    //            var m = Qt.matrix4x4();
    //            m.rotate(userAngle, Qt.vector3d(0, 1, 0))
    //            m.translate(Qt.vector3d(20, 0, 0));
    //            return m;
    //        }
    //    }

    //    QQ2.NumberAnimation {
    //        target: sphereTransform
    //        property: "userAngle"
    //        duration: 10000
    //        from: 0
    //        to: 360

    //        loops: QQ2.Animation.Infinite
    //        running: true
    //    }

    //    Entity {
    //        id: sphereEntity
    //        components: [ sphereMesh, material, sphereTransform ]
    //    }

}

