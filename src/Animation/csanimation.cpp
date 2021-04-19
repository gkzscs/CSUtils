#include "csanimation.h"

#include <QTimer>
#include <QPainter>


namespace cs
{

CSAnimation::CSAnimation(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

void CSAnimation::start()
{
    _timerDraw->start();
    if (_timerDuration->interval() > 0) _timerDuration->start();

    show();
}

void CSAnimation::stop()
{
    _timerDraw->stop();
    if (_timerDuration->isActive()) _timerDuration->stop();

    hide();
}

bool CSAnimation::active() const
{
    return _timerDraw->isActive();
}

void CSAnimation::setDuration(int msec)
{
    _timerDuration->setInterval(msec);
}

void CSAnimation::setSpeed(int n)
{
    _timerDraw->setInterval(100 / n);
    update();
}

int CSAnimation::duration() const
{
    return _timerDuration->interval();
}

int CSAnimation::speed() const
{
    return (100 / _timerDraw->interval());
}

void CSAnimation::initMember()
{
    _timerDraw = new QTimer(this);
    _timerDuration = new QTimer(this);
}

void CSAnimation::initUI()
{
    // Set attribute
    resize(100, 100);

    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_StyledBackground);

    // Set duration timer to be single shot
    _timerDuration->setSingleShot(true);

    // Set speed and duration
    setSpeed(1);
    setDuration(0);
}

void CSAnimation::initSignalSlot()
{
    connect(_timerDraw, &QTimer::timeout, [&] { update(); } );
    connect(_timerDuration, &QTimer::timeout, this, &CSAnimation::stop);
}

std::tuple<double, double> CSAnimation::scaleRatio() const
{
    const QSize orgSize(100, 100);
    double ratioW = static_cast<double>(width()) / orgSize.width();
    double ratioH = static_cast<double>(height()) / orgSize.height();

    return std::make_tuple(ratioW, ratioH);
}

void CSAnimation::drawAll(QPainter &p)
{
    Q_UNUSED(p)
}

void CSAnimation::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (_timerDraw->isActive())
    {
        QPainter p(this);
        drawAll(p);
    }
}

}   // End of `cs`
