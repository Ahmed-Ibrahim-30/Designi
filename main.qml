import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 1920
    height: 820
    // color:"#252628"

    color:"green"
    title: "Design Rooms"

    property bool vis1: true
    property bool vis2: false

    Button{
        width : 20
        height : 20
        text: "switch"
        x:0
        y:0
        onClicked: {
            vis1 = !vis1
            vis2 = !vis2
        }
    }

    Design3D{
        visible: vis1
    }

    Design2D{
        visible: vis2
    }
}
