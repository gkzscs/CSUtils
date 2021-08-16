#include "csadjustablewgt.h"
#include <QMouseEvent>


namespace cs
{

CSAdjustableWgt::CSAdjustableWgt(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
}

void CSAdjustableWgt::initMember()
{
    _pressed = false;
    _direction = Unknown;
}

void CSAdjustableWgt::initUI()
{
    // Set attribute
    resize(800, 600);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);
}

void CSAdjustableWgt::mousePressEvent(QMouseEvent *e)
{
    const auto pos = e->pos();

    _pressed = true;

    _direction = calcDirection(pos);
    if (_direction == Unknown) _offset = pos;
}

void CSAdjustableWgt::mouseMoveEvent(QMouseEvent *e)
{
    const auto pos = e->pos();

    // Reset the shape of mouse cursor
    if (!_pressed)
    {
        autoReshapeMouse(pos);
        return;
    }

    // If pressed mouse button
    if (_direction != Unknown)
    {
        autoResize(pos);
    }
}

void CSAdjustableWgt::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    _pressed = false;
    _direction = Unknown;

    // Reshape mouse cursor
    autoReshapeMouse(e->pos());
}

/**
 * @brief Get the direction, and determine the shape of the cursor
 * @param pos
 * @return
 */
CSAdjustableWgt::Direction CSAdjustableWgt::calcDirection(const QPoint &pos)
{
    const int diff = 10;
    const auto rect = this->rect();
    Direction tmpDir = Unknown;

    // Get the direction by cursor's current position
    if (abs(rect.top() - pos.y()) < diff)
    {
        if (abs(rect.left() - pos.x()) < diff) tmpDir = TopLeft;
        else if (abs(rect.right() - pos.x()) < diff) tmpDir = TopRight;
        else tmpDir = Up;
    }
    else if (abs(rect.bottom() - pos.y()) < diff)
    {
        if (abs(rect.left() - pos.x()) < diff) tmpDir = BottomLeft;
        else if (abs(rect.right() - pos.x()) < diff) tmpDir = BottomRight;
        else tmpDir = Down;
    }
    else if (abs(rect.left() - pos.x()) < diff)
    {
        tmpDir = Left;
    }
    else if (abs(rect.right() - pos.x()) < diff)
    {
        tmpDir = Right;
    }

    return tmpDir;
}

/**
 * @brief Reshape the mouse when the mouse is hover on the window, on border or inside
 * @param pos
 */
void CSAdjustableWgt::autoReshapeMouse(const QPoint &pos)
{
    auto tmpDir = calcDirection(pos);
    Qt::CursorShape shape;

    switch (tmpDir)
    {
    case TopLeft:
    case BottomRight:
        shape = Qt::SizeFDiagCursor;
        break;
    case TopRight:
    case BottomLeft:
        shape = Qt::SizeBDiagCursor;
        break;
    case Up:
    case Down:
        shape = Qt::SizeVerCursor;
        break;
    case Left:
    case Right:
        shape = Qt::SizeHorCursor;
        break;
    default:
        shape = Qt::ArrowCursor;
        break;
    }

    setCursor(shape);
}

/**
 * @brief Auto resize the window when user want to adjust its size
 * @param pos
 */
void CSAdjustableWgt::autoResize(const QPoint &pos)
{
    auto globalPos = mapToGlobal(pos);
    QRect r;
    QPoint anchor;

    // Reset the geometry of widget by Direction
    switch (_direction)
    {
    case TopLeft:
        anchor = mapToGlobal(QPoint(width(), height()));
        if (anchor.x()-globalPos.x() < 100) globalPos.setX(anchor.x() - 100);
        if (anchor.y()-globalPos.y() < 100) globalPos.setY(anchor.y() - 100);
        r = QRect(globalPos.x(), globalPos.y(), anchor.x()-globalPos.x(), anchor.y()-globalPos.y());
        break;
    case TopRight:
        anchor = mapToGlobal(QPoint(0, height()));
        if (globalPos.x()-anchor.x() < 100) globalPos.setX(anchor.x() + 100);
        if (anchor.y()-globalPos.y() < 100) globalPos.setY(anchor.y() - 100);
        r = QRect(anchor.x(), globalPos.y(), globalPos.x()-anchor.x(), anchor.y()-globalPos.y());
        break;
    case BottomLeft:
        anchor = mapToGlobal(QPoint(width(), 0));
        if (anchor.x()-globalPos.x() < 100) globalPos.setX(anchor.x() - 100);
        if (globalPos.y()-anchor.y() < 100) globalPos.setY(anchor.y() + 100);
        r = QRect(globalPos.x(), anchor.y(), anchor.x()-globalPos.x(), globalPos.y()-anchor.y());
        break;
    case BottomRight:
        anchor = mapToGlobal(QPoint(0, 0));
        if (globalPos.x()-anchor.x() < 100) globalPos.setX(anchor.x() + 100);
        if (globalPos.y()-anchor.y() < 100) globalPos.setY(anchor.y() + 100);
        r = QRect(anchor.x(), anchor.y(), globalPos.x()-anchor.x(), globalPos.y()-anchor.y());
        break;
    case Up:
        anchor = mapToGlobal(QPoint(width(), height()));
        if (anchor.y()-globalPos.y() < 100) globalPos.setY(anchor.y() - 100);
        r = QRect(x(), globalPos.y(), width(), anchor.y()-globalPos.y());
        break;
    case Down:
        anchor = mapToGlobal(QPoint(0, 0));
        if (globalPos.y()-anchor.y() < 100) globalPos.setY(anchor.y() + 100);
        r = QRect(anchor.x(), anchor.y(), width(), globalPos.y()-anchor.y());
        break;
    case Left:
        anchor = mapToGlobal(QPoint(width(), 0));
        if (anchor.x()-globalPos.x() < 100) globalPos.setX(anchor.x() - 100);
        r = QRect(globalPos.x(), y(), anchor.x()-globalPos.x(), height());
        break;
    case Right:
        anchor = mapToGlobal(QPoint(0, 0));
        r = QRect(anchor.x(), anchor.y(), globalPos.x()-anchor.x(), height());
        break;
    default:
        break;
    }

    setGeometry(r);
}

bool CSAdjustableWgt::isInside(const QPoint &pos)
{
    return this->rect().contains(pos);
}

}   // `cs`
