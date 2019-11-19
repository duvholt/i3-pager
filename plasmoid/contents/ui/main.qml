import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.3
import QtQuick.Dialogs 1.3
import QtQuick.Controls.Styles 1.3
import org.kde.plasma.plasmoid 2.0
import QtQuick.Window 2.13
import I3Pager 1.0

ColumnLayout {
    id: root
    Plasmoid.preferredRepresentation: Plasmoid.fullRepresentation
    spacing: 0

    I3Pager {
        id: i3pager
        currentScreen: Screen.name
    }

    // Hack to update current screen
    Screen.onNameChanged: {
        i3pager.currentScreen = Screen.name
    }

    Row  {
        id: workspaceRow
        Layout.alignment: Layout.AlignVCenter | Layout.AlignHCenter
        spacing: 0
        Repeater {
            id: repeater
            model: i3pager.workspaces
            Text {
                id: workspaceText
                text: modelData.name
                color: "#dfdfdf"
                leftPadding: 10
                rightPadding: 10
                topPadding: 6
                bottomPadding: 6
                font.pixelSize: 16
                font.family: "Noto Sans"
                MouseArea {
                    id: mouseArea
                    anchors.fill: parent
                    hoverEnabled: true
                    cursorShape: Qt.PointingHandCursor
                    onClicked: { i3pager.activateWorkspace(modelData.name) }
                }
                Rectangle {
                    function getColor() {
                        if (mouseArea.containsMouse) {
                            return "#ffe8bd";
                        } else if (modelData.visible) {
                            return "#e5c07b";
                        }
                        return "transparent";
                    }
                    color: getColor()
                    height: 2
                    width: parent.width
                    anchors.bottom: parent.bottom
                }
            }
        }
    }
}
