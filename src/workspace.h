#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QDebug>
#include <QtCore/QObject>

class Workspace {
    Q_GADGET
    Q_PROPERTY(QString id MEMBER id)
    Q_PROPERTY(QString index MEMBER index)
    Q_PROPERTY(QString name MEMBER name)
    Q_PROPERTY(QString icon MEMBER icon)
    Q_PROPERTY(QString output MEMBER output)
    Q_PROPERTY(bool focused MEMBER focused)
    Q_PROPERTY(bool visible MEMBER visible)
    Q_PROPERTY(bool urgent MEMBER urgent)
public:
    static QList<Workspace> filterByCurrentScreen(QList<Workspace> inputWorkspaces, QString currentScreen);
    QString id;
    QString index;
    QString name;
    QString icon;
    QString output;
    bool focused;
    bool visible;
    bool urgent;
};

Q_DECLARE_METATYPE(Workspace)

#endif //WORKSPACE_H
