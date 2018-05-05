import QtQuick 2.5
import QtQuick.Controls 1.4
import "../../widgets"
import "../.."

Item {
    id: loginPage
    opacity: 1
    visible: opacity > 0

    // Main container
    Rectangle {
        id: mainContainer
        width: parent.width
        height: parent.height-2*Theme.toolBarHeight
        anchors.centerIn: parent
        color: "transparent"
        radius: 8
        border.color: "white"

        Item {
            anchors.fill: parent
            anchors.margins: 16

            // Maps
            Item {
                id: mapGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: parent.top
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Maps")
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.mapPath = selectedFolder
                }
            }

            // Mission
            Item {
                id: missionGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: mapGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Mission")
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.missionPath = selectedFolder
                }
            }

            // Logs
            Item {
                id: logGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: missionGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Logs")
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.logPath = selectedFolder
                }
            }

            // Alerts
            Item {
                id: alertGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: logGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Alerts")
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.alertPath = selectedFolder
                }
            }

            // Gallery
            Item {
                id: galleryGroup
                width: parent.width
                height: Theme.toolBarHeight
                anchors.top: alertGroup.bottom
                anchors.topMargin: Theme.toolBarHeight
                anchors.horizontalCenter: parent.horizontalCenter

                FileSelectorWidget {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    title: qsTr("Gallery")
                    onSelectedFolderChanged: MASTERCONTROLLER.settingController.galleryPath = selectedFolder
                }
            }
        }
    }
}
