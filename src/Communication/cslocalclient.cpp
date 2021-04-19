#include "cslocalclient.h"
#include <QWidget>
#include <QApplication>
#include <QProcess>
#include <QThread>
#include <QLocalSocket>


namespace cs
{

CSLocalClient::CSLocalClient(QWidget *wnd)
    : QObject(wnd), _wnd(wnd)
{
    initMember();
    initSignalSlot();
}

CSLocalClient::~CSLocalClient()
{
    _serverName = nullptr;
    _wnd = nullptr;
    _client->deleteLater();
}

void CSLocalClient::setServerName(const QString &name)
{
    _serverName = name;

    // To do, whether need to check current server that is connected?
//    if (_client->serverName() != _serverName && _client->isOpen())
//    {
//        disconnectFromServer();
//        connect2Server();
//    }
}

bool CSLocalClient::connect2Server()
{
    _client->connectToServer(_serverName);
    bool res = _client->waitForConnected();
    if (!res)
    {
        qDebug() << QApplication::applicationName() << "failed to connect to server:" << _serverName;
    }

    return res;
}

bool CSLocalClient::disconnectFromServer()
{
    _client->disconnectFromServer();
    // To modify, this code may not work well?
    bool res = _client->waitForDisconnected();
    if (!res)
    {
        qDebug() << QApplication::applicationName() << "failed to disconnect from server:" << _serverName;
    }

    return res;
}

QString CSLocalClient::serverName() const
{
    return _serverName;
}

QLocalSocket *CSLocalClient::socket() const
{
    return _client;
}

void CSLocalClient::sendCommand(const QString &appName, CSIpcHelper::Command cmd)
{
    CSIpcHelper::instance()->sendCommand(_client, appName, cmd);
}

void CSLocalClient::initMember()
{
    _client = new QLocalSocket(this);
}

void CSLocalClient::initSignalSlot()
{
    connect(_client, &QLocalSocket::connected, this, &CSLocalClient::connectedSlot);
    connect(_client, &QLocalSocket::disconnected, this, &CSLocalClient::disconnectedSlot);
    connect(_client, &QLocalSocket::readyRead, this, &CSLocalClient::readyReadSlot);
}

void CSLocalClient::hideWindow()
{
    if (!_wnd) return;

    _wnd->hide();
}

void CSLocalClient::showWindow()
{
    if (!_wnd) return;

    _wnd->setWindowFlag(Qt::WindowStaysOnTopHint);
    _wnd->setWindowModality(Qt::ApplicationModal);
    _wnd->showNormal();
}

void CSLocalClient::exitApp()
{
    QApplication::exit(0);
}

void CSLocalClient::connectedSlot()
{
    qDebug() << QApplication::applicationName() << "connected to the server:" << _serverName;

    // If connected, then auto register itself to server
    sendCommand(QApplication::applicationName(), CSIpcHelper::Register);
}

void CSLocalClient::disconnectedSlot()
{
    qDebug() << QApplication::applicationName() << "disconnected from the server:" << _serverName;
}

void CSLocalClient::readyReadSlot()
{
    QString str = _client->readAll();
    auto inst = CSIpcHelper::instance();

    if (str.contains(inst->cmdStr(CSIpcHelper::Register))) qDebug() << "Registerd client:" << QApplication::applicationName();
    else if (str.contains(inst->cmdStr(CSIpcHelper::Show))) showWindow();
    else if (str.contains(inst->cmdStr(CSIpcHelper::Hide))) hideWindow();
    else if (str.contains(inst->cmdStr(CSIpcHelper::Exit))) exitApp();
}

}   // End of `cs`
