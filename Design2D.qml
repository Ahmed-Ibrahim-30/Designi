import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    anchors.fill: parent

    Button{
        text: "Next"
        width: 50
        height: 50
        x : 10
        y : 10
        onClicked: {
            qmlDrawing.getNextSolution()
            canvas.requestPaint();
        }
    }

    Button{
        text: "Prev"
        width: 50
        height: 50
        x : 10
        y : 80
        onClicked: {
            qmlDrawing.getPrevSolution()
            canvas.requestPaint();
        }
    }

    // Create the Canvas to draw on
    Canvas {
        id: canvas
        anchors.fill: parent

        // Drawing logic inside onPaint handler
        onPaint: {
            var ctx = canvas.getContext("2d");
            ctx.clearRect(0, 0, canvas.width, canvas.height);

            var rooms = qmlDrawing.roomRects;

            // Draw each room in the design
            for (var i = 0; i < rooms.length; i++) {
                var rect = rooms[i];
                var roomId =  rooms[i].roomId;
                // Set the stroke width (optional)
                ctx.lineWidth = 5;
                ctx.strokeStyle = 'black'; // Border color
                ctx.fillStyle = 'lightblue'; // Fill color

                // Draw the rectangle boundary (stroke) first
                ctx.strokeRect(rect.x, rect.y, rect.width, rect.height);

                // Fill the rectangle with the chosen color
                ctx.fillRect(rect.x, rect.y, rect.width, rect.height);

                // Draw the room ID in the center of the rectangle
                ctx.fillStyle = 'black'; // Text color
                ctx.font = '20px Arial'; // Font size and family
                ctx.textAlign = 'center'; // Center the text horizontally
                ctx.textBaseline = 'middle'; // Center the text vertically

                // Calculate the center of the rectangle for text placement
                var centerX = rect.x + rect.width / 2;
                var centerY = rect.y + rect.height / 2;

                // Draw the room ID at the center of the rectangle
                ctx.fillText(roomId, centerX, centerY);

            }
        }
    }
}
