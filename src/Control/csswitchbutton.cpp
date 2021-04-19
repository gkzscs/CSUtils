#include "csswitchbutton.h"
#include <QPainter>
#include <QTimer>


namespace cs
{

CSSwitchButton::CSSwitchButton(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

CSSwitchButton::~CSSwitchButton()
{
    _timer->deleteLater();
}

void CSSwitchButton::switchOn(bool flag)
{
    _isOn = flag;
    _timer->start();
}

bool CSSwitchButton::isOn() const
{
    return _isOn;
}

void CSSwitchButton::initMember()
{
    _isOn = false;
    _coreX = 1;
    _timer = new QTimer(this);
}

void CSSwitchButton::initUI()
{
    // Set atttribute
    resize(40, 24);

    _timer->setInterval(10);
}

void CSSwitchButton::initSignalSlot()
{
    connect(_timer, &QTimer::timeout, [&]() {
        if (_isOn)
        {
            if (_coreX >= width() - height()-1)
            {
                _timer->stop();
                return;
            }
            ++_coreX;
        }
        else
        {
            if (_coreX <= 0+1)
            {
                _timer->stop();
                return;
            }
            --_coreX;
        }

        update();
    });
}

void CSSwitchButton::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    drawBorder(p);
    drawCore(p);
}

void CSSwitchButton::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    // Follow code would change the value of `_isOn`
    switchOn(!_isOn);
    emit switchSignal(_isOn);
}

void CSSwitchButton::drawBorder(QPainter &p)
{
    QRect rect = this->rect();
    QRect rightRect = calcRightBorderRect();
    QColor bgColor(15, 255, 255);
    QColor rightBgColor(224, 224, 224);
    int r = height() / 2;

    p.save();
    p.setPen(Qt::transparent);
    p.setBrush(bgColor);
    p.drawRoundedRect(rect, r, r);
    p.setBrush(rightBgColor);
    p.drawRoundedRect(rightRect, r, r);
    p.restore();
}

void CSSwitchButton::drawCore(QPainter &p)
{
    QRect rect = calcCoreRect();
    rect = QRect(rect.x(), rect.y()+1, rect.width()-2, rect.height()-2);

    p.save();
    p.setPen(Qt::white);
    p.setBrush(Qt::white);
    p.drawEllipse(rect);
    p.restore();
}

QRect CSSwitchButton::calcCoreRect()
{
    int r = height();

    QRect rect(_coreX, 0, r, r);
    return rect;
}

QRect CSSwitchButton::calcRightBorderRect()
{
    QRect rect = calcCoreRect();
    rect = QRect(rect.x(), rect.y(), width()-rect.x(), height());

    return rect;
}

}   // End of `cs`
