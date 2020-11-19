import QtQuick 2.14
import QtQuick.Controls 2.5
import Qt.labs.qmlmodels 1.0
import QtQml.Models 2.1
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0
import org.kde.kirigami 2.10 as Kirigami
import I3Pager 1.0
import "screens.js" as ScreensJS

ColumnLayout {
    id : page

    property var cfg_screenNameList
    property var cfg_screenColorList
    property var cfg_screenColorOpacity
    property alias cfg_colorWorkspaceByScreen : colorWorkspaceByScreen.checked

    I3Pager {
        id : i3pager
    }

    Kirigami.FormLayout {
        CheckBox {
            Kirigami.FormData.label : i18n("Color workspaces by screen:")

            id : colorWorkspaceByScreen
            checked : plasmoid.configuration.colorWorkspaceByScreen
            onCheckedChanged : plasmoid.configuration.colorWorkspaceByScreen = checked
        }

        RowLayout {
            Kirigami.FormData.label : i18n("Workspace color opacity:")

            Slider {
                id : screenColorOpacity
                from : 0
                to : 1
                stepSize : 0.05
                snapMode : Slider.SnapAlways
                value : cfg_screenColorOpacity
                onMoved : {
                    cfg_screenColorOpacity = value;
                    ScreensJS.saveConfig();
                }
            }

            SpinBox {
                from : 0
                to : 100
                stepSize : 5
                value : cfg_screenColorOpacity * 100
                onValueModified : {
                    cfg_screenColorOpacity = value / 100;
                    ScreensJS.saveConfig();
                }
            }
        }
    }

    ScrollView {
        id : scrollView

        Layout.fillWidth : true
        Layout.fillHeight : true
        contentHeight : screensListView.implicitHeight

        Component.onCompleted : {
            scrollView.background.visible = true;
        }

        ScrollBar.horizontal.policy : ScrollBar.AlwaysOff
        property bool scrollBarVisible : ScrollBar.vertical && ScrollBar.vertical.visible
        property var scrollBarWidth: scrollBarVisible ? ScrollBar.vertical.width : 0

        ListView {
            id : screensListView
            clip : true

            property var visibilityColumnWidth: Kirigami.Units.gridUnit

            Component.onCompleted : {
                ScreensJS.loadConfig();
                ScreensJS.loadNewScreens();
                ScreensJS.saveConfig();
            }

            model : ListModel {
                id : screenListModel
                dynamicRoles : true
            }

            header : Kirigami.AbstractListItem {
                hoverEnabled : false

                RowLayout {
                    Kirigami.Heading {
                        text : i18n("Name")
                        level : 2
                        Layout.fillWidth : true
                    }
                    Kirigami.Heading {
                        text : i18n("Color")
                        level : 2
                        Layout.preferredWidth : screensListView.visibilityColumnWidth
                        Component.onCompleted : screensListView.visibilityColumnWidth = Math.max(implicitWidth, screensListView.visibilityColumnWidth)
                    }
                    Kirigami.Heading {
                        text : i18n("Actions")
                        level : 2
                        Layout.preferredWidth : screensListView.visibilityColumnWidth
                        Component.onCompleted : screensListView.visibilityColumnWidth = Math.max(implicitWidth, screensListView.visibilityColumnWidth)
                    }
                }
            }

            delegate : Kirigami.AbstractListItem {
                highlighted : false
                hoverEnabled : false

                contentItem : RowLayout {
                    Label {
                        Layout.fillWidth : true
                        text : screenName
                    }

                    MouseArea {
                        hoverEnabled : true
                        cursorShape : Qt.PointingHandCursor
                        Layout.fillHeight : true
                        property var contentWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
                        implicitWidth : Math.max(contentWidth, screensListView.visibilityColumnWidth)
                        Component.onCompleted : screensListView.visibilityColumnWidth = Math.max(implicitWidth, screensListView.visibilityColumnWidth)
                        onClicked : {
                            colorDialog.color = screenColor;
                            colorDialog.open();
                        }

                        Rectangle {
                            id : colorRectangle
                            width : parent.width
                            height : parent.height
                            color : screenColor
                        }

                        ColorDialog {
                            id : colorDialog
                            title : "Please choose a screen color"
                            onAccepted : {
                                screenListModel.set(index, {
                                    screenName: screenName,
                                    screenColor: colorDialog.color
                                });
                                ScreensJS.saveConfig();
                            }
                        }
                    }

                    RowLayout {
                        property var contentWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
                        implicitWidth : Math.max(contentWidth, screensListView.visibilityColumnWidth)
                        Component.onCompleted : screensListView.visibilityColumnWidth = Math.max(implicitWidth, screensListView.visibilityColumnWidth)

                        Button {
                            enabled : index != 0
                            icon.name : "up"
                            onClicked : {
                                screenListModel.move(index, index - 1, 1);
                                ScreensJS.saveConfig();
                            }
                        }
                        Button {
                            enabled : index != (screenListModel.count - 1)
                            icon.name : "down"
                            onClicked : {
                                screenListModel.move(index, index + 1, 1);
                                ScreensJS.saveConfig();
                            }
                        }
                    }
                }
            }
        }
    }
}
