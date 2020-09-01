import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0
import pl.osla.todo 1.0

Item {
    property Controler control

    property alias model: view.model

    signal showAddPage()
    signal showEditPage()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Style.margin

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true

            border.width: 1
            border.color: "black"

            ListView {
                id: view

                anchors.fill: parent

                highlightFollowsCurrentItem : true
                boundsBehavior: Flickable.StopAtBounds

                delegate: TaskDelegate {
                    height: 60
                    width: view.width

                    MouseArea {
                        anchors.fill: parent
                        onClicked: view.currentIndex = index
                    }
                }

                highlight: Rectangle {
                    color: "navy"
                    opacity: 0.2
                }
            }
        }


        RowLayout {
            Button {
                text: "Dodaj"
                onClicked: showAddPage()
            }
            Button {
                text: "Edytuj"
                onClicked: showEditPage()
            }
            Button {
                text: "Usuń"
                onClicked: control.asyncRemoveRow(view.currentIndex)
            }
            Button {
                text: "Odśwież"
                onClicked: control.asyncTasks()
            }
            Item {
                Layout.fillWidth: true
            }
        }
    }

}
