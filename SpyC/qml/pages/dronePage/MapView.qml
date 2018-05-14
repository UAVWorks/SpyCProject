import QtQuick 2.5
import QtQuick.Layouts 1.3
import QtPositioning 5.6
import QtLocation 5.6
import QtQuick.Controls 1.4
import Components 1.0
import "../.."
import "../../toolbars"

// Main map
Map {
    id: mapView
    plugin: mapPlugin
    zoomLevel: 10
    property variant targetDrone
    property bool mapGestureEnabled: true
    gesture.enabled: mapGestureEnabled

    // Map plugin
    Plugin {
        id: mapPlugin
        name: "osm"
    }

    // Draw mission plan way points
    MapItemView {
        id: missionPlanWayPoints
        model: targetDrone.missionPlanModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: Theme.missionPlanColor
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                        {
                            targetDrone.removeCoordinateFromMissionPlanAtIndex(index)
                        }
                    }
                    onPressed: {
                        mapGestureEnabled = false
                        targetDrone.missionPlanModel.currentPointIndex = index
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            targetDrone.setMissionPlanPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        mapGestureEnabled = true
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw mission plan
    MapPolyline {
        id: missionPlanPoly
        line.width: 3
        line.color: Theme.missionPlanColor
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<targetDrone.missionPlanModel.path.size(); i++)
                lines[i] = targetDrone.missionPlanModel.path.coordinateAt(i)
            missionPlanPoly.path = lines
        }
        function onDataChanged()
        {
            if (targetDrone.missionPlanModel.path.size() === 0)
            {
                missionPlanPoly.visible = false
                var lines = []
                missionPlanPoly.path = lines
            }
            else
            {
                missionPlanPoly.visible = true
                updatePolyLine()
                missionPlanPoly.path = lines
            }
        }

        Component.onCompleted: targetDrone.missionPlanModel.pathChanged.connect(onDataChanged)
    }

    // Draw safety way points
    MapItemView {
        id: safetyWayPoints
        model: targetDrone.safetyModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: Theme.safetyColor
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.SAFETY_EDIT
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            targetDrone.removeCoordinateFromSafetyPlanAtIndex(index)
                    }
                    onPressed: {
                        mapGestureEnabled = false
                        targetDrone.safetyModel.currentPointIndex = index
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            targetDrone.setSafetyPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        mapGestureEnabled = true
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw safety
    MapPolyline {
        id: safetyPoly
        line.width: 3
        line.color: Theme.safetyColor
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<targetDrone.safetyModel.path.size(); i++)
                lines[i] = targetDrone.safetyModel.path.coordinateAt(i)
            safetyPoly.path = lines
        }
        function onDataChanged()
        {
            if (targetDrone.safetyModel.path.size() === 0)
            {
                safetyPoly.visible = false
                var lines = []
                safetyPoly.path = lines
            }
            else
            {
                safetyPoly.visible = true
                updatePolyLine()
                safetyPoly.path = lines
            }
        }
        Component.onCompleted: targetDrone.safetyModel.pathChanged.connect(onDataChanged)
    }

    // Draw landing plan waypoints
    MapItemView {
        id: landingPlanWayPoints
        model: targetDrone.landingPlanModel
        delegate: Component {
            MapCircle {
                id: circle
                property bool selected: false
                center {
                    latitude: wayPointLatitude
                    longitude: wayPointLongitude
                }
                radius: 250
                color: Theme.landingPlanColor
                border.width: 3
                MouseArea {
                    id: circleMouseArea
                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                    anchors.fill: parent
                    enabled: targetDrone.workMode === DroneBase.LANDING_PLAN_EDIT
                    onClicked: {
                        if (mouse.button === Qt.RightButton)
                            targetDrone.removeCoordinateFromLandingPlanAtIndex(index)
                    }
                    onPressed: {
                        mapGestureEnabled = false
                        targetDrone.landingPlanModel.currentPointIndex = index
                        circle.selected = true
                    }
                    onPositionChanged: {
                        if (circle.selected)
                        {
                            var mapped = circleMouseArea.mapToItem(mapView, mouse.x, mouse.y)
                            targetDrone.setLandingPlanPointPosition(index, mapView.toCoordinate(Qt.point(mapped.x, mapped.y)))
                        }
                    }
                    onReleased: {
                        mapGestureEnabled = true
                        circle.selected = false
                    }
                }
            }
        }
    }

    // Draw landing plan
    MapPolyline {
        id: landingPlanPoly
        line.width: 3
        line.color: Theme.landingPlanColor
        function updatePolyLine()
        {
            var lines = []
            for(var i=0; i<targetDrone.landingPlanModel.path.size(); i++)
                lines[i] = targetDrone.landingPlanModel.path.coordinateAt(i)
            landingPlanPoly.path = lines
        }
        function onDataChanged()
        {
            if (targetDrone.landingPlanModel.path.size() === 0)
            {
                landingPlanPoly.visible = false
                var lines = []
                landingPlanPoly.path = lines
            }
            else
            {
                landingPlanPoly.visible = true
                updatePolyLine()
                landingPlanPoly.path = lines
            }
        }
        Component.onCompleted: targetDrone.landingPlanModel.pathChanged.connect(onDataChanged)
    }

    // Exclusion area (polygon)
    PolygonExclusionArea {
         model: targetDrone.exclusionAreaModel
    }

    // Exclusion area (circle)
    CircleExclusionArea {
        model: targetDrone.exclusionAreaModel
    }

    // Drone marker
    MapQuickItem {
        id: droneMarker
        anchorPoint.x: droneItem.width / 2
        anchorPoint.y: droneItem.height / 2
        coordinate: targetDrone.position
        z: Theme.zMax

        sourceItem: Item {
            id: droneItem
            width: droneIcon.width
            height: droneIcon.height
            property int size: 48

            Image {
                id: droneIcon
                source: "qrc:/icons/ico-drone2.svg"
                mipmap: true
                width: droneItem.size
                sourceSize.width: droneItem.size
                fillMode: Image.PreserveAspectFit
                transform: Rotation {
                    origin.x: droneIcon.width /2
                    origin.y: droneIcon.height/2
                    angle: targetDrone.heading
                }
            }
        }
    }

    // Handle clicks
    MouseArea {
        anchors.fill: parent
        enabled: (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT) || (targetDrone.workMode === DroneBase.SAFETY_EDIT) ||
                 (targetDrone.workMode === DroneBase.LANDING_PLAN_EDIT) || (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)
        onClicked: {
            if (targetDrone.workMode === DroneBase.SAFETY_EDIT)
                targetDrone.addCoordinateToSafety(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            else
            if (targetDrone.workMode === DroneBase.MISSION_PLAN_EDIT)
                targetDrone.addCoordinateToMissionPlan(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            else
            if (targetDrone.workMode === DroneBase.LANDING_PLAN_EDIT)
            {
                targetDrone.addCoordinateToLandingPlan(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
            }
            else
            if (targetDrone.workMode === DroneBase.EXCLUSION_EDIT)
            {
                if (targetDrone.currentExclusionShape === DroneBase.RECTANGLE)
                    targetDrone.exclusionAreaModel.addRectangle(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
                else
                if (targetDrone.currentExclusionShape === DroneBase.TRIANGLE)
                    targetDrone.exclusionAreaModel.addTriangle(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
                else
                if (targetDrone.currentExclusionShape === DroneBase.CIRCLE)
                    targetDrone.exclusionAreaModel.addCircle(mapView.toCoordinate(Qt.point(mouse.x, mouse.y)))
             }
        }
    }

    Component.onCompleted: mapView.center = targetDrone.initialPosition
}
