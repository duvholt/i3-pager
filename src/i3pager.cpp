#include "i3pager.h"

I3Pager::I3Pager(QObject* parent)
    : QObject(parent) {
    currentScreenPrivate = QString();
    mode = "default";
    i3ipcFuture = QtConcurrent::run(QThreadPool::globalInstance(), [this]() {
        while (true) {
            handleI3Events();
            qWarning() << "Lost ipc connection";
            QThread::sleep(10);
        }
    });
}

I3Pager::~I3Pager() {
    i3ipcFuture.cancel();
}

void I3Pager::handleI3Events() {
    try {
        i3ipc::connection conn;
        conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_BINDING | i3ipc::ET_MODE);
        // Handler of WORKSPACE EVENT
        conn.signal_workspace_event.connect([this](const i3ipc::workspace_event_t& ev) {
            qInfo() << "workspace_event: " << (char)ev.type;
            if (ev.current) {
                qInfo() << "\tSwitched to #" << ev.current->num << " - \"" << QString::fromStdString(ev.current->name) << '"';
                Q_EMIT workspacesChanged();
            }
        });

        conn.signal_mode_event.connect([this](const i3ipc::mode_t& mode) {
            this->mode = QString::fromStdString(mode.change);
            qInfo() << "mode: " << this->mode;
            Q_EMIT modeChanged();
        });

        while (true) {
            conn.handle_event();
        }
    } catch (...) {
        // TODO
        qWarning() << "i3ipc error";
    }
}

QList<Workspace> I3Pager::getWorkspaces(bool filterByCurrentScreen) {
    QList<Workspace> workspaceList;
    try {
        i3ipc::connection conn;
        auto i3workspaceList = conn.get_workspaces();
        qInfo() << "Loading workspaces:";

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

            qInfo() << "i3Workspace name:" << QString::fromStdString(i3workspace->name);
            qInfo() << "Workspace:"
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
    } catch (...) {
        qWarning() << "i3ipc error";
    }

    if (filterByCurrentScreen) {
        workspaceList = Workspace::filterByCurrentScreen(workspaceList, this->currentScreenPrivate);
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
