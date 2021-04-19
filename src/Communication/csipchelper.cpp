#include "csipchelper.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QThread>
#include <QProcess>


namespace cs
{

CSIpcHelper *CSIpcHelper::_instance = nullptr;

CSIpcHelper *CSIpcHelper::instance()
{
    if (!_instance) _instance = new CSIpcHelper();

    return _instance;
}

CSIpcHelper::~CSIpcHelper()
{
    _instance = nullptr;
    _mapCmdStr.clear();
}

void CSIpcHelper::bootApp(const QString &appUrl)
{
    // Boot other applications in another seperated thread, to avoid block
    QThread *thread = new QThread(this);
    QProcess process;
    process.moveToThread(thread);

    // Start the process
    bool res = process.startDetached(appUrl);
    if (!res)
    {
        qDebug() << "Failed to start process:" << appUrl;
    }

//    QTime dieTime = QTime::currentTime().addSecs(2);
//    while (QTime::currentTime() < dieTime) QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    thread->quit();
}

void CSIpcHelper::sendCommand(QLocalSocket *sock, const QString &appName, Command cmd)
{
    // Get the information to send
    QString info("%1:%2");
    info = info.arg(appName).arg(_mapCmdStr.value(cmd));

    // Write to local socket
    sock->write(info.toUtf8());
    sock->flush();
}

QString CSIpcHelper::cmdStr(Command cmd) const
{
    return _mapCmdStr.value(cmd);
}

QPair<QString, CSIpcHelper::Command> CSIpcHelper::parseAppNameCommand(QString msg) const
{
    QRegExp re("^([a-zA-Z0-9_]+):([a-zA-Z0-9_]+)$");

    // Get the matched strings
    int pos = re.indexIn(msg);
    if (pos < 0) return qMakePair<QString, Command>(nullptr, CSIpcHelper::Unknown);

    // Get app name and cmd
    QString appName = re.cap(1);
    CSIpcHelper::Command cmd = _mapCmdStr.key(re.cap(2));

    return qMakePair<QString, Command>(appName, cmd);
}

void CSIpcHelper::initMember()
{
    _instance = nullptr;

    // Initialize the container
    QStringList listStr;
    listStr << "unknown" << "register" << "show" << "hide" << "boot" << "exit";
    for (int i = 0; i < listStr.size(); ++i)
    {
        auto cmd = static_cast<Command>(i);
        _mapCmdStr.insert(cmd, listStr.at(i));
    }
}

CSIpcHelper::CSIpcHelper()
    : QObject(nullptr)
{
    initMember();
}

}   // End of `cs`
