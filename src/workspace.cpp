#include "workspace.h"

QList<Workspace> Workspace::filterByCurrentScreen(QList<Workspace> inputWorkspaces, QString currentScreen) {
    QList<Workspace> outputWorkspaces;
    qInfo() << "Filtering by current screen:" << currentScreen;
    for (auto workspace : inputWorkspaces) {
        if (currentScreen == workspace.output) {
            qInfo() << "Added workspace:" << workspace.name << "output:" << workspace.output;
            outputWorkspaces.append(workspace);
        } else {
            qInfo() << "Removed workspace:" << workspace.name << "output:" << workspace.output;
        }
    }
    return outputWorkspaces;
}