#include <QtQml>
#include "plugin.h"
#include "i3pager.h"


void Plugin::registerTypes(const char *uri) {
    qmlRegisterType<I3Pager>("I3Pager", 1, 0, "I3Pager");
}
