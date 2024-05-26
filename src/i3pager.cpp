/*  -*- c++ -*-
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "i3pager.h"

#include <i3ipc++/ipc.hpp>
#include "i3pager_debug.h"
#include "i3listener.h"
#include <future>
#include <QDebug>


I3Pager::I3Pager(QObject* parent)
    : QObject(parent) {
    currentScreenPrivate = QString();
    mode = "default";

    qCDebug(I3PAGER) << "Starting i3 listener";
    this->i3ListenerThread = new I3ListenerThread(this);
    connect(i3ListenerThread, &I3ListenerThread::modeChanged, this, [=](const QString& mode) {
        this->mode = mode;
        Q_EMIT modeChanged();
    });
    connect(i3ListenerThread, &I3ListenerThread::workspacesChanged, this, [=]() {
        Q_EMIT workspacesChanged();
    });
    connect(i3ListenerThread, &I3ListenerThread::finished, i3ListenerThread, &QObject::deleteLater);
    i3ListenerThread->start();
    qCDebug(I3PAGER) << "i3 listener started";
}

I3Pager::~I3Pager() {
    qCDebug(I3PAGER) << "I3Pager destructor";
    this->i3ListenerThread->stop();
    this->i3ListenerThread->wait();
    qCDebug(I3PAGER) << "I3Pager destructor done";
}

QList<QString> I3Pager::getScreenNames() {
    QList<QString> screenList;
    try {
        i3ipc::connection conn;
        auto screens = conn.get_outputs();

        for (auto& screen : screens) {
            if (screen->active) {
                screenList.append(QString::fromStdString(screen->name));
                qCDebug(I3PAGER) << "Screen name:" << QString::fromStdString(screen->name);
            }
        }
    } catch (std::exception const& e) {
        qCWarning(I3PAGER) << "Exception while retrieving screen names: " << e.what();
    }

    return screenList;
}

QList<Workspace> I3Pager::getWorkspaces(bool filterByCurrentScreen, QString orderWorkspacesBy, QList<QString> screenOrder) {
    QList<Workspace> workspaceList;
    try {
        i3ipc::connection conn;
        auto i3workspaceList = conn.get_workspaces();
        qCDebug(I3PAGER) << "Loading workspaces:";

        for (auto& i3workspace : i3workspaceList) {
            Workspace workspace;

            auto splitName = QString::fromStdString(i3workspace->name).split(':');
            workspace.id = QString::fromStdString(i3workspace->name);
            workspace.index = splitName[0];
            workspace.name = splitName.size() == 1 ? splitName[0] : splitName[1];
            workspace.icon = splitName.size() == 3 ? splitName[2] : "";

            workspace.output = QString::fromStdString(i3workspace->output);
            workspace.focused = i3workspace->focused;
            workspace.visible = i3workspace->visible;
            workspace.urgent = i3workspace->urgent;

            qCDebug(I3PAGER) << "i3Workspace name:" << QString::fromStdString(i3workspace->name);
            qCDebug(I3PAGER) << "Workspace:"
                    << "id:" << workspace.id
                    << "index:" << workspace.index
                    << "name:" << workspace.name
                    << "icon:" << workspace.icon
                    << "focused:" << workspace.focused
                    << "urgent:" << workspace.urgent
                    << "visible:" << workspace.visible
                    << "output:" << workspace.output;
            workspaceList.append(workspace);
        }
    } catch (std::exception const& e) {
        qCWarning(I3PAGER) << "Exception while retrieving workspaces:" << e.what();
    }

    if (filterByCurrentScreen) {
        workspaceList = Workspace::filterByCurrentScreen(workspaceList, this->currentScreenPrivate);
    }

    if (orderWorkspacesBy == "screen" && !screenOrder.isEmpty()) {
        workspaceList = Workspace::orderByOutput(workspaceList, screenOrder);
    }
    else if (orderWorkspacesBy == "name") {
        workspaceList = Workspace::orderByName(workspaceList);
    }

    return workspaceList;
}

void I3Pager::activateWorkspace(QString workspace) {
    i3ipc::connection conn;
    conn.send_command("workspace " + workspace.toStdString());
}

void I3Pager::setCurrentScreen(QString screen) {
    this->currentScreenPrivate = screen;
    Q_EMIT workspacesChanged();
}

QString I3Pager::getMode() {
    return mode;
}

QString I3Pager::getCurrentScreen() {
    return this->currentScreenPrivate;
}
