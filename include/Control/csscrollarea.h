#ifndef CSSCROLLAREA_H
#define CSSCROLLAREA_H

#include "Control/cswidget.h"

namespace cs
{ // Start of namespace `cs`

namespace cs
{

class CSUTILS_EXPORT CSScrollArea : public CSWidget
{
    Q_OBJECT

public:
    CSScrollArea(QWidget *parent = nullptr);
    virtual ~CSScrollArea() override;

    void setWidget(QWidget *wgt);
    QWidget *getWidget() const;
    void moveWidget(int x, int y);
    void moveWidget(const QPoint &pos);

protected:
    virtual void initMember() override;
    virtual void initUI() override;
    virtual void initSignalSlot() override;

    void drawHorizontalBar(QPainter &p);
    void drawVerticalBar(QPainter &p);

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

protected:
    void updateWidgetPosition(const QPoint &oldPos, const QPoint &newPos);
    QRect getProgressRect(bool isHorizontal) const;
    QRect getBarRect(bool isHorizontal) const;
    bool isOnProgress(const QPoint &point, bool isHorizontal) const;
    bool isOnBar(const QPoint &point, bool isHorizontal) const;

protected:
    bool _showHorizontalBar;
    bool _showVerticalBar;
    bool _activeHProgress;
    bool _activeVProgress;
    QPoint _lastPos;
    QPoint _lastWgtPos;
    QWidget *_wgt;

};

<<<<<<< HEAD:include/Control/csscrollarea.h
}   // End of namespace `cs`

=======
}
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013:src/csutils/csscrollarea.h

#endif // CSSCROLLAREA_H
