import QtQuick 2.15
import QtQuick.Window 2.14
import QtQuick3D
import QtQuick.Controls 2.1
import Qt3D.Extras 2.15

Item {
    anchors.fill: parent

    // Properties for cubes
    property real x1: -200
    property real y1: -150
    property real z1: -100
    property real x2: 300
    property real y2: 200
    property real z2: 400
    property string cubeColor: "orange"

    View3D {
        id: view
        anchors.fill: parent
        camera: camera
        renderMode: View3D.Overlay

        PerspectiveCamera {
            id: camera
            position: Qt.vector3d(0, 200, 300)
            fieldOfView: 90
            eulerRotation.x: -30
        }

        DirectionalLight {
            eulerRotation.x: -30
            eulerRotation.y: -45
        }

        Model {
            // Calculate center position
            property real centerX: (x1 + x2) / 2
            property real centerY: (y1 + y2) / 2
            property real centerZ: (z1 + z2) / 2

            // Calculate scale dimensions
            property real scaleX: Math.abs(x2 - x1)
            property real scaleY: Math.abs(y2 - y1)
            property real scaleZ: Math.abs(z2 - z1)

            id: cube
            visible: true
            position: Qt.vector3d(centerX, centerY, centerZ)
            scale: Qt.vector3d(scaleX / 100, scaleY / 100, scaleZ / 100)
            source: "#Cube"
            materials: [
                DefaultMaterial {
                    diffuseColor: cubeColor
                }
            ]
        }

        // Ground plane for reference
        Model {
            id: grid
            position: Qt.vector3d(0, -cube.scaleY / 2 - 1, 0)
            materials: DefaultMaterial {
                diffuseColor: "white"
            }
        }
    }
}
