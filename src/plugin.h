#ifndef I3PAGER_PLASMOID_PLUGIN_H
#define I3PAGER_PLASMOID_PLUGIN_H

#include "i3pager.h"
#include "workspace.h"
#include <QQmlExtensionPlugin>
#include <QtQml>

class QQmlEngine;
class Plugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char* uri) override;
};

#endif //I3PAGER_PLASMOID_PLUGIN_H
