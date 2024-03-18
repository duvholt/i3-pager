#ifndef I3LISTENER_H
#define I3LISTENER_H

#include <QDebug>
#include <QLocalSocket>
#include <QSocketNotifier>
#include <QThread>
#include <QtCore/QObject>
#include <i3ipc++/ipc.hpp>

class I3ListenerThread : public QThread {
    Q_OBJECT

public:
    explicit I3ListenerThread(QObject* parent = nullptr);
    void run() override;
    void stop();

Q_SIGNALS:
    void workspacesChanged();
    void modeChanged(const QString& mode);

private:
    bool stopping = false;
    void handleI3Events();
};

#endif //I3LISTENER_H
