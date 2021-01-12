#ifndef CSAppConnector_H
#define CSAppConnector_H

#include <map>
#include "csutils_stable.h"


namespace cs
{

class CSUTILS_EXPORT CSAppConnector
{  
public:
    enum Command
    {
        Register,
        Show,
        Hide,
        Exit
    };

public:
    explicit CSAppConnector(unsigned wndId);
    virtual ~CSAppConnector();

    void setServerName(const char *name);
    char *serverName() const;

    virtual bool connect2Server() = 0;
    virtual bool disconnectFromServer() = 0;

    virtual void bootApp(const char *appUrl) = 0;
    virtual void sendCommand(const char *appName, Command cmd) = 0;

protected:
    void initMember();
    void initSignalSlot();

protected:
    void connectedSlot();
    void disconnectedSlot();
    void readyReadSlot();

protected:
    unsigned _wndId;
    char *_serverName;
    //    QLocalSocket *_client;

    std::map<Command, const char *> _mapCmdStr;

};

}   // End of `cs`

#endif // CSAppConnector_H
