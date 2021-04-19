#include "cswaitanimation.h"

#include <QPainter>
#include <QTimer>


namespace cs
{

CSWaitAnimation::CSWaitAnimation(QWidget *parent)
    : CSAnimation(parent)
{
    initMember();
    initSignalSlot();
}

void CSWaitAnimation::setInfo(const QString &info)
{
    _info = info;
    update();
}

QString CSWaitAnimation::info() const
{
    return _info;
}

void CSWaitAnimation::initMember()
{
    _angle = 0;
}

void CSWaitAnimation::initSignalSlot()
{
    connect(_timerDraw, &QTimer::timeout, [&] { _angle += 50; } );
}

void CSWaitAnimation::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);

    drawInfo(p);
    drawDots(p);
}

void CSWaitAnimation::drawDots(QPainter &p)
{
    // Assign to variables
    const int totalAngle = 360;
    const int intervalAngle = 50;
    const int smallR = (width() < height() ? width() : height()) / 15;
    const int bigR = smallR * 2;
    const QPoint centerP(width()/2, height()/2);
    QColor color = p.pen().color();

    // Start drawing, adjust coordinate
    p.save();
    p.translate(centerP);
    p.rotate(_angle);

    // Set pen and brush
    p.setBrush(color);
    p.setPen(Qt::transparent);

    // Draw each ellipse
    for (int angle = 0; angle < totalAngle; angle += intervalAngle)
    {
        // Calculate next circle's radius
        int r = smallR + angle / intervalAngle;

        // Start drawing one ellipse
        p.save();
        p.rotate(angle);
        p.translate(bigR, 0);

        p.drawEllipse(0, 0, r, r);

        p.restore();
    }

    // Restore painter
    p.restore();
}

void CSWaitAnimation::drawInfo(QPainter &p)
{
    const QRect orgRect(0, 0, 100, 100);
    auto tupRatio = scaleRatio();
    QFont font;
    font.setPixelSize(9);

    p.save();
    p.scale(std::get<0>(tupRatio), std::get<1>(tupRatio));

    p.drawText(orgRect, Qt::AlignCenter, _info);
    p.restore();
}

}   // End of `cs`
