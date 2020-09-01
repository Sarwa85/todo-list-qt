import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.0

Item {
    signal needPop()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: Style.margin

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }

        RowLayout {
            Button {
                text: "Wstecz"
                onClicked: needPop()
            }
        }
    }
}
