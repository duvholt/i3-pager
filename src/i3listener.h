#ifndef I3LISTENER_H
#define I3LISTENER_H

#include <QDebug>
#include <QLocalSocket>
#include <QSocketNotifier>
#include <QThread>
#include <QtCore/QObject>
#include <i3ipc++/ipc.hpp>

// rewrite to qthread subclass?


class I3ListenerThread : public QThread {
    Q_OBJECT

public:
    explicit I3ListenerThread(QObject* parent = 0);
    void run() override;
    void stop();

Q_SIGNALS:
    void workspacesChanged();
    void modeChanged(const QString& mode);

private:
    bool stopping = false;
    void handleI3Events();
};


class I3Listener : public QObject {
    Q_OBJECT

public:
    explicit I3Listener(QObject* parent = 0);
    ~I3Listener();

Q_SIGNALS:
    void workspacesChanged();
    void modeChanged(const QString& mode);

private:
    I3ListenerThread* i3ListenerThread;
};

#endif //I3LISTENER_H
