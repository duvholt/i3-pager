#ifndef I3PAGER_PLASMOID_H
#define I3PAGER_PLASMOID_H

#include "workspace.h"
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QMetaType>
#include <QScreen>
#include <QVariant>
#include <QtConcurrent/QtConcurrent>
#include <QtCore/QObject>
#include <future>
#include <i3ipc++/ipc.hpp>

class I3Pager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentScreen READ getCurrentScreen WRITE setCurrentScreen)
    Q_PROPERTY(bool monitorForEvents WRITE setMonitorForEvents)
    Q_PROPERTY(QString mode READ getMode NOTIFY modeChanged)

public:
    explicit I3Pager(QObject* parent = 0);
    ~I3Pager();

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
    void setMonitorForEvents(bool monitorForEvents);
    Q_INVOKABLE void activateWorkspace(QString workspace);

public Q_SLOTS:
    QString getCurrentScreen();
    QList<Workspace> getWorkspaces(bool filterByCurrentScreen, QString orderWorkspacesBy, QList<QString> screenOrder);
    QList<QString> getScreenNames();
    QString getMode();

Q_SIGNALS:
    void workspacesChanged();
    void modeChanged();

private:
    QString currentScreenPrivate;
    QString mode;
    QFuture<void> i3ipcFuture;
    void handleI3Events();
};

#endif //I3PAGER_PLASMOID_H
