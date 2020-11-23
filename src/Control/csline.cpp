#include "csline.h"
#include "Core/csutils.h"
#include <QPainter>


namespace cs
{

SplitLine::SplitLine(QWidget *parent)
    : CSWidget(parent), _type(Normal)
{
    init();
}

SplitLine::SplitLine(Type type, QWidget *parent)
    : CSWidget(parent), _type(type)
{
    init();
}


void SplitLine::setType(Type type)
{
    if (type == _type) return;
    _type = type;

    update();
}

SplitLine::Type SplitLine::getType() const
{
    return _type;
}

void SplitLine::initUI()
{
    resize(100, 1);
    setHidden(false);
}

void SplitLine::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    // Enable style sheet
    CSUtils::enableStyleSheet(this);

    QPainter p(this);
    if (_type == Normal) drawNormal(p);
    else if (_type == CircleRect) drawCircleRect(p);
}

void SplitLine::drawNormal(QPainter &p)
{
    p.save();
    p.fillRect(rect(), QBrush());
    p.restore();
}

void SplitLine::drawCircleRect(QPainter &p)
{
    const int r = height()/2;
    QLine line(0, height()/2, width(), 1);
    QPoint centerP(15, r);
    QRect rect(width() - 20, 0, 48, height());

    p.save();
    p.setPen(QColor(0, 255, 255));
    p.setBrush(QColor(0, 255, 255));
    p.drawLine(line);
    p.drawEllipse(centerP, r, r);
    p.drawRect(rect);
    p.restore();
}

}
