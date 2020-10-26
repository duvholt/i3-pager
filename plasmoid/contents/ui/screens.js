function saveConfig() {
    cfg_screenNameList = [];
    cfg_screenColorList = [];
    for (var i = 0; i < screenListModel.count; i++) {
        cfg_screenNameList.push(screenListModel.get(i).screenName);
        cfg_screenColorList.push(screenListModel.get(i).screenColor);
    }
}

function loadConfig() {
    for (var i = 0; i < cfg_screenNameList.length; i++) {
        screenListModel.append({screenName: cfg_screenNameList[i], screenColor: cfg_screenColorList[i]});
    }
}

function loadNewScreens() {
    for (var screenName of i3pager.getScreenNames()) {
        if (!isScreenNameOnList(screenName, cfg_screenNameList)) {
            screenListModel.append({screenName: screenName, screenColor: "#40ff0000"});
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
