import QtQuick
import QtQuick.Controls.Basic

Item {
    id: root

    Button {
        id: button

        anchors.centerIn: root

        width: 320
        height: 76

        // Disable effects.
        flat: true

        contentItem: Image {
            anchors.fill: button

            width: 320
            height: 76

            source: "/images/develer.svg"
        }

        background: Rectangle {
            anchors.fill: parent
            color: "transparent"
        }

        onClicked: applicationModel.rotating = !applicationModel.rotating
    }

    // Rotate the image.
    RotationAnimator {
        target: button

        from: 0
        to: 360
        loops: Animation.Infinite

        duration: 2000
        running: applicationModel.rotating

        // Reset the image orientation to 0 when the automation is stopped.
        onStopped: button.rotation = 0
    }
}
