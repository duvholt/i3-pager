import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import org.kde.kirigami 2.4 as Kirigami

Kirigami.FormLayout {
    id : page
    width : childrenRect.width
    height : childrenRect.height

    property alias cfg_showWorkspaceNames : showWorkspaceNames.checked
    property alias cfg_filterByCurrentScreen : filterByCurrentScreen.checked
    property alias cfg_urgentColorWholeWorkspace : urgentColorWholeWorkspace.checked
    property alias cfg_rounded : rounded.checked
    property var cfg_orderWorkspacesBy
    property var cfg_style
    property var cfg_indicatorPosition

    ColumnLayout {
        Kirigami.FormData.label : i18n("Basic:")
        Kirigami.FormData.buddyFor : showWorkspaceNames

        CheckBox {
            id : showWorkspaceNames
            text : i18n("Show workspace names")
            checked : plasmoid.configuration.showWorkspaceNames
            onCheckedChanged : plasmoid.configuration.showWorkspaceNames = checked
        }

        CheckBox {
            id : filterByCurrentScreen
            text : i18n("Filter workspaces by current screen")
            checked : plasmoid.configuration.filterByCurrentScreen
            onCheckedChanged : plasmoid.configuration.filterByCurrentScreen = checked
        }

        CheckBox {
            id : urgentColorWholeWorkspace
            text : i18n("Color the whole workspace if urgent")
            checked : plasmoid.configuration.urgentColorWholeWorkspace
            onCheckedChanged : plasmoid.configuration.urgentColorWholeWorkspace = checked
        }

        CheckBox {
            id : rounded
            text : i18n("Rounded corners")
            checked : plasmoid.configuration.rounded
            onCheckedChanged : plasmoid.configuration.rounded = checked
        }
    }

    Item {
        Kirigami.FormData.isSection : true
    }

    ColumnLayout {
        Kirigami.FormData.label : i18n("Order workspaces by:")
        Kirigami.FormData.buddyFor : orderWorkspacesByDefaultRadio

        RadioButton {
            id : orderWorkspacesByDefaultRadio
            text : i18n("Default")
            checked : cfg_orderWorkspacesBy == "default"
            onClicked : {
                cfg_orderWorkspacesBy = "default"
            }
        }

        RadioButton {
            id : orderWorkspacesByScreenRadio
            text : i18n("Screen")
            checked : cfg_orderWorkspacesBy == "screen"
            onClicked : {
                cfg_orderWorkspacesBy = "screen"
            }
        }
        
        RadioButton {
            id : orderWorkspacesByName
            text : i18n("Name")
            checked : cfg_orderWorkspacesBy == "name"
            onClicked : {
                cfg_orderWorkspacesBy = "name"
            }
        }
    }

    Item {
        Kirigami.FormData.isSection : true
    }

    ColumnLayout {
        Kirigami.FormData.label : i18n("Indicator style:")
        Kirigami.FormData.buddyFor : styleUnderlineRadio

        RadioButton {
            id : styleUnderlineRadio
            text : i18n("Line")
            checked : cfg_style == "line"
            onClicked : {
                cfg_style = "line"
            }
        }

        RadioButton {
            id : styleBorderRadio
            text : i18n("Border")
            checked : cfg_style == "border"
            onClicked : {
                cfg_style = "border"
            }
        }
    }

    Item {
        Kirigami.FormData.isSection : true
    }

    ColumnLayout {
        Kirigami.FormData.label : i18n("Indicator position:")
        Kirigami.FormData.buddyFor : indicatorPositionTopRadio
        visible : cfg_style == "line"

        RadioButton {
            id : indicatorPositionTopRadio
            text : i18n("Top")
            checked : cfg_indicatorPosition == "top"
            onClicked : {
                cfg_indicatorPosition = "top"
            }
        }

        RadioButton {
            id : indicatorPositionBottomRadio
            text : i18n("Bottom")
            checked : cfg_indicatorPosition == "bottom"
            onClicked : {
                cfg_indicatorPosition = "bottom"
            }
        }
    }
}
