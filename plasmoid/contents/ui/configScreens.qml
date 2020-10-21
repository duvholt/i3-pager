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

    I3Pager {
        id : i3pager
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
        property var scrollBarWidth: scrollBarVisible ?ScrollBar.vertical.width : 0

        ListView {
            id : screensListView
            clip : true

            Component.onCompleted : {
                ScreensJS.loadConfig();
                ScreensJS.loadNewScreens();
            }

            model : ListModel {
                id : screenListModel
            }

            property var visibilityColumnWidth: Kirigami.Units.gridUnit
            property var keySequenceColumnWidth: Kirigami.Units.gridUnit

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
                        text : name
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
