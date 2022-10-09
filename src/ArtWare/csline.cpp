#include "csline.h"
#include "Core/csutils.h"
#include <QPainter>


namespace cs
{

CSLine::CSLine(QWidget *parent)
    : CSArtWare(parent), _type(Normal)
{
    initUI();
}

CSLine::CSLine(Type type, QWidget *parent)
    : CSArtWare(parent), _type(type)
{
    initUI();
}

void CSLine::setType(Type type)
{
    if (type == _type) return;
    _type = type;

    update();
}

CSLine::Type CSLine::getType() const
{
    return _type;
}

void CSLine::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);

    if (_type == Normal) drawNormal(p);
    else if (_type == CircleRect) drawCircleRect(p);
}

void CSLine::drawNormal(QPainter &p)
{
    p.save();
    p.fillRect(rect(), _color);
    p.restore();
}

void CSLine::drawCircleRect(QPainter &p)
{
    const int r = height()/2;
    QLine line(0, height()/2, width(), 1);
    QPoint centerP(15, r);
    // Strange! The geometry is not `y = 1 && h = height()-2`
    QRect rect(width() - 66, 0, 48, height()-2);

    p.save();
    p.setPen(_color);
    p.setBrush(_color);
    p.drawLine(line);
    p.drawEllipse(centerP, r, r);
    p.drawRect(rect);
    p.restore();
}

void CSLine::initUI()
{
    resize(100, 1);

    // Set the default color of line
    switch (_type)
    {
    case Normal:
        setColor(QColor(255, 255, 255, 51));
        break;
    case CircleRect:
        setColor(QColor(15, 255, 255, 120));
        break;
    }
}

}   // End of `cs`
