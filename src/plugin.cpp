#include "plugin.h"

void Plugin::registerTypes(const char* uri) {
    qRegisterMetaType<Workspace>();
    qRegisterMetaType<QList<Workspace>>();
    qmlRegisterType<I3Pager>("I3Pager", 1, 0, "I3Pager");
}
