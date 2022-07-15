import QtQuick 2.12
import QtQuick.Window 2.12
import Qt3D.Core 2.14
import Qt3D.Render 2.14
import Qt3D.Extras 2.14
import Qt3D.Input 2.14


Entity{
    id: topplane

    PhongMaterial{
        id: meterial
    }

    Mesh{
        id: topplaneMesh
        source: "qrc:/obj/ball.obj"
    }

    components: [topplaneMesh,meterial]
}
