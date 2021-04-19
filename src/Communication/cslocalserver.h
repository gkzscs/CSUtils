#ifndef CSLocalServer_H
#define CSLocalServer_H

#include "csipchelper.h"


class QLocalServer;
class QLocalSocket;

namespace cs
{

class CSUTILS_EXPORT CSLocalServer : public QObject
{
    Q_OBJECT

public:
    CSLocalServer(QObject *parent = nullptr);
    virtual ~CSLocalServer() override;

    QLocalServer *server() const;
    QList<QLocalSocket *> clientList() const;

    void bootApp(const QString &appUrl);
    void sendCommand(const QString &appName, CSIpcHelper::Command cmd);
    void sendCommand2AllClients(CSIpcHelper::Command cmd);

protected:
    void initMember();
    void initSignalSlot();

protected:
    void dealCommand(QLocalSocket *client, const QString &appName, CSIpcHelper::Command cmd);

protected slots:
    void connectedSlot();
    void disconnectedSlot();
    void readyReadSlot();

protected:
    QLocalServer *_server;
    QList<QLocalSocket *> _listClients;

};

}   // End of `cs`

#endif // CSLocalServer_H
