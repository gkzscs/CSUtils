#include "csprogressbar.h"


namespace cs
{

CSProgressBar::CSProgressBar(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
    initUI();
}

//void CSProgressBar::setBgColor(const QColor &cl)
//{
//    _colorBg = cl;
//    update();
//}

void CSProgressBar::setRange(double min, double max)
{
    if (min >= max) return;

    _minRange = min;
    _maxRange = max;
    adjustValue();
    update();
}

void CSProgressBar::setValue(double val)
{
    _value = val;
    adjustValue();
    update();
}

//QColor CSProgressBar::bgColor() const
//{
//    return _colorBg;
//}

double CSProgressBar::minRange() const
{
    return _minRange;
}

double CSProgressBar::maxRange() const
{
    return _maxRange;
}

double CSProgressBar::value() const
{
    return _value;
}

void CSProgressBar::initMember()
{
//    _sizeOrg = QSize(100, 10);
    _bgColor = QColor(187, 187, 187);
    _color = QColor(15, 255, 255);
    _minRange = 0.0;
    _maxRange = 100.0;
    _value = 50.0;
}

void CSProgressBar::initUI()
{
    // Set attribute
    resetOriginSize(100, 10);
//    resize(_sizeOrg);
}

void CSProgressBar::drawAll(QPainter &p)
{
    p.setRenderHint(QPainter::Antialiasing);

    drawBaseBar(p);
    drawCurrentBar(p);
}

void CSProgressBar::drawBaseBar(QPainter &p)
{
    double penW = height();
    auto line = calcBaseLine();

    p.save();
    alterPen(p, penW, _bgColor);
    p.drawLine(line);
    p.restore();
}

void CSProgressBar::drawCurrentBar(QPainter &p)
{
    double penW = height();
    auto line = calcCurrentLine();

    p.save();
    alterPen(p, penW, _color);
    p.drawLine(line);
    p.restore();
}

/**
 * @brief CSProgressBar::calcBaseLine
 * @return
 */
QLineF CSProgressBar::calcBaseLine()
{
    double penW = height();
    double x1 = penW / 2.0;
    double y1 = height() / 2.0;
    double x2 = x1 + width() - penW;
    double y2 = y1;

    return QLineF(x1, y1, x2, y2);
}

/**
 * @brief CSProgressBar::calcCurrentLine
 * @return
 */
QLineF CSProgressBar::calcCurrentLine()
{
    double penW = height();
    double x1 = penW / 2.0;
    double y1 = height() / 2.0;
    double x2 = x1 + (width()-penW) * (_value-_minRange) / (_maxRange-_minRange);
    double y2 = y1;

    return QLineF(x1, y1, x2, y2);
}

/**
 * @brief CSProgressBar::alterPen
 * @param p
 * @param w
 * @param cl
 */
void CSProgressBar::alterPen(QPainter &p, double w, const QColor &cl)
{
    auto pen = p.pen();
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);
    pen.setWidthF(w);
    pen.setColor(cl);
    p.setPen(pen);
}

/**
 * @brief CSProgressBar::adjustValue
 */
void CSProgressBar::adjustValue()
{
    if (_value < _minRange) _value = _minRange;
    if (_value > _maxRange) _value = _maxRange;
}

}   // cs
