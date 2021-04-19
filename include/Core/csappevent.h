#ifndef CSAppEvent_H
#define CSAppEvent_H

#include <QObject>


namespace cs
{

class CSUTILS_EXPORT CSAppEvent : public QObject
{
    Q_OBJECT

public:
    virtual ~CSAppEvent() override;

    static CSAppEvent *instance();

private:
    CSAppEvent();

signals:
    void clickSignal(QObject *sender, QWidget *target);
    void doubleClickSignal(QObject *sender, QWidget *target);
    void foldChangeSignal(QObject *sender, bool flag);
    void sendItemSignal(QObject *sender, QWidget *item);
    void receiveItemSignal(QObject *sender, int idx, QWidget *item);
    void resizeSignal(QObject *s, QResizeEvent *e);
    void showEditSignal(QObject *sender);
    void refreshDataSignal(QObject *s);

private:
    static CSAppEvent *_instance;

};

}

#endif // CSAppEvent_H
