#ifndef CSSCROLLAREA_H
#define CSSCROLLAREA_H

#include "cswidget.h"


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


#endif // CSSCROLLAREA_H
