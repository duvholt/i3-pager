#include "i3listener.h"

I3ListenerThread::I3ListenerThread(QObject* parent)
    : QThread(parent) {
}

void I3ListenerThread::run() {
    while (!stopping) {
        this->handleI3Events();
        // sleep 100ms to avoid log spamming on i3 crash or reload
        this->msleep(100);
    }
}

void I3ListenerThread::handleI3Events() {
    try {
        i3ipc::connection conn;
        conn.subscribe(i3ipc::ET_WORKSPACE | i3ipc::ET_BINDING | i3ipc::ET_MODE);

        // Workspace events handler
        conn.signal_workspace_event.connect([this](const i3ipc::workspace_event_t& ev) {
            qDebug() << "workspace_event: " << (char)ev.type;
            if (ev.current) {
                qDebug() << "\tSwitched to #" << ev.current->num << " - \"" << QString::fromStdString(ev.current->name) << '"';
                Q_EMIT workspacesChanged();
            }
        });

        // Mode events handler
        conn.signal_mode_event.connect([this](const i3ipc::mode_t& i3mode) {
            const auto mode = QString::fromStdString(i3mode.change);
            qDebug() << "mode: " << mode;
            Q_EMIT modeChanged(mode);
        });

        while (!stopping) {
            conn.handle_event();
        }
    } catch (std::exception const& e) {
        qWarning() << "Exception in i3listener handle events:" << e.what();
        this->stop();
    }
}

void I3ListenerThread::stop() {
    this->stopping = true;
    // Not good practice, but i3ipc::conn.handle_event is blocking on read
    // and I don't know how to interrupt that
    this->terminate();
}
