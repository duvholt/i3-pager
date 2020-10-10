#include "i3pager.h"

I3Pager::I3Pager(QObject* parent)
    : QObject(parent) {

    //qmlRegisterType<Workspace>();
    currentScreenPrivate = QString();
    mode = "default";
    QtConcurrent::run(QThreadPool::globalInstance(), [this]() {
        while (true) {
            handleI3Events();
            qWarning() << "Lost ipc connection";
            QThread::sleep(10);
        }
    });
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
                Q_EMIT currentScreenChanged();
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

QList<Workspace> I3Pager::getWorkspaces() {
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
            workspace.visible = i3workspace->visible;
            workspace.urgent = i3workspace->urgent;
            workspace.output = QString::fromStdString(i3workspace->output);

            qInfo() << "Workspace:" << workspace.name << "urgent:" << workspace.urgent << "visible:" << workspace.visible << "output:" << workspace.output;
            workspaceList.append(workspace);
        }
    } catch (...) {
        qWarning() << "i3ipc error";
    }
    workspaceList = Workspace::filterByCurrentScreen(workspaceList, this->currentScreenPrivate);
    return workspaceList;
}

void I3Pager::activateWorkspace(QString workspace) {
    i3ipc::connection conn;
    conn.send_command("workspace " + workspace.toStdString());
}

void I3Pager::setCurrentScreen(QString screen) {
    this->currentScreenPrivate = screen;
    Q_EMIT currentScreenChanged();
}

QString I3Pager::getMode() {
    return mode;
}
