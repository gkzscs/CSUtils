#ifndef CSSCROLLAREA_H
#define CSSCROLLAREA_H

#include "Control/Base/cswidget.h"


namespace cs
{ // Start of namespace `cs`

class CSUTILS_EXPORT CSScrollArea : public CSWidget
{
    Q_OBJECT

public:
    CSScrollArea(QWidget *parent = nullptr);
    ~CSScrollArea() override;

    void setWidget(QWidget *wgt);
    QWidget *getWidget() const;
    void moveWidget(int x, int y);
    void moveWidget(const QPoint &pos);

protected:
    void initMember();
    void initSignalSlot();

    void drawHorizontalBar(QPainter &p);
    void drawVerticalBar(QPainter &p);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

protected:
    void updateWidgetPosition();
    void updateWidgetPosition(const QPoint &oldPos, const QPoint &newPos);
    QRect getProgressRect(bool isHorizontal) const;
    QRect getBarRect(bool isHorizontal) const;
    bool isOnProgress(const QPoint &point, bool isHorizontal) const;
    bool isOnBar(const QPoint &point, bool isHorizontal) const;

protected slots:
    void resizeSlot(QObject *s, QResizeEvent *e);

protected:
    bool _showHorizontalBar;
    bool _showVerticalBar;
    bool _activeHProgress;
    bool _activeVProgress;
    QPoint _lastPos;
    QPoint _lastWgtPos;
    QWidget *_wgt;

};

}   // End of namespace `cs`

#endif // CSSCROLLAREA_H
