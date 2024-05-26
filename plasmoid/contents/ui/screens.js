/*  -*- qml -*-
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

function saveConfig() {
    console.log("Saving config")
    cfg_screenNameList = [];
    cfg_screenColorList = [];

    for (var i = 0; i < screenListModel.count; i++) {
        var name = screenListModel.get(i).screenName;
        var color = qColorFromString(screenListModel.get(i).screenColor);
        color.a = cfg_screenColorOpacity;

        cfg_screenNameList.push(name);
        cfg_screenColorList.push(color);
    }
}

function loadConfig() {
    for (var i = 0; i < cfg_screenNameList.length; i++) {
        var name = cfg_screenNameList[i];
        var color = qColorFromString(cfg_screenColorList[i]);
        color.a = 1;

        screenListModel.append({screenName: name, screenColor: color});
    }
}

function loadNewScreens() {
    var defaultColors = ["#004040", "#007D7D", "#00D7D7"];
    for (var screenName of i3pager.getScreenNames()) {
        if (!isScreenNameOnList(screenName, cfg_screenNameList)) {
            var colorIndex = Math.min(screenListModel.count, defaultColors.length - 1);
            screenListModel.append({screenName: screenName, screenColor: defaultColors[colorIndex]});
        }
    }
}

function isScreenNameOnList(name, list) {
    for (var screenName of list) {
        if (name == screenName) {
            return true;
        }
    }
    return false;
}

/* This is a helper function. There is no
 * function for creating QColor from string,
 * therefore we use Qt.lighter with the
 * factor of 1 as a workaround. */
function qColorFromString(stringColor) {
    return Qt.lighter(stringColor, 1);
}
