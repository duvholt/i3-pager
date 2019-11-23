#ifndef I3PAGER_PLASMOID_H
#define I3PAGER_PLASMOID_H



#include <QtCore/QObject>
#include <QVariant>

class I3Pager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString currentScreen WRITE setCurrentScreen)
    Q_PROPERTY(QVariantList workspaces READ getWorkspaces NOTIFY currentScreenChanged)
    Q_PROPERTY(QString mode READ getMode NOTIFY modeChanged)

public:
    explicit I3Pager(QObject *parent = 0);

    QString getCurrentScreen() const;
    void setCurrentScreen(QString screen);
    Q_INVOKABLE void activateWorkspace(QString workspace);

public Q_SLOTS:
    QVariantList getWorkspaces();
    QString getMode();

Q_SIGNALS:
    void currentScreenChanged();
    void modeChanged();

private:
    QString currentScreenPrivate;
    QString mode;
    void poll();
};


#endif //I3PAGER_PLASMOID_H
