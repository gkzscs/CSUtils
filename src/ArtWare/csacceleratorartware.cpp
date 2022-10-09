#include "csacceleratorartware.h"


namespace cs
{

static const int scMinValue = 0;
static const int scMaxValue = 100;
static const int scTotalAngle = 180;


CSAcceleratorArtWare::CSAcceleratorArtWare(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
    initUI();

    setValue(50);
}

void CSAcceleratorArtWare::setValue(int v)
{
    if (v < scMinValue) v = scMinValue;
    if (v > scMaxValue) v = scMaxValue;

    _value = v;
    update();
}

int CSAcceleratorArtWare::value() const
{
    return _value;
}

void CSAcceleratorArtWare::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);

    drawArch(p);
    drawPointer(p);
}

void CSAcceleratorArtWare::drawArch(QPainter &p)
{
    int curSpanAngle = calcRotateAngle();
    auto pen = p.pen();
    pen.setWidth(4);
    pen.setColor(QColor(_color.red(), _color.green(), _color.blue(), 64));

    p.save();
    scalePainter(p);
    p.setPen(pen);
    drawArch(p, scTotalAngle*16);

    pen.setColor(_color);
    p.setPen(pen);
    drawArch(p, curSpanAngle*16);
    p.restore();
}

void CSAcceleratorArtWare::drawPointer(QPainter &p)
{
    auto posBase = calcPointerBasePoint();
    auto poly = calcTrianglePolygon();
    auto angle = calcRotateAngle();
    const int r = 3;

    p.save();
    scalePainter(p);
    p.setBrush(_color);
    p.setPen(Qt::transparent);

    // Draw circle
    p.drawEllipse(posBase, r, r);

    // Draw triangle
    p.translate(posBase);
    p.rotate(angle);
    p.drawPolygon(poly);
    p.restore();
}

/**
 * @brief Draw arch with current span angle
 * @param p
 * @param curSpanAngle
 */
void CSAcceleratorArtWare::drawArch(QPainter &p, int curSpanAngle)
{
    auto r = calcArchRect();
    int n = 4;
    int intervalAngle = 20;
    int startAngle = scTotalAngle * 16;
    int spanAngle = (scTotalAngle + intervalAngle) * 16 / n;
    n = curSpanAngle / spanAngle;

    p.save();
    for (auto i = 0; i < n; ++i)
    {
        p.drawArc(r, startAngle, -spanAngle+intervalAngle*16);
        startAngle -= spanAngle;
    }
    p.drawArc(r, startAngle, -curSpanAngle+spanAngle*n);

    p.restore();
}

QRect CSAcceleratorArtWare::calcArchRect() const
{
    int x = 10;
    int y = 12;
    int w = _sizeOrg.width() - x*2;
    int h = (_sizeOrg.height() - y*2) * 2;

    return QRect(x, y, w, h);
}

QPoint CSAcceleratorArtWare::calcPointerBasePoint() const
{
    auto rArch = calcArchRect();
    int x = rArch.x() + rArch.width()/2;
    int y = rArch.y() + rArch.height()/2;

    return QPoint(x, y);
}

QPolygon CSAcceleratorArtWare::calcTrianglePolygon() const
{
    auto rArch = calcArchRect();
    const int w = 4;
    const int l = rArch.width()/2 - w;

    QVector<QPoint> pointsVec;
    pointsVec.append(QPoint(0, -w/2));
    pointsVec.append(QPoint(0, w/2));
    pointsVec.append(QPoint(-l, 0));

    return QPolygon(pointsVec);
}

int CSAcceleratorArtWare::calcRotateAngle() const
{
    auto angle = (_value-scMinValue) * scTotalAngle / (scMaxValue-scMinValue);
    return angle;
}

void CSAcceleratorArtWare::initMember()
{
//    _sizeOrg = QSize(56, 40);
}

void CSAcceleratorArtWare::initUI()
{
    // Set attribute
    resetOriginSize(56, 40);
//    resize(_sizeOrg);
}

}   // `cs`
