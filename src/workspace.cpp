#include "workspace.h"

QList<Workspace> Workspace::filterByCurrentScreen(QList<Workspace> inputWorkspaces, QString currentScreen) {
    QList<Workspace> outputWorkspaces;
    for (auto workspace : inputWorkspaces) {
        if (currentScreen == workspace.output) {
            outputWorkspaces.append(workspace);
        }
    }
    return outputWorkspaces;
}