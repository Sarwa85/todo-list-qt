import QtQuick 2.0
import pl.osla.todo 1.0
import QtQuick.Controls 2.0

Rectangle {
    id: mainItem

    color: "white"

    FileRepository {
        id: dataRepo
        name: "todo-base"
    }

    TaskModel {
        id: dataModel
    }

    Controler {
        id: dataControler
        model: dataModel
        repository: dataRepo
    }

    Component.onCompleted: {
        dataControler.init()
        dataControler.asyncTasks()
    }

    StackView {
        id: stack

        anchors.fill: parent

        initialItem: listComponent
    }

    Component {
        id: listComponent

        ListPage {
            id: listPage

            model: dataModel
            control: dataControler

            Connections {
                target: listPage

                function onShowAddPage() {
                    stack.push(editComponent)
                }
            }
        }
    }

    Component {
        id: editComponent

        EditPage {
            id: editPage

            Connections {
                target: editPage

                function onNeedPop() {
                    stack.pop()
                }
            }

        }
    }
}
