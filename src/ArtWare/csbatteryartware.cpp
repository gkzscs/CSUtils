#include "csbatteryartware.h"


namespace cs
{

static const int maxValue = 100;
static const int radius = 3;


CSBatteryArtWare::CSBatteryArtWare(QWidget *parent)
    : CSArtWare(parent)
{
    initMember();
}

void CSBatteryArtWare::setTextVisible(bool flag)
{
    _textVisible = flag;
    update();
}

void CSBatteryArtWare::setValue(int v)
{
    if (v < 0) v = 0;
    if (v > maxValue) v = maxValue;

    _value = v;
    update();
}

bool CSBatteryArtWare::textVisible() const
{
    return _textVisible;
}

int CSBatteryArtWare::value() const
{
    return _value;
}

void CSBatteryArtWare::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);

    drawBackground(p);
    drawBody(p);
    drawHead(p);
}

void CSBatteryArtWare::drawBody(QPainter &p)
{
    auto rect = calcBodyRect();
    QString strValue = QString::number(_value) + "%";

    p.save();
    scalePainter(p);
    // Draw border
    p.setPen(_color);
    p.drawRoundedRect(rect, radius, radius);

    // Draw text
    if (_textVisible)
    {
        p.setPen(Qt::black);
        p.drawText(rect, Qt::AlignCenter, strValue);
    }

    p.restore();
}

void CSBatteryArtWare::drawHead(QPainter &p)
{
    auto rect = calcHeadRect();

    p.save();
    scalePainter(p);
    p.setPen(Qt::transparent);
    p.setBrush(_color);
    p.drawRoundedRect(rect, radius, radius);
    p.restore();
}

void CSBatteryArtWare::drawBackground(QPainter &p)
{
    auto rect = calcBgRect();

    p.save();
    scalePainter(p);
    p.setPen(Qt::transparent);
    p.setBrush(_color);
    p.drawRoundedRect(rect, radius, radius);
    p.restore();
}

void CSBatteryArtWare::initMember()
{
    _textVisible = true;
    _value = 0;
}

QRect CSBatteryArtWare::calcBodyRect() const
{
    int w = 32;
    int h = 16;
    int x = (_sizeOrg.width() - w) / 2;
    int y = (_sizeOrg.height() - h) / 2;

    return QRect(x, y, w, h);
}

QRect CSBatteryArtWare::calcHeadRect() const
{
    auto rectBody = calcBodyRect();

    int x = rectBody.x() + rectBody.width();
    int y = rectBody.y() + rectBody.height() / 3;
    int w = 2;
    int h = rectBody.height() - rectBody.height() / 3 * 2;

    return QRect(x, y, w, h);
}

QRect CSBatteryArtWare::calcBgRect() const
{
    auto rectBody = calcBodyRect();
    int w = (rectBody.width() - 2) * _value / 100;
    int h = rectBody.height() - 2;
    int x = rectBody.x() + 1;
    int y = rectBody.y() + 1;

    return QRect(x, y, w, h);
}

}   // `cs`
