#include <i3ipc++/ipc.hpp>
#include "i3pager.h"
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>


I3Pager::I3Pager(QObject *parent) : QObject(parent) {
    currentScreenPrivate = QString();
}

QStringList I3Pager::getWorkspaces() {
    QStringList dataList;
    try {
        i3ipc::connection conn;
        qInfo() << "Screen name " << this->currentScreenPrivate;
        auto workspaces = conn.get_workspaces();
        for (auto& workspace : workspaces) {
            qInfo() << "name " << QString::fromStdString(workspace->name);
            qInfo() << "out " << QString::fromStdString(workspace->output);
            if(QString::fromStdString(workspace->output) == this->currentScreenPrivate) {
                dataList.append(QString::fromStdString(workspace->name));
            }
        }
    } catch (...) {
        // TODO
    }
    return dataList;
}

void I3Pager::activateWorkspace(QString workspace) {
    i3ipc::connection conn;
    conn.send_command("workspace " + workspace.toStdString());
}

QString I3Pager::getCurrentScreen() const {
    return this->currentScreenPrivate;
}

void I3Pager::setCurrentScreen(QString screen) {
    this->currentScreenPrivate = screen;
    Q_EMIT currentScreenChanged();
}
