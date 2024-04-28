#include "plugin.h"

#include <QtQml>

void Plugin::registerTypes(const char  *uri) {
    Q_ASSERT(uri == QLatin1String("org.kde.private.I3Pager"));
    qRegisterMetaType<Workspace>();
    qRegisterMetaType<QList<Workspace>>();
    qmlRegisterType<I3Pager>(uri, 1, 0, "I3Pager");
}
