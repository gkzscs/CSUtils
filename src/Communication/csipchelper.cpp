#include "csipchelper.h"
#include "loggingservice.h"
#include <QLocalSocket>
#include <QLocalServer>
#include <QThread>
#include <QProcess>
#include <QJsonParseError>
#include <QJsonDocument>

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

void CSIpcHelper::addEnvironmentVars()
{
    QFile file(environmetVarsConfigJson);
    if (file.open(QFile::ReadOnly) == false)
    {
        SERVICE_LOG_ERROR("open file faild.");
        return;
    }

    QJsonParseError jsonError;
    QJsonDocument document = QJsonDocument::fromJson(QString(file.readAll()).toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        SERVICE_LOG_ERROR("parse json failed.");
        return;
    }

    QJsonArray pathArray = document.object().value("path").toArray();
    for (int i = 0; i < pathArray.size(); i++)
    {
        _lstEnvironmentVars.push_back(pathArray[i].toString());
    }

    file.close();
}

void CSIpcHelper::bootApp(const QString &appUrl)
{
    // Boot other applications in another seperated thread, to avoid block
    QThread *thread = new QThread(this);
    QProcess process;
    process.moveToThread(thread);

    QString addedEnvVars;
    for (int i = 0; i < _lstEnvironmentVars.size(); i++)
    {
        addedEnvVars += _lstEnvironmentVars.at(i) + ";";
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", addedEnvVars + env.value("PATH"));
    process.setProcessEnvironment(env);

    // Start the process
    bool res = process.startDetached(appUrl);
    if (!res)
    {
        SERVICE_LOG_ERROR("Failed to start process: " + appUrl);
    }

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

void CSIpcHelper::sendCommand(QLocalSocket *sock, const QString &appName)
{
    // Get the information to send
    QString info(appName);

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
    addEnvironmentVars();
}

}   // End of `cs`
