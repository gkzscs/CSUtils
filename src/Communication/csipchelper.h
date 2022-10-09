#ifndef CSIpcHelper_H
#define CSIpcHelper_H

#include <QObject>
#include <QMap>
#include "csutils_global.h"

static const QString environmetVarsConfigJson = "./config/environment_vars.json";

class QLocalSocket;

namespace cs
{

class CSUTILS_EXPORT CSIpcHelper : public QObject
{
    Q_OBJECT

public:
    enum Command
    {
        Unknown,
        Register,
        Show,
        Hide,
        Boot,
        Exit,
        Reboot
    };

public:
    static CSIpcHelper *instance();
    ~CSIpcHelper();

    void addEnvironmentVars();          // 增加运行环境变量
    void bootApp(const QString &appUrl);
    void sendCommand(QLocalSocket *sock, const QString &appName, Command cmd);
    void sendCommand(QLocalSocket *sock, const QString &appName);
    QString cmdStr(Command cmd) const;
    QPair<QString, Command> parseAppNameCommand(QString msg) const;

protected:
    void initMember();

private:
    CSIpcHelper();

protected:
    static CSIpcHelper *_instance;
    QMap<Command, QString> _mapCmdStr;
    QStringList _lstEnvironmentVars;    // 增加的环境变量
};

}   // End of `cs`

#endif // CSIpcHelper_H
