function saveConfig() {
	cfg_screenNameList = [];
	for (var i = 0; i < screenListModel.count; i++) {
		cfg_screenNameList.push(screenListModel.get(i).name);
	}
}

function loadConfig() {
	for (var i = 0; i < cfg_screenNameList.length; i++) {
		screenListModel.append({ name: cfg_screenNameList[i] });
	}
}

function loadNewScreens() {
	for (var screenName of i3pager.getScreenNames()) {
		if (!isScreenNameOnList(screenName, cfg_screenNameList)) {
			screenListModel.append({ name: screenName });
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
