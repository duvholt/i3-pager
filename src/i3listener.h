/*  -*- c++ -*-
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#pragma  once

#include <QThread>

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
