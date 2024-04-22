import QtQuick 2.15
import org.kde.plasma.configuration

ConfigModel {
    ConfigCategory {
        name: i18n("General")
        icon: "configure"
        source: "configGeneral.qml"
    }
    ConfigCategory {
        name: i18n("Screens")
        icon: "monitor"
        source: "configScreens.qml"
    }
}
