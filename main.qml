import QtQuick 2.0
import QtQuick.Scene3D 2.0

Item {

    Rectangle {
        id: scene
        anchors.fill: parent
        anchors.margins: 0
        color: "transparent"

        Scene3D {
            id: scene3d
            anchors.fill: parent
            anchors.margins: 5
            focus: true
            aspects: ["input", "logic"]
            cameraAspectRatioMode: Scene3D.AutomaticAspectRatio
            entity: AnimatedEntity {}
        }
    }
}
