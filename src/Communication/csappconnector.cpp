#include "csappconnector.h"


namespace cs
{

CSAppConnector::CSAppConnector(unsigned wndId)
    : _wndId(wndId)
{
    initMember();
    initSignalSlot();
}

CSAppConnector::~CSAppConnector()
{
    _serverName = nullptr;
//    _client->deleteLater();

    _mapCmdStr.clear();
}

void CSAppConnector::setServerName(const char *name)
{
    strcpy_s(_serverName, strlen(name), name);

    // To do, whether need to check current server that is connected?
}

char *CSAppConnector::serverName() const
{
    return _serverName;
}

void CSAppConnector::initMember()
{
    _serverName = nullptr;
//    _client = new QLocalSocket(this);

    // Initialize the container
    _mapCmdStr.insert(std::make_pair(Register, "register"));
    _mapCmdStr.insert(std::make_pair(Show, "show"));
    _mapCmdStr.insert(std::make_pair(Hide, "hide"));
    _mapCmdStr.insert(std::make_pair(Exit, "exit"));
}

void CSAppConnector::initSignalSlot()
{
    // To do
}

void CSAppConnector::sendCommand(const char *appName, Command cmd)
{
    Q_UNUSED(appName)
    Q_UNUSED(cmd)

//    // Get the information to send
//    QString info("%1:%2");
//    info = info.arg(appName).arg(_mapCmdStr.value(cmd));

//    // Write to local socket
//    _client->write(info.toUtf8());
//    _client->flush();
}

void CSAppConnector::connectedSlot()
{
    // To do
}

void CSAppConnector::disconnectedSlot()
{
    // To do
}

void CSAppConnector::readyReadSlot()
{
//    QString str = _client->readAll();

//    if (str.contains("show")) showWindow();
//    else if (str.contains("hide")) hideWindow();
//    else if (str.contains("exit")) exitApp();
}

}   // End of `cs`

