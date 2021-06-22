#include "csbatteryartware.h"


namespace cs
{

static const int maxValue = 100;
static const int radius = 3;


CSBatteryArtWare::CSBatteryArtWare(QWidget *parent)
    : CSArtWare(parent)
{
    initMember();
    initUI();
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

void CSBatteryArtWare::setColor(const QColor &color)
{
    _color = color;
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

QColor CSBatteryArtWare::color() const
{
    return _color;
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
    p.setPen(Qt::transparent);
    p.setBrush(_color);
    p.drawRoundedRect(rect, radius, radius);
    p.restore();
}

void CSBatteryArtWare::drawBackground(QPainter &p)
{
    auto rect = calcBgRect();

    p.save();
    p.setPen(Qt::transparent);
    p.setBrush(_color);
    p.drawRoundedRect(rect, radius, radius);
    p.restore();
}

void CSBatteryArtWare::initMember()
{
    _textVisible = true;
    _value = 0;
    _color = Qt::black;
}

void CSBatteryArtWare::initUI()
{
    // Set attribute
    resize(50, 20);
    autoSetPaintAreaSize();
}

QRect CSBatteryArtWare::calcBodyRect() const
{
    auto rect = paintAreaRect();
    int w = rect.width() * 97 / 100;
    int h = rect.height();
    int x = (rect.width() - w) / 2 + rect.x();
    int y = (rect.height() - h) / 2 + rect.y();

    return QRect(x, y, w, h);
}

QRect CSBatteryArtWare::calcHeadRect() const
{
    auto rect = paintAreaRect();
    auto rectBody = calcBodyRect();
    int w = rect.width() - rectBody.width();
    int h = rectBody.height() / 3;
    int x = rectBody.x() + rectBody.width();
    int y = (rectBody.height() - h) / 2 + rectBody.y();

    return QRect(x, y, w, h);
}

QRect CSBatteryArtWare::calcBgRect() const
{
    auto rectBody = calcBodyRect();
    int w = rectBody.width() * _value / 100;
    int h = rectBody.height();
    int x = rectBody.x();
    int y = rectBody.y();

    return QRect(x, y, w, h);
}

}   // `cs`
