import QtQuick 2.15
import QtQuick.Controls
import Qt.labs.qmlmodels
import QtQml.Models
import QtQuick.Layouts
import QtQuick.Dialogs
import org.kde.kirigami as Kirigami
import org.kde.kirigami.delegates as KirigamiDelegates
import org.kde.private.I3Pager
import "screens.js" as ScreensJS
import org.kde.kcmutils as KCM

KCM.SimpleKCM {

    property var cfg_screenNameList
    property var cfg_screenColorList
    property var cfg_screenColorOpacity
    property alias cfg_colorWorkspaceByScreen : colorWorkspaceByScreen.checked
    property var cfg_orderWorkspacesBy
    property var cfg_style
    property var cfg_styleDefault
    property var cfg_indicatorPosition
    property var cfg_colorWorkspaceByScreenDefault
    property var cfg_filterByCurrentScreenDefault
    property var cfg_indicatorPositionDefault
    property var cfg_orderWorkspacesByDefault
    property var cfg_roundedDefault
    property var cfg_screenColorListDefault
    property var cfg_filterByCurrentScreen
    property var cfg_showWorkspaceNamesDefault
    property var cfg_urgentColorWholeWorkspaceDefault
    property var cfg_urgentColorWholeWorkspace
    property var cfg_rounded
    property var cfg_screenColorOpacityDefault
    property var cfg_screenNameListDefault
    property var cfg_showWorkspaceNames

    ColumnLayout {
        id : page


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
            contentHeight: 200

            Component.onCompleted : {
                scrollView.background.visible = true;
            }

            ScrollBar.horizontal.policy : ScrollBar.AlwaysOff
            property bool scrollBarVisible : ScrollBar.vertical && ScrollBar.vertical.visible
            property var scrollBarWidth: scrollBarVisible ? ScrollBar.vertical.width : 0

            ListView {
                id : screensListView
                clip : true

                property real colorColumnWidth: 40
                property real actionsColumnWidth: 90

                Component.onCompleted : {
                    ScreensJS.loadConfig();
                    ScreensJS.loadNewScreens();
                    ScreensJS.saveConfig();
                }

                model : ListModel {
                    id : screenListModel
                    dynamicRoles : true
                }

                header: RowLayout {
                    width: screensListView.width
                    spacing: Kirigami.Units.smallSpacing

                    Kirigami.Heading {
                        text : i18n("Name")
                        textFormat: Text.PlainText
                        level : 2
                        Layout.fillWidth : true
                    }
                    Kirigami.Heading {
                        text : i18n("Color")
                        textFormat: Text.PlainText
                        level : 2
                        Layout.preferredWidth : screensListView.colorColumnWidth
                    }
                    Kirigami.Heading {
                        text : i18n("Actions")
                        level : 2
                        Layout.preferredWidth : screensListView.actionsColumnWidth
                    }
                }

                delegate: ItemDelegate {
                    highlighted: false
                    hoverEnabled: false
                    down: false
                    width: screensListView.width
                    spacing: Kirigami.Units.smallSpacing
                    
                    contentItem : RowLayout {
                        width: screensListView.width
                        spacing: Kirigami.Units.smallSpacing

                        Label {
                            Layout.fillWidth : true
                            text : screenName
                        }

                        MouseArea {
                            hoverEnabled : true
                            cursorShape : Qt.PointingHandCursor
                            Layout.fillHeight : true
                            Layout.minimumWidth: screensListView.colorColumnWidth
                            Layout.preferredWidth: screensListView.colorColumnWidth

                            onClicked : {
                                colorDialog.selectedColor = screenColor;
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
                                        screenColor: colorDialog.selectedColor
                                    });
                                    ScreensJS.saveConfig();
                                }
                            }
                        }

                        RowLayout {
                            Layout.minimumWidth: screensListView.actionsColumnWidth
                            Layout.preferredWidth: screensListView.actionsColumnWidth

                            Button {
                                enabled : index != 0
                                icon.name : "up"
                                onClicked: {
                                    screenListModel.move(index, index - 1, 1);
                                    ScreensJS.saveConfig();
                                }
                            }
                            Button {
                                enabled : index != (screenListModel.count - 1)
                                icon.name : "down"
                                onClicked: {
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
}
