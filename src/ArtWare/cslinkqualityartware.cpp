#include "cslinkqualityartware.h"


namespace cs
{

static const int scMinValue = 0;
static const int scMaxValue = 100;


CSLinkQualityArtWare::CSLinkQualityArtWare(Type type, QWidget *parent)
    : cs::CSArtWare(parent)
{
    setType(type);
    setValue(50);
}

void CSLinkQualityArtWare::setValue(int val)
{
    if (val < scMinValue) val = scMinValue;
    if (val > scMaxValue) val = scMaxValue;

    _value = val;
    update();
}

int CSLinkQualityArtWare::value() const
{
    return _value;
}

void CSLinkQualityArtWare::drawAll(QPainter &p)
{
    drawArrow(p);
    drawLinkQuality(p);
    drawText(p);
}

void CSLinkQualityArtWare::drawArrow(QPainter &p)
{
    auto r = calcArrowRect();

    p.save();
    scalePainter(p);
    p.translate(r.topLeft());
    p.setPen(Qt::transparent);
    p.setBrush(_color);

    switch (_type)
    {
    case Up:
        drawUpArrow(p);
        break;
    case Down:
        drawDownArrow(p);
        break;
    }

    p.restore();
}

void CSLinkQualityArtWare::drawLinkQuality(QPainter &p)
{
    // Set the style of pen
    auto pen = p.pen();
    pen.setWidth(3);
    pen.setColor(QColor(_color.red(), _color.green(), _color.blue(), 64));
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    p.save();
    scalePainter(p);
    p.setRenderHint(QPainter::Antialiasing);
    // Draw background
    p.setPen(pen);
    drawLinkQuality(p, scMaxValue);

    // Draw foreground
    pen.setColor(_color);
    p.setPen(pen);
    drawLinkQuality(p, _value);
    p.restore();
}

void CSLinkQualityArtWare::drawText(QPainter &p)
{
    auto r = calcTextRect();
    auto strVal = QString("%1%").arg(_value);
    auto f = font();
    f.setPixelSize(9);
    f.setBold(false);

    p.save();
    scalePainter(p);
    p.setFont(f);
    p.setPen(_color);
    p.drawText(r, Qt::AlignCenter, strVal);
    p.restore();
}

void CSLinkQualityArtWare::drawUpArrow(QPainter &p)
{
    auto r = calcArrowRect();
    const int rectH = 4;
    const int rectW = 2;
    const int triangleH = r.height() - rectH;
    int rectX = (r.width() - rectW) / 2;
    int rectY = triangleH;

    // Draw triangle
    QPoint points[3];
    points[0] = QPoint(r.width()/2, 0);
    points[1] = QPoint(0, triangleH);
    points[2] = QPoint(r.width(), triangleH);
    p.drawPolygon(points, 3);

    // Draw rectangle
    QRect rec(rectX, rectY, rectW, rectH);
    p.drawRect(rec);
}

void CSLinkQualityArtWare::drawDownArrow(QPainter &p)
{
    auto r = calcArrowRect();
    const int rectH = 4;
    const int rectW = 2;
    const int triangleY = rectH;
    int rectX = (r.width() - rectW) / 2;
    int rectY = 0;

    // Draw triangle
    QPoint points[3];
    points[0] = QPoint(r.width()/2, r.height());
    points[1] = QPoint(0, triangleY);
    points[2] = QPoint(r.width(), triangleY);
    p.drawPolygon(points, 3);

    // Draw rectangle
    QRect rec(rectX, rectY, rectW, rectH);
    p.drawRect(rec);
}

/**
 * @brief Draw link quality part according to the level of link quality
 * @param p
 * @param val
 */
void CSLinkQualityArtWare::drawLinkQuality(QPainter &p, int val)
{
    const int unitVal = 20;
    int level = (val/unitVal) + (val%unitVal > 0 ? 1 : 0);

    for (int i = 0; i < level; ++i)
    {
        auto line = calcLinkQualityLine(i);
        p.drawLine(line);
    }
}

QRect CSLinkQualityArtWare::calcArrowRect() const
{
    int x = 7;
    int y = 9;
    int w = 6;
    int h = 8;

    return QRect(x, y, w, h);
}

QLine CSLinkQualityArtWare::calcLinkQualityLine(int level) const
{
    const int w = 3;
    const int space = 2;
    const int minH = 3;
    const int intervalH = 2;
    int left = 11;
    int bottom = 10;
    int x = left + level * (w+space);
    int y = _sizeOrg.height() - bottom;
    int h = minH + (intervalH*level - 1);

    return QLine(QPoint(x, y), QPoint(x, y-h));
}

QRect CSLinkQualityArtWare::calcTextRect() const
{
    int x = 14;
    int y = 9;
    int w = 20;
    int h = 8;

    return QRect(x, y, w, h);
}

/**
 * @brief Set the type of art ware
 * @param type
 */
void CSLinkQualityArtWare::setType(Type type)
{
    _type = type;
    update();
}

}   // `cs`
