#ifndef CSAppEvent_H
#define CSAppEvent_H

#include <QObject>


namespace cs
{

class CSUTILS_EXPORT CSAppEvent : public QObject
{
    Q_OBJECT

public:
    ~CSAppEvent() override;

    static CSAppEvent *instance();

private:
    CSAppEvent();

signals:
    void clickSignal(QObject *sender, QWidget *src, bool leftButton = true);
    void doubleClickSignal(QObject *sender, QWidget *src);
    void statusChangeSignal(QObject *sender, QObject *src, int oldStatus, int newStatus);
    void foldChangeSignal(QObject *sender, QWidget *src, bool flag);
    void sendItemSignal(QObject *sender, QWidget *item);
    void receiveItemSignal(QObject *sender, int idx, QWidget *item);
    void resizeSignal(QWidget *s, QResizeEvent *e);
    void showEditSignal(QObject *sender);
    void refreshDataSignal(QObject *s);

private:
    static CSAppEvent *_instance;

};

}

#endif // CSAppEvent_H
