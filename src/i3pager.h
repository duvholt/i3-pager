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
    Q_PROPERTY(QString currentScreen WRITE setCurrentScreen)
    Q_PROPERTY(QList<Workspace> workspaces READ getWorkspaces NOTIFY workspacesChanged)
    Q_PROPERTY(QString mode READ getMode NOTIFY modeChanged)

public:
    explicit I3Pager(QObject* parent = 0);

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
    Q_INVOKABLE void activateWorkspace(QString workspace);

public Q_SLOTS:
    QList<Workspace> getWorkspaces();
    QString getMode();

Q_SIGNALS:
    void workspacesChanged();
    void modeChanged();

private:
    QString currentScreenPrivate;
    QString mode;
    void handleI3Events();
};

#endif I3PAGER_PLASMOID_H
