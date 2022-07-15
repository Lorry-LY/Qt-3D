import Qt3D.Core 2.0
import Qt3D.Render 2.14
import Qt3D.Input 2.0
import Qt3D.Extras 2.0
import Qt3D.Render 2.14

import QtQuick.Controls 1.4
import QtQuick 2.14 as QQ2
import QtQuick.Layouts 1.14
import QtQuick3D 1.14 as Q3D


Entity {
    id: sceneRoot

    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        nearPlane : 0.1
        farPlane : 1000.0
        position: Qt.vector3d( 0.0, 130, 0 )
        upVector: Qt.vector3d( 0, 1, 1 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }

    FirstPersonCameraController { camera: camera }

    components: [
        RenderSettings{
            activeFrameGraph : RenderSurfaceSelector {
                Viewport {
                    id: mainViewport
                    normalizedRect: Qt.rect(0, 0, 1, 1)
                    ClearBuffers {
                        buffers: ClearBuffers.ColorDepthBuffer
                        clearColor: "steelblue"
                    }

                    Viewport {
                        id: topLeftViewport
                        normalizedRect: Qt.rect(0, 0.2, 0.6, 0.6)

                        CameraSelector {
                            id: cameraSelectorTopLeftViewport
                            camera: camera
                        }

                    }
                    Viewport {
                        id: topRightViewport
                        normalizedRect: Qt.rect(0.65, 0, 0.3, 0.3)
                        CameraSelector {
                            id: cameraSelectorTopRightViewport
                            camera:Camera {
                                id: camerafront
                                projectionType: CameraLens.PerspectiveProjection
                                fieldOfView: 45
                                nearPlane : 0.1
                                farPlane : 1000.0
                                position: Qt.vector3d( 0.0, 135, 0.0 )
                                upVector: Qt.vector3d( 0.0, 0.0, 1 )
                                viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
                            }
                        }
                    }
                    Viewport {
                        id: bottomLeftViewport
                        normalizedRect: Qt.rect(0.65, 0.35, 0.3, 0.3)
                        CameraSelector {
                            id: cameraSelectorBottomLeftViewport
                            camera: Camera {
                                id: cameraleft
                                projectionType: CameraLens.PerspectiveProjection
                                fieldOfView: 45
                                nearPlane : 0.1
                                farPlane : 1000.0
                                position: Qt.vector3d( 90.0, 30, 0.0 )
                                upVector: Qt.vector3d( 0.0, 1, 0 )
                                viewCenter: Qt.vector3d( 0.0, 30, 0.0 )
                            }
                        }

                        //                        Q3D.PointLight{
                        //                            id:lightLeft
                        //                            color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                        //                            position: cameraleft.position
                        //                            rotation: Qt.vector3d(135, 50, 100)
                        //                        }

                    }
                    Viewport {
                        id: bottomRightViewport
                        normalizedRect: Qt.rect(0.65, 0.7, 0.3, 0.3)
                        CameraSelector {
                            id: cameraSelectorBottomRightViewport
                            camera:Camera {
                                id: cameratop
                                projectionType: CameraLens.PerspectiveProjection
                                fieldOfView: 45
                                nearPlane : 0.1
                                farPlane : 1000.0
                                position: Qt.vector3d( 0.0, 30, 100 )
                                upVector: Qt.vector3d( 1.0, 0.0, 0.0 )
                                viewCenter: Qt.vector3d( 0.0, 30, 0.0 )
                            }
                        }

                        //                        Q3D.PointLight{
                        //                            id:lightTop
                        //                            color: Qt.rgba(1.0, 1.0, 1.0, 1.0)
                        //                            position: cameratop.position
                        //                            rotation: Qt.vector3d(135, 50, 100)
                        //
                    }
                }
            }
        },
        InputSetting { }
    ]



    MyEntity {}

}
