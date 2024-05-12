/*  -*- c++ -*-
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#pragma once

#include "workspace.h"
#include <QObject>

class I3ListenerThread;
class Workspace;

class I3Pager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentScreen READ getCurrentScreen WRITE setCurrentScreen)
    Q_PROPERTY(QString mode READ getMode NOTIFY modeChanged)

public:
    explicit I3Pager(QObject* parent = 0);
    ~I3Pager();

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
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
    I3ListenerThread* i3ListenerThread;
    QString currentScreenPrivate;
    QString mode;
};
