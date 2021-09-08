#include "workspace.h"

QList<Workspace> Workspace::filterByCurrentScreen(QList<Workspace> inputWorkspaces, QString currentScreen) {
    QList<Workspace> outputWorkspaces;
    qDebug() << "Filtering by current screen:" << currentScreen;
    for (auto workspace : inputWorkspaces) {
        if (currentScreen == workspace.output) {
            qDebug() << "Added workspace:" << workspace.name << "output:" << workspace.output;
            outputWorkspaces.append(workspace);
        } else {
            qDebug() << "Removed workspace:" << workspace.name << "output:" << workspace.output;
        }
    }
    return outputWorkspaces;
}

QList<Workspace> Workspace::orderByOutput(QList<Workspace> inputWorkspaces, QList<QString> outputList) {
    QList<Workspace> outputWorkspaces;
    qDebug() << "Ordering workspaces by screens:" << outputList;
    for (auto output : outputList) {
        for (auto workspace : inputWorkspaces) {
            if (workspace.output == output) {
                qDebug() << "Added workspace:" << workspace.name << "output:" << workspace.output;
                outputWorkspaces.append(workspace);
            }
        }
    }

    return outputWorkspaces;
}
