#ifndef CSIpcHelper_H
#define CSIpcHelper_H

#include <QObject>
#include <QMap>
#include "csutils_global.h"


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
        Exit
    };

public:
    static CSIpcHelper *instance();
    ~CSIpcHelper();

    void bootApp(const QString &appUrl);
    void sendCommand(QLocalSocket *sock, const QString &appName, Command cmd);

    QString cmdStr(Command cmd) const;
    QPair<QString, Command> parseAppNameCommand(QString msg) const;

protected:
    void initMember();

private:
    CSIpcHelper();

protected:
    static CSIpcHelper *_instance;
    QMap<Command, QString> _mapCmdStr;

};

}   // End of `cs`

#endif // CSIpcHelper_H
