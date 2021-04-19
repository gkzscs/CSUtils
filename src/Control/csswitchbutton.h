#ifndef CSSWITCHBUTTON_H
#define CSSWITCHBUTTON_H

#include <QWidget>
#include "csutils_global.h"


namespace cs
{

class CSUTILS_EXPORT CSSwitchButton : public QWidget
{
    Q_OBJECT

public:
    CSSwitchButton(QWidget *parent = nullptr);
    virtual ~CSSwitchButton() override;

    void switchOn(bool flag);
    bool isOn() const;

protected:
    void initMember();
    void initUI();
    void initSignalSlot();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

protected:
    void drawBorder(QPainter &p);
    void drawCore(QPainter &p);

protected:
    QRect calcCoreRect();
    QRect calcRightBorderRect();

signals:
    void switchSignal(bool flag);

protected:
    bool _isOn;
    int _coreX;

    QTimer *_timer;

};

}   // End of `cs`

#endif // CSSWITCHBUTTON_H
