import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls
import QtQuick.Dialogs
import org.kde.plasma.plasmoid
import org.kde.plasma.core 2.0 as PlasmaCore
import QtQuick.Window 2.13
import I3Pager 1.0

PlasmoidItem {
    id : root

    preferredRepresentation : Plasmoid.fullRepresentation

    readonly property color defaultWorkspace : "transparent"
    readonly property color focusedWorkspace : PlasmaCore.Theme.positiveTextColor
    readonly property color visibleWorkspace : PlasmaCore.Theme.neutralTextColor
    readonly property color urgentWorkspace : PlasmaCore.Theme.negativeTextColor
    readonly property color mouseWorkspace : PlasmaCore.Theme.linkColor

    ColumnLayout {
        id : rootColumnLayout

        I3Pager {
            id : i3pager
            currentScreen : Screen.name
            onWorkspacesChanged : {
                updateWorkspaces();
            }
            function updateWorkspaces() {
                var screenNameList = []
                for (var screenName of plasmoid.configuration.screenNameList) {
                    screenNameList.push(screenName);
                }
                repeater.model = i3pager.getWorkspaces(plasmoid.configuration.filterByCurrentScreen, plasmoid.configuration.orderWorkspacesBy, screenNameList);
            }
        }

        Connections {
            target : plasmoid.configuration
            onFilterByCurrentScreenChanged : {
                i3pager.updateWorkspaces();
            }
            onOrderWorkspacesByChanged : {
                i3pager.updateWorkspaces();
            }
            onScreenNameListChanged : {
                i3pager.updateWorkspaces();
            }
            onIndicatorPositionChanged : {
                i3pager.updateWorkspaces();
            }
        }

        // Hack to update current screen
        Screen.onNameChanged : {
            i3pager.currentScreen = Screen.name
        }

        Row {
            id : workspaceRow
            Layout.alignment : Layout.AlignVCenter | Layout.AlignHCenter
            spacing : 2

            Repeater {
                id : repeater

                MouseArea {
                    id : mouseArea
                    hoverEnabled : true
                    cursorShape : Qt.PointingHandCursor
                    onClicked : {
                        i3pager.activateWorkspace(modelData.id)
                    }
                    width : textRow.width
                    height : root.height
                    function getIndicatorColor() {
                        if (mouseArea.containsMouse) {
                            return mouseWorkspace;
                        } else if (modelData.urgent && !plasmoid.configuration.urgentColorWholeWorkspace) {
                            return urgentWorkspace;
                        } else if (modelData.focused) {
                            return focusedWorkspace;
                        } else if (modelData.visible) {
                            return visibleWorkspace;
                        }
                        return defaultWorkspace;
                    }
                    function getFillColor() {
                        if (modelData.urgent && plasmoid.configuration.urgentColorWholeWorkspace) {
                            return urgentWorkspace;
                        } else if (!plasmoid.configuration.colorWorkspaceByScreen) {
                            return "transparent";
                        }
                        var indexOfScreen = plasmoid.configuration.screenNameList.indexOf(modelData.output);
                        var screenColor = plasmoid.configuration.screenColorList[indexOfScreen];
                        return screenColor;
                    }
                    function getRadius() {
                        return plasmoid.configuration.rounded ? 3 : 0;
                    }

                    Rectangle { // Border style
                        visible : plasmoid.configuration.style === "border"
                        color : mouseArea.getFillColor()
                        radius : getRadius()
                        height : textRow.height
                        width : textRow.width
                        border {
                            width : 2
                            color : mouseArea.getIndicatorColor()
                        }
                    }

                    Rectangle { // Underline style
                        visible : plasmoid.configuration.style === "line"
                        color : mouseArea.getFillColor()
                        radius : getRadius()
                        height : textRow.height
                        width : textRow.width

                        Rectangle {
                            Component.onCompleted : {
                                if (plasmoid.configuration.indicatorPosition === "top") {
                                    anchors.top = parent.top;
                                } else {
                                    anchors.bottom = parent.bottom;
                                }
                            }

                            height : 5
                            width : textRow.width
                            radius : getRadius()
                            color : mouseArea.getIndicatorColor()
                        }
                    }

                    RowLayout {
                        id : textRow
                        height : parent.height

                        Rectangle {
                            width : 5
                        }
                        Text {
                            font.family : PlasmaCore.Theme.defaultFont.family
                            height : textRow.height
                            minimumPixelSize : PlasmaCore.Theme.smallestFont.pixelSize
                            font.pixelSize : Math.min(textRow.height * 0.5, 1.5 * PlasmaCore.Theme.defaultFont.pixelSize)
                            fontSizeMode : Text.VerticalFit
                            color : PlasmaCore.Theme.textColor
                            text : modelData.index
                            verticalAlignment : Text.AlignHCenter
                        }
                        Label {
                            id : icon
                            rightPadding : 3
                            leftPadding : 3
                            bottomPadding : 0
                            height : textRow.height
                            minimumPixelSize : PlasmaCore.Theme.smallestFont.pixelSize
                            font.pixelSize : Math.min(textRow.height * 0.5, 1.5 * PlasmaCore.Theme.defaultFont.pixelSize)
                            fontSizeMode : Text.VerticalFit
                            font.family : "Font Awesome 5 Free Solid"
                            font.styleName : "Solid"
                            color : PlasmaCore.Theme.textColor
                            text : modelData.icon
                            verticalAlignment : Text.AlignHCenter
                            visible : plasmoid.configuration.showWorkspaceNames
                        }
                        Text {
                            height : textRow.height
                            minimumPixelSize : PlasmaCore.Theme.smallestFont.pixelSize
                            font.pixelSize : Math.min(textRow.height * 0.5, 1.5 * PlasmaCore.Theme.defaultFont.pixelSize)
                            fontSizeMode : Text.VerticalFit
                            font.family : PlasmaCore.Theme.defaultFont.family
                            color : PlasmaCore.Theme.textColor
                            text : modelData.name
                            verticalAlignment : Text.AlignHCenter
                            visible : plasmoid.configuration.showWorkspaceNames
                        }
                        Rectangle {
                            width : 5
                        }
                    }
                }
            }
            Item {
                width : modeText.width
                height : modeText.height
                anchors.verticalCenter : parent.verticalCenter
                visible : i3pager.mode !== "default"
                Rectangle {
                    color : "#e5c07b"
                    height : parent.height
                    width : parent.width
                }
                Text {
                    id : modeText
                    rightPadding : 10
                    leftPadding : 10
                    minimumPixelSize : PlasmaCore.Theme.smallestFont.pixelSize
                    font.pixelSize : Math.min(textRow.height * 0.5, 1.5 * PlasmaCore.Theme.defaultFont.pixelSize)
                    fontSizeMode : Text.VerticalFit
                    font.family : PlasmaCore.Theme.defaultFont.family
                    color : "#333333"
                    text : i3pager.mode
                }
            }
        }
    }
}
