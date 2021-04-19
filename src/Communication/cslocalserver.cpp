#include "cslocalserver.h"
#include <QLocalServer>


namespace cs
{

CSLocalServer::CSLocalServer(QObject *parent)
    : QObject(parent)
{
    initMember();
    initSignalSlot();
}

CSLocalServer::~CSLocalServer()
{
    _server->deleteLater();

    qDeleteAll(_listClients);
    _listClients.clear();
}

QLocalServer *CSLocalServer::server() const
{
    return _server;
}

QList<QLocalSocket *> CSLocalServer::clientList() const
{
    return _listClients;
}

void CSLocalServer::bootApp(const QString &appUrl)
{
    CSIpcHelper::instance()->bootApp(appUrl);
}

void CSLocalServer::sendCommand(const QString &appName, CSIpcHelper::Command cmd)
{
    for (auto client : _listClients)
    {
        if (client->objectName() != appName) continue;

        // Only one client could receive the command
        CSIpcHelper::instance()->sendCommand(client, appName, cmd);
        break;
    }
}

// Send command to all connected clients
void CSLocalServer::sendCommand2AllClients(CSIpcHelper::Command cmd)
{
    for (auto client : _listClients)
    {
        CSIpcHelper::instance()->sendCommand(client, client->objectName(), cmd);
    }
}

void CSLocalServer::initMember()
{
    _server = new QLocalServer(this);
    _server->listen(QApplication::applicationName());
}

void CSLocalServer::initSignalSlot()
{
    connect(_server, &QLocalServer::newConnection, this, &CSLocalServer::connectedSlot);
}

void CSLocalServer::dealCommand(QLocalSocket *client, const QString &appName, CSIpcHelper::Command cmd)
{
    if (!client) return;

    switch (cmd)
    {
    case CSIpcHelper::Unknown:
    case CSIpcHelper::Show:
    case CSIpcHelper::Hide:
    case CSIpcHelper::Exit:
        break;
    case CSIpcHelper::Register:
        client->setObjectName(appName);
        break;
    case CSIpcHelper::Boot:
        // To modify
        bootApp(appName);
        break;
    }

    sendCommand(appName, cmd);
}

void CSLocalServer::connectedSlot()
{
    bool res = _server->hasPendingConnections();
    if (!res) return;

    auto client = _server->nextPendingConnection();
    if (!client) return;

    _listClients.append(client);

    connect(client, &QLocalSocket::disconnected, this, &CSLocalServer::disconnectedSlot);
    connect(client, &QLocalSocket::readyRead, this, &CSLocalServer::readyReadSlot);
}

void CSLocalServer::disconnectedSlot()
{
    auto client = dynamic_cast<QLocalSocket *>(sender());
    if (!client) return;

    _listClients.removeAll(client);

    disconnect(client, &QLocalSocket::disconnected, this, &CSLocalServer::disconnectedSlot);
    disconnect(client, &QLocalSocket::readyRead, this, &CSLocalServer::readyReadSlot);
}

void CSLocalServer::readyReadSlot()
{
    auto client = dynamic_cast<QLocalSocket *>(sender());
    if (!client) return;

    // Get message
    QString msg = client->readAll();
    auto pairNameCmd = CSIpcHelper::instance()->parseAppNameCommand(msg);

    // Deal commands
    dealCommand(client, pairNameCmd.first, pairNameCmd.second);
}

}   // End of `cs`
