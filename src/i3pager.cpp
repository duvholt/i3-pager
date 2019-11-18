#include <i3ipc++/ipc.hpp>
#include "i3pager.h"
#include <QScreen>
#include <QGuiApplication>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <future>
#include <QVariant>

#include <QtConcurrent/QtConcurrent>


I3Pager::I3Pager(QObject *parent) : QObject(parent) {
    currentScreenPrivate = QString();
    QtConcurrent::run(QThreadPool::globalInstance(), [this]() {
        poll();
    });
}

void I3Pager::poll() {
    try {
        i3ipc::connection conn;
        conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_BINDING);
        // Handler of WORKSPACE EVENT
        conn.signal_workspace_event.connect([this](const i3ipc::workspace_event_t&  ev) {
            qInfo() << "workspace_event: " << (char)ev.type;
            if (ev.current) {
                qInfo() << "\tSwitched to #" << ev.current->num << " - \"" << QString::fromStdString(ev.current->name) << '"';
                Q_EMIT currentScreenChanged();
            }
        });
        while (true) {
            conn.handle_event();
        }
    } catch (...) {
        // TODO
        qWarning() << "i3ipc error";
    }
}

QVariantList I3Pager::getWorkspaces() {
    QVariantList dataList;
    try {
        i3ipc::connection conn;
        qInfo() << "Screen name " << this->currentScreenPrivate;
        auto workspaces = conn.get_workspaces();
        for (auto& workspace : workspaces) {
            qInfo() << "name " << QString::fromStdString(workspace->name);
            qInfo() << "out " << QString::fromStdString(workspace->output);
            if(QString::fromStdString(workspace->output) == this->currentScreenPrivate) {
                QMap<QString, QVariant> workspaceData;
                workspaceData.insert("name", QString::fromStdString(workspace->name));
                workspaceData.insert("visible", workspace->visible);
                dataList.append(workspaceData);
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
