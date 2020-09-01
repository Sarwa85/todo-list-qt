import QtQuick 2.0
import QtQuick.Layouts 1.0

Item {
    id: delegate

    property int compactHeight: 20
    property int expandHeight: 60


    Rectangle {
        anchors.fill: parent
        anchors.margins: 1
        color: "transparent"
    }

    clip: true

//    Behavior on height {
//        NumberAnimation {
//            duration: 300
//            easing.type: Easing.OutExpo
//        }
//    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Text {
            id: titleText

            Layout.fillHeight: true
            Layout.fillWidth: true

            text: roleTitle
            font.pixelSize: compactHeight
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        Text {
            id: descText

            Layout.fillHeight: true
            Layout.fillWidth: true

            text: roleText
            font.pixelSize: compactHeight
            fontSizeMode: Text.Fit
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            visible: opacity > 0

//            Behavior on opacity {
//                NumberAnimation {
//                    duration: 100
//                }
//            }
        }
    }

    Rectangle {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: 1
        color: "black"
    }
}
