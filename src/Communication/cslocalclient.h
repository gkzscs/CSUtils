#ifndef CSLocalClient_H
#define CSLocalClient_H

#include "csipchelper.h"


namespace cs
{

// Each app should contains a `CSLocalClient` object in its main window,
// used to communicate with other app
class CSUTILS_EXPORT CSLocalClient : public QObject
{
    Q_OBJECT

public:
    CSLocalClient(QWidget *wnd);
    virtual ~CSLocalClient() override;

    void setServerName(const QString &name);
    bool connect2Server();
    bool disconnectFromServer();
    QString serverName() const;
    QLocalSocket *socket() const;

    void sendCommand(const QString &appName, CSIpcHelper::Command cmd);

protected:
    void initMember();
    void initSignalSlot();

private:
    void hideWindow();
    void showWindow();
    void exitApp();

protected slots:
    void connectedSlot();
    void disconnectedSlot();
    void readyReadSlot();

protected:
    QWidget *_wnd;
    QLocalSocket *_client;
    QString _serverName;

};

}   // End of `cs`

#endif // CSLocalClient_H
