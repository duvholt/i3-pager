#include "i3listener.h"

I3ListenerThread::I3ListenerThread(QObject* parent)
    : QThread(parent) {
}

void I3ListenerThread::run() {
    // // while (!this->stopping) {
    // this->handleI3Events();
    // qWarning() << "Lost ipc connection";
    // // QThread::sleep(10);
    // // QTimer::singleShot(200, this, &Foo::updateCaption);
    // // }
    while (!stopping) {
        this->handleI3Events();
        this->msleep(100);
    }
}

void I3ListenerThread::handleI3Events() {
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

        conn.signal_mode_event.connect([this](const i3ipc::mode_t& i3mode) {
            const auto mode = QString::fromStdString(i3mode.change);
            qInfo() << "mode: " << mode;
            Q_EMIT modeChanged(mode);
        });

        while (!stopping) {
            conn.handle_event();
        }
    } catch (std::exception const& e) {
        qWarning() << "Exception in i3listener handle events:" << e.what();
    }
}

void I3ListenerThread::stop() {
    this->stopping = true;
    // Not good practice, but i3ipc::conn.handle_event is blocking on read
    // and I don't know how to interrupt that
    this->terminate();
}

I3Listener::I3Listener(QObject* parent)
    : QObject(parent) {
    qDebug() << "Starting i3 listener";
    this->i3ListenerThread = new I3ListenerThread(this);
    connect(i3ListenerThread, &I3ListenerThread::modeChanged, this, [=](const QString& mode) {
        Q_EMIT modeChanged(mode);
    });
    connect(i3ListenerThread, &I3ListenerThread::workspacesChanged, this, [=]() {
        Q_EMIT workspacesChanged();
    });
    connect(i3ListenerThread, &I3ListenerThread::finished, i3ListenerThread, &QObject::deleteLater);
    i3ListenerThread->start();
    qDebug() << "i3 listener started";
}

I3Listener::~I3Listener() {
    this->i3ListenerThread->stop();
    this->i3ListenerThread->wait();
}
