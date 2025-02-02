import QtQuick 2.15

Item {
    anchors.fill: parent

    Repeater{
        model: qmlWallDrawing.wallCount()
        MyCube{
            x1: qmlWallDrawing.curWalls()[index].x1
            y1: qmlWallDrawing.curWalls()[index].y1
            z1: qmlWallDrawing.curWalls()[index].z1
            x2: qmlWallDrawing.curWalls()[index].x2
            y2: qmlWallDrawing.curWalls()[index].y2
            z2: qmlWallDrawing.curWalls()[index].z2
            cubeColor : qmlWallDrawing.curWalls()[index].wallColor
        }
    }
}
