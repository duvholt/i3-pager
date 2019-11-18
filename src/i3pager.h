#ifndef I3PAGER_PLASMOID_H
#define I3PAGER_PLASMOID_H



#include <QtCore/QObject>
#include <QVariant>

class I3Pager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentScreen READ getCurrentScreen WRITE setCurrentScreen NOTIFY currentScreenChanged)
    Q_PROPERTY(QVariantList workspaces READ getWorkspaces NOTIFY currentScreenChanged)

public:
    explicit I3Pager(QObject *parent = 0);

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
    Q_INVOKABLE void activateWorkspace(QString workspace);

public Q_SLOTS:
    QVariantList getWorkspaces();

Q_SIGNALS:
    void currentScreenChanged();

private:
    QString currentScreenPrivate;
    void poll();
};


#endif //I3PAGER_PLASMOID_H
