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

QList<Workspace> Workspace::orderByOutput(QList<Workspace> inputWorkspaces, QList<QString> outputList) {
    QList<Workspace> outputWorkspaces;
    qInfo() << "Ordering workspaces by screens:" << outputList;
    for (auto output : outputList) {
        for (auto workspace : inputWorkspaces) {
            if (workspace.output == output) {
                qInfo() << "Added workspace:" << workspace.name << "output:" << workspace.output;
                outputWorkspaces.append(workspace);
            }
        }
    }

    return outputWorkspaces;
}
