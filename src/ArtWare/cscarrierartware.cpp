#include "cscarrierartware.h"


namespace cs
{

static const int maxIntensity = 5;


CSCarrierArtWare::CSCarrierArtWare(QWidget *parent)
    : CSArtWare(parent)
{
    initMember();
    initUI();
}

void CSCarrierArtWare::setIntensity(int intensity)
{
    if (intensity < 0) intensity = 0;
    if (intensity > maxIntensity) intensity = maxIntensity;

    _intensity = intensity;
    update();
}

void CSCarrierArtWare::setColor(const QColor &color)
{
    _color = color;
    update();
}

int CSCarrierArtWare::intensity() const
{
    return _intensity;
}

QColor CSCarrierArtWare::color() const
{
    return _color;
}

void CSCarrierArtWare::drawAll(QPainter &p)
{
    drawBody(p);
}

void CSCarrierArtWare::drawBody(QPainter &p)
{
    p.save();
    p.setPen(Qt::transparent);
    p.setBrush(_color);

    for (int i = 1; i <= _intensity; ++i)
    {
        auto rect = calcBlockRect(i);
        p.drawRect(rect);
    }

    p.restore();
}

void CSCarrierArtWare::initMember()
{
    _intensity = 5;
    _color = Qt::white;
}

void CSCarrierArtWare::initUI()
{
    // Set attribute
    resize(50, 40);
    autoSetPaintAreaSize();
}

QRect CSCarrierArtWare::calcBlockRect(int intensity)
{
    auto rect = paintAreaRect();
    int space = 1;
    int w = (rect.width() + space) / maxIntensity - space;
    int h = rect.height() * intensity / maxIntensity;
    int x = (w + space) * (intensity - 1) + rect.x();
    int y = rect.height() - h + rect.y();

    return QRect(x, y, w, h);
}

}   // `cs`
