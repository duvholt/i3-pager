#ifndef I3PAGER_PLASMOID_H
#define I3PAGER_PLASMOID_H



#include <QtCore/QObject>

class I3Pager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString getMessage READ getMessage NOTIFY currentScreenChanged)
    Q_PROPERTY(QString currentScreen READ getCurrentScreen WRITE setCurrentScreen NOTIFY currentScreenChanged)
    Q_PROPERTY(QStringList workspaces READ getWorkspaces NOTIFY currentScreenChanged)

public:
    explicit I3Pager(QObject *parent = 0);

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
    Q_INVOKABLE void activateWorkspace(QString workspace);

public Q_SLOTS:
    QString getMessage();
    QStringList getWorkspaces();

Q_SIGNALS:
    void currentScreenChanged();

private:
    QString currentScreenPrivate;
};


#endif //I3PAGER_PLASMOID_H
