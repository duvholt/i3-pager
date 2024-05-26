/*  -*- qml -*-
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

import QtQuick 2.15
import QtQuick.Controls as QQC2
import QtQuick.Dialogs
import QtQuick.Layouts 1.3

import org.kde.plasma.plasmoid 2.0
import org.kde.kquickcontrols 2.0 as KQC
import org.kde.kirigami 2.10 as Kirigami
import org.kde.kitemmodels 1.0
import org.kde.kcmutils as KCM

import org.kde.private.I3Pager
import "screens.js" as ScreensJS

KCM.ScrollViewKCM {

    property var cfg_screenNameList
    property var cfg_screenColorList
    property var cfg_screenColorOpacity
    property alias cfg_colorWorkspaceByScreen: colorWorkspaceByScreen.checked
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

    id: page
    Layout.fillWidth: true

    I3Pager {
        id: i3pager
    }

    header: Kirigami.FormLayout {
        QQC2.CheckBox {
            Kirigami.FormData.label: i18n("Color workspaces by screen:")

            id: colorWorkspaceByScreen
            checked: plasmoid.configuration.colorWorkspaceByScreen
            onCheckedChanged: plasmoid.configuration.colorWorkspaceByScreen = checked
        }

        RowLayout {
            Kirigami.FormData.label: i18n("Workspace color opacity:")

            QQC2.Slider {
                id: screenColorOpacity
                from: 0
                to: 1
                stepSize: 0.05
                snapMode: QQC2.Slider.SnapAlways
                value: cfg_screenColorOpacity
                onMoved: {
                    cfg_screenColorOpacity = value;
                    ScreensJS.saveConfig();
                }
            }

            QQC2.SpinBox {
                from: 0
                to: 100
                stepSize: 5
                value: cfg_screenColorOpacity * 100
                onValueModified: {
                    cfg_screenColorOpacity = value / 100;
                    ScreensJS.saveConfig();
                }
            }
        }
    }

    view: ListView {
        id: screensListView
        clip: true

        property real colorColumnWidth: Kirigami.Units.gridUnit
        property real actionsColumnWidth: Kirigami.Units.gridUnit

        Component.onCompleted: {
            ScreensJS.loadConfig();
            ScreensJS.loadNewScreens();
            ScreensJS.saveConfig();
        }

        model: ListModel {
            id: screenListModel
            dynamicRoles: true
        }
        reuseItems: true

        header: RowLayout {
            width: screensListView.width
            spacing: Kirigami.Units.smallSpacing

            Kirigami.Heading {
                text: i18n("Name")
                textFormat: Text.PlainText
                level: 2
                Layout.fillWidth: true
            }
            Kirigami.Heading {
                text: i18n("Color")
                textFormat: Text.PlainText
                level: 2
                Layout.preferredWidth: screensListView.colorColumnWidth
                Component.onCompleted: screensListView.colorColumnWidth = Math.max(implicitWidth, screensListView.colorColumnWidth)
            }
            Kirigami.Heading {
                text: i18n("Actions")
                level: 2
                Layout.preferredWidth: screensListView.actionsColumnWidth
                Component.onCompleted: screensListView.actionsColumnWidth = Math.max(implicitWidth, screensListView.actionsColumnWidth)
            }
        }

        delegate: QQC2.ItemDelegate {
            highlighted: false
            hoverEnabled: false
            down: false
            width: screensListView.width

            contentItem: FocusScope {
                implicitHeight: childrenRect.height

                RowLayout {
                    width: parent.width
                    spacing: Kirigami.Units.smallSpacing

                    QQC2.Label {
                        Layout.fillWidth: true
                        text: screenName
                    }

                    MouseArea {
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        Layout.fillHeight: true
                        Layout.minimumWidth: screensListView.colorColumnWidth
                        Layout.preferredWidth: screensListView.colorColumnWidth
                        Component.onCompleted: screensListView.colorColumnWidth = Math.max(implicitWidth, screensListView.colorColumnWidth)

                        onClicked: {
                            colorDialog.selectedColor = screenColor;
                            colorDialog.open();
                        }

                        Rectangle {
                            id: colorRectangle
                            width: parent.width
                            height: parent.height
                            color: screenColor
                        }

                        ColorDialog {
                            id: colorDialog
                            title: "Please choose a screen color"
                            onAccepted: {
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
                        Component.onCompleted: screensListView.actionsColumnWidth = Math.max(implicitWidth, screensListView.actionsColumnWidth)

                        QQC2.Button {
                            enabled: index != 0
                            icon.name: "arrow-up"
                            onClicked: {
                                screenListModel.move(index, index - 1, 1);
                                ScreensJS.saveConfig();
                            }
                        }
                        QQC2.Button {
                            enabled: index != (screenListModel.count - 1)
                            icon.name: "arrow-down"

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
