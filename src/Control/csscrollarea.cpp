#include "csscrollarea.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QDebug>


namespace cs
{ // Start of namespace `cs`

CSScrollArea::CSScrollArea(QWidget *parent)
    : CSWidget(parent)
{
    initMember();
}

CSScrollArea::~CSScrollArea()
{
    _wgt = nullptr;
//    if (_wgt) _wgt->deleteLater();
}

void CSScrollArea::setWidget(QWidget *wgt)
{
    _wgt = wgt;
    if (_wgt) _wgt->setParent(this);
}

QWidget *CSScrollArea::getWidget() const
{
    return _wgt;
}

void CSScrollArea::initMember()
{
    _showHorizontalBar = true;
    _showVerticalBar = true;
    _activeHProgress = false;
    _activeVProgress = false;
    _wgt = nullptr;
}

void CSScrollArea::drawHorizontalBar(QPainter &p)
{
    if (!_wgt) return;
    p.save();

    // Base bar
    const int n = 5;
    QPen pen(Qt::transparent);
    pen.setWidth(n);
    pen.setCapStyle(Qt::RoundCap);
    p.setPen(pen);
    p.drawLine(0, height()-n/2, width(), height()-n/2);

    // Pointer bar
    pen.setColor(Qt::gray);
    p.setPen(pen);
    int x = static_cast<int>(width() * (std::abs(_wgt->x()) / static_cast<double>(_wgt->width())));
    int w = static_cast<int>(width() * (width() / static_cast<double>(_wgt->width())));
    p.drawLine(x, height()-n/2, x+w, height()-n/2);

    // Must add `update()` function, but I don't know why
//    update();
    p.restore();
}

void CSScrollArea::drawVerticalBar(QPainter &p)
{
    if (!_wgt) return;
    p.save();

    // Base bar
    const int n = 5;
    QPen pen(Qt::transparent);
    pen.setWidth(n);
    pen.setCapStyle(Qt::RoundCap);
    p.setPen(pen);
    p.drawLine(width()-n/2, 0, width()-n/2, height());

    // Pointer bar
    pen.setColor(Qt::gray);
    p.setPen(pen);
    int y = static_cast<int>(height() * (std::abs(_wgt->y()) / static_cast<double>(_wgt->height())));
    int h = static_cast<int>(height() * (height() / static_cast<double>(_wgt->height())));
    p.drawLine(width()-n/2, y, width()-n/2, y+h);

    // Must add `update()` function, but I don't know why
//    update();
    p.restore();

}

void CSScrollArea::paintEvent(QPaintEvent *event)
{
    CSWidget::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    if (_showHorizontalBar && _wgt && _wgt->width() > width()) drawHorizontalBar(p);
    if (_showVerticalBar && _wgt && _wgt->height() > height()) drawVerticalBar(p);
}

void CSScrollArea::mousePressEvent(QMouseEvent *event)
{
    _lastPos = event->pos();
    _lastWgtPos = _wgt->pos();
    if (isOnProgress(_lastPos, true)) _activeHProgress = true;
    else if (isOnProgress(_lastPos, false)) _activeVProgress = true;
}

void CSScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    updateWidgetPosition(_lastPos, event->pos());
}

void CSScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

    _activeHProgress = false;
    _activeVProgress = false;
}

void CSScrollArea::wheelEvent(QWheelEvent *event)
{
    int offY = event->delta();
    moveWidget(_wgt->x(), _wgt->y()+offY);
}

void CSScrollArea::updateWidgetPosition(const QPoint &oldPos, const QPoint &newPos)
{
    if (_activeHProgress)
    {
        int offX = static_cast<int>((newPos.x()-oldPos.x()) / static_cast<double>(width()) * _wgt->width());
        moveWidget(_lastWgtPos.x()-offX, _lastWgtPos.y());
    }
    else if (_activeVProgress)
    {
        int offY = static_cast<int>((newPos.y()-oldPos.y()) / static_cast<double>(height()) * _wgt->height());
        moveWidget(_lastWgtPos.x(), _lastWgtPos.y()-offY);
    }
}

void CSScrollArea::moveWidget(int x, int y)
{
    if (!_wgt) return;

    const int minX = width() - _wgt->width();
    const int minY = height() - _wgt->height();

    if (x < minX) x = minX;
    if (x > 0) x = 0;
    if (y < minY) y = minY;
    if (y > 0) y = 0;

    _wgt->move(x, y);
}

void CSScrollArea::moveWidget(const QPoint &pos)
{
    moveWidget(pos.x(), pos.y());
}

QRect CSScrollArea::getProgressRect(bool isHorizontal) const
{
    const int n = 5*2;
    QRect rect;

    if (isHorizontal)
    {
        int x = static_cast<int>(width() * (std::abs(_wgt->x()) / static_cast<double>(_wgt->width())));
        int w = static_cast<int>(width() * (width() / static_cast<double>(_wgt->width())));
        rect = QRect(x, height()-n, w, n);
    }
    else
    {
        int y = static_cast<int>(height() * (std::abs(_wgt->y()) / static_cast<double>(_wgt->height())));
        int h = static_cast<int>(height() * (height() / static_cast<double>(_wgt->height())));
        rect = QRect(width()-n, y, n, h);
    }

    return rect;
}

QRect CSScrollArea::getBarRect(bool isHorizontal) const
{
    const int n = 5;
    QRect rect;

    if (isHorizontal)
    {
        rect = QRect(0, height()-n/2, width(), height()-n/2);
    }
    else
    {
        rect = QRect(width()-n/2, 0, width()-n/2, height());
    }

    return rect;
}

bool CSScrollArea::isOnProgress(const QPoint &point, bool isHorizontal) const
{
    QRect rect = getProgressRect(isHorizontal);
    return rect.contains(point);
}

bool CSScrollArea::isOnBar(const QPoint &point, bool isHorizontal) const
{
    QRect rect = getBarRect(isHorizontal);
    return rect.contains(point);
}

} // End of namespace `cs`






