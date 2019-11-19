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

            MouseArea {
                id: mouseArea
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: { i3pager.activateWorkspace(modelData.id) }

                width: textRow.width
                height: textRow.height

                RowLayout {
                    id: textRow
                    Text {
                        font.pixelSize: 15
                        leftPadding: 10
                        topPadding: 5
                        bottomPadding: 8
                        font.family: "Noto Sans"
                        color: "#dfdfdf"
                        text: modelData.index
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Label {
                        id: icon
                        rightPadding: 3
                        leftPadding: 3
                        bottomPadding: 2
                        font.pixelSize: 15
                        font.family: "Font Awesome 5 Free Solid"
                        font.styleName: "Solid"
                        color: "#dfdfdf"
                        text: modelData.icon
                        Layout.alignment: Qt.AlignHCenter
                    }
                    Text {
                        topPadding: 5
                        bottomPadding: 8
                        rightPadding: 10
                        font.pixelSize: 15
                        font.family: "Noto Sans"
                        color: "#dfdfdf"
                        text: modelData.name
                        Layout.alignment: Qt.AlignHCenter
                    }
                }
                Rectangle {
                    function getColor() {
                        if(mouseArea.containsMouse && modelData.visible) {
                            return "#d19a66";
                        } else if (modelData.visible) {
                            return "#e5c07b";
                        } else if (mouseArea.containsMouse) {
                            return "#56b6c2";
                        }
                        return "transparent";
                    }
                    color: getColor()
                    height: 3
                    width: parent.width
                    anchors.bottom: textRow.bottom
                }
            }
        }
    }
}
