#include "cswindartware.h"


namespace cs
{

static const double scMinAngle = 0.0;
static const double scMaxAngle = 360.0;
static const int scMinLevel = 0;
static const int scMaxLevel = 13;


CSWindArtWare::CSWindArtWare(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
}

void CSWindArtWare::setDirection(double angle)
{
    if (angle < scMinAngle) angle = scMinAngle;
    if (angle > scMaxAngle) angle = scMaxAngle;

    _angle = angle;
    update();
}

void CSWindArtWare::setLevel(int lv)
{
    if (lv < scMinLevel) lv = scMinLevel;
    if (lv > scMaxLevel) lv = scMaxLevel;

    _level = lv;
    update();
}

double CSWindArtWare::direction() const
{
    return _angle;
}

int CSWindArtWare::level() const
{
    return _level;
}

void CSWindArtWare::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);
    drawWind(p);
}

void CSWindArtWare::drawWind(QPainter &p)
{
    auto r = calcWindRect();
    QPoint posCenter(_sizeOrg.width()/2, _sizeOrg.height()/2);
    auto pen = p.pen();
    pen.setWidth(2);
    pen.setColor(_color);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    // Do matrix operation, and set pen
    p.save();
    scalePainter(p);
    p.setPen(pen);

    // Draw wind of level 0
    if (_level == 0)
    {
        drawWindLevel0(p);
        return;
    }

    // Draw wind between level 0 and 12
    p.translate(posCenter);
    p.rotate(-_angle);

    if (_level <= 7) drawWindNoMoreThanLevel7(p, r.size());
    else drawWindAboveLevel7(p, r.size());

    p.restore();
}

void CSWindArtWare::drawWindLevel0(QPainter &p)
{
    const QString txt = "--";
    auto r = rect();

    p.drawText(r, Qt::AlignCenter, txt);
}

/**
 * @brief Draw control when the `_level` is no more than 7
 * @param p
 */
void CSWindArtWare::drawWindNoMoreThanLevel7(QPainter &p, const QSize &s)
{
    int n = _level / 2;
    int w = s.width();
    int h = s.height();
    int x = 0;
    int y = 0;
    int space = h / 5;

    // Translate
    p.translate(-s.width()/2, -s.height()/2);

    // Draw vertical line
    p.drawLine(0, 0, 0, h);

    // Draw horizontal lines
    // Draw long line
    for (int i = 0; i < n; ++i)
    {
        p.drawLine(x, y, w, y);
        y += space;
    }

    // Draw short line
    if (_level % 2 != 0)
    {
        p.drawLine(x, y, w/2, y);
    }
}

void CSWindArtWare::drawWindAboveLevel7(QPainter &p, const QSize &s)
{
    int n = (_level - 8) / 2;
    int w = s.width();
    int h = s.height();
    int x = 0;
    int y = 0;
    int space = h / 5;

    // Translate
    p.translate(-s.width()/2, -s.height()/2);

    // Draw vertical line
    p.drawLine(0, 0, 0, h);

    // Draw horizontal lines
    // Draw flag
    p.drawLine(x, y, w, y+space);
    y += space * 2;
    p.drawLine(x, y, w, y-space);
    y += space;

    // Draw long line
    for (int i = 0; i < n; ++i)
    {
        p.drawLine(x, y, w, y);
        y += space;
    }

    // Draw short line
    if ((_level - 8) % 2 != 0)
    {
        p.drawLine(x, y, w/2, y);
    }
}

QRect CSWindArtWare::calcWindRect() const
{
    int w = _sizeOrg.width() / 4;
    int h = _sizeOrg.height() / 2;
    int x = (_sizeOrg.width() - w) / 2;
    int y = (_sizeOrg.height() - h) / 2;

    return QRect(x, y, w, h);
}

void CSWindArtWare::initMember()
{
    setLevel(5);
    setDirection(0.0);
}

}   // `cs`
