import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.2
import Components 1.0
import ".."
import "../widgets"

PanelBase {
    id: root
    panelContents: Item {
        anchors.fill: parent

        Row {
            anchors.centerIn: parent
            spacing: Theme.buttonSize
            ImageButton {
                id: circleExclusion
                source: "qrc:/icons/ico-circle.svg"
                anchors.verticalCenter: parent.verticalCenter
                label: qsTr("Circle")
                textPosition: "below"
                textColor: Theme.defaultFontColor
                onClicked: targetDrone.currentExclusionShape = DroneBase.ELLIPSE
                checkable: true
                checked: root.droneValid() ? (targetDrone.currentExclusionShape === DroneBase.ELLIPSE) : false
            }
            ImageButton {
                id: rectExclusion
                source: "qrc:/icons/ico-rectangle.svg"
                anchors.verticalCenter: parent.verticalCenter
                label: qsTr("Rectangle")
                textPosition: "below"
                textColor: Theme.defaultFontColor
                onClicked: targetDrone.currentExclusionShape = DroneBase.RECTANGLE
                checkable: true
                checked: root.droneValid() ? (targetDrone.currentExclusionShape === DroneBase.RECTANGLE) : false
            }
            ImageButton {
                id: triangleExclusion
                source: "qrc:/icons/ico-triangle.svg"
                anchors.verticalCenter: parent.verticalCenter
                label: qsTr("Triangle")
                textPosition: "below"
                textColor: Theme.defaultFontColor
                onClicked: targetDrone.currentExclusionShape = DroneBase.TRIANGLE
                checkable: true
                checked: root.droneValid() ? (targetDrone.currentExclusionShape === DroneBase.TRIANGLE) : false
            }
        }
    }
}
