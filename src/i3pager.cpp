#include "i3pager.h"

I3Pager::I3Pager(QObject* parent)
    : QObject(parent) {
    currentScreenPrivate = QString();
    mode = "default";

    qDebug() << "Starting i3 listener";
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
    qDebug() << "i3 listener started";
}

I3Pager::~I3Pager() {
    qDebug() << "I3Pager destructor";
    this->i3ListenerThread->stop();
    this->i3ListenerThread->wait();
    qDebug() << "I3Pager destructor done";
}

QList<QString> I3Pager::getScreenNames() {
    QList<QString> screenList;
    try {
        i3ipc::connection conn;
        auto screens = conn.get_outputs();

        for (auto& screen : screens) {
            if (screen->active) {
                screenList.append(QString::fromStdString(screen->name));
                qDebug() << "Screen name:" << QString::fromStdString(screen->name);
            }
        }
    } catch (std::exception const& e) {
        qWarning() << "Exception while retrieving screen names: " << e.what();
    }

    return screenList;
}

QList<Workspace> I3Pager::getWorkspaces(bool filterByCurrentScreen, QString orderWorkspacesBy, QList<QString> screenOrder) {
    QList<Workspace> workspaceList;
    try {
        i3ipc::connection conn;
        auto i3workspaceList = conn.get_workspaces();
        qDebug() << "Loading workspaces:";
        qDebug() << "Variables,CurrentScreen:"<<filterByCurrentScreen<<", orderBy:"<<orderWorkspacesBy;

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

            qDebug() << "i3Workspace name:" << QString::fromStdString(i3workspace->name);
            qDebug() << "Workspace:"
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
        qWarning() << "Exception while retrieving workspaces:" << e.what();
    }

    if (filterByCurrentScreen) {
        workspaceList = Workspace::filterByCurrentScreen(workspaceList, this->currentScreenPrivate);
    }

    if (orderWorkspacesBy == "screen" && !screenOrder.isEmpty()) {
        workspaceList = Workspace::orderByOutput(workspaceList, screenOrder);
    }
    else if (orderWorkspacesBy == "name"){
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
