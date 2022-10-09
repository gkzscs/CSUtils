#include "csplayerprogress.h"


namespace cs
{

static const double scMargin = 12;
static const double scTotalProgressH = 4;
static const double scCurrentProgressH = 6;


CSPlayerProgress::CSPlayerProgress(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
    initUI();
}

//void CSPlayerProgress::setBgColor(const QColor &bgColor)
//{
//    _colorBg = bgColor;
//    update();
//}

void CSPlayerProgress::setRange(qint64 min, qint64 max)
{
    if (max <= min) return;
    _minRange = min;
    _maxRange = max;
    adjustCurrentValue();

    update();
    emit rangeChangedSignal(_minRange, _maxRange);
}

void CSPlayerProgress::setValue(qint64 val)
{
    _value = val;
    adjustCurrentValue();

    update();
    emit valueChangedSignal(_value);
}

qint64 CSPlayerProgress::minRange() const
{
    return _minRange;
}

qint64 CSPlayerProgress::maxRange() const
{
    return _maxRange;
}

qint64 CSPlayerProgress::value() const
{
    return _value;
}

double CSPlayerProgress::progress() const
{
    double prgr = static_cast<double>(_value - _minRange) / (_maxRange - _minRange);
    qDebug() << _value << _minRange << _maxRange << prgr;
    return prgr;
}

void CSPlayerProgress::mousePressEvent(QMouseEvent *e)
{
    cs::CSArtWare::mousePressEvent(e);

    auto r = calcControlPointRect();
    if (r.contains(e->pos()))
    {
        _controlling = true;
        _posPressed = e->pos();
        update();
    }
}

void CSPlayerProgress::mouseMoveEvent(QMouseEvent *e)
{
    cs::CSArtWare::mouseMoveEvent(e);

    if (_controlling)
    {
        auto val = calcCurrentValue(e->x());
        _posPressed = e->pos();

        setValue(val);
    }
}

void CSPlayerProgress::mouseReleaseEvent(QMouseEvent *e)
{
    cs::CSArtWare::mouseReleaseEvent(e);

    _controlling = false;
    auto r = calcTotalProgressRect();
    if (r.contains(e->pos()))
    {
        auto val = calcCurrentValue(e->x());
        setValue(val);

        emit valueChangedByHandSignal(val);
    }
}

void CSPlayerProgress::initMember()
{
    _minRange = 0.0;
    _maxRange = 100.0;
    _value = 50.0;
    _bgColor = QColor(255, 255, 255, 128);
    _controlling = false;
    _posPressed = QPointF(0, 0);
}

void CSPlayerProgress::initUI()
{
    // Set attributes
    resetOriginSize(100, 30);
}

void CSPlayerProgress::drawAll(QPainter &p)
{
    drawTotalProgress(p);
    drawCurrentProgress(p);
    drawControlPoint(p);
}

void CSPlayerProgress::drawTotalProgress(QPainter &p)
{
    auto line = calcTotalProgressLine();
    auto pen = p.pen();
    auto penW = totalProgressHeight();
    pen.setWidthF(penW);
    pen.setColor(_bgColor);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    p.save();
    p.setPen(pen);
    p.drawLine(line);
    p.restore();
}

void CSPlayerProgress::drawCurrentProgress(QPainter &p)
{
    auto line = calcCurrentProgressLine();
    auto pen = p.pen();
    auto penW = currentProgressHeight();
    pen.setWidthF(penW);
    pen.setColor(_color);
    pen.setCapStyle(Qt::PenCapStyle::RoundCap);

    p.save();
    p.setPen(pen);
    p.drawLine(line);
    p.restore();
}

void CSPlayerProgress::drawControlPoint(QPainter &p)
{
    auto r = calcControlPointRect();
    auto colorBrush = (_controlling ? _color : Qt::white);

    p.save();
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::transparent);
    p.setBrush(colorBrush);
    p.drawEllipse(r);
    p.restore();
}

QLineF CSPlayerProgress::calcTotalProgressLine()
{
    double w = width() - margin()*2;
    double x = margin();
    double y = height() / 2;

    return QLineF(x, y, x+w, y);
}

QLineF CSPlayerProgress::calcCurrentProgressLine()
{
    double w = progress() * (width() - margin()*2);
    double x = margin();
    double y = height() / 2;

    if (_controlling && valueInRange())
    {
        w = _posPressed.x() - x;
    }

    return QLineF(x, y, x+w, y);
}

/**
 * @brief Calculate the rect of hot region belongs to total progress, not the region that is shown
 * @return
 */
QRectF CSPlayerProgress::calcTotalProgressRect()
{
    double w = width() - margin()*2;
    double h = totalProgressHeight() * 3;
    double x = margin();
    double y = (height() - h) / 2;

    return QRectF(x, y, w, h);
}

QRectF CSPlayerProgress::calcCurrentProgressRect()
{
    double w = static_cast<int>(progress() * (width() - margin()*2));
    double h = currentProgressHeight();
    double x = margin();
    double y = (height() - h) / 2;

    return QRectF(x, y, w, h);
}

QRectF CSPlayerProgress::calcControlPointRect()
{
    double w = 24 * scaleRatio();
    double h = 24 * scaleRatio();
    double x = margin() + progress() * (width() - margin()*2) - w/2;
    double y = (height() - h) / 2;

    if (_controlling && valueInRange())
    {
        x = _posPressed.x() - w/2;
    }

    return QRectF(x, y, w, h);
}

/**
 * @brief Calculate current value by the position of mouse
 * @param posCurrent
 * @return
 */
qint64 CSPlayerProgress::calcCurrentValue(double x)
{
    qint64 val = static_cast<qint64>(_minRange + (x - margin()) * (_maxRange - _minRange) / (width() - margin()*2));
    return val;
}

/**
 * @brief Calculate the scale ratio
 * @return
 */
double CSPlayerProgress::scaleRatio() const
{
    double fw = static_cast<double>(width()) / _sizeOrg.width();
    double fh = static_cast<double>(height()) / _sizeOrg.height();
    return qMin(fw, fh);
}

/**
 * @brief CSPlayerProgress::margin
 * @return
 */
double CSPlayerProgress::margin() const
{
    return scMargin * scaleRatio();
}

/**
 * @brief CSPlayerProgress::totalProgressHeight
 * @return
 */
double CSPlayerProgress::totalProgressHeight() const
{
    return scTotalProgressH * scaleRatio();
}

/**
 * @brief CSPlayerProgress::currentProgressHeight
 * @return
 */
double CSPlayerProgress::currentProgressHeight() const
{
    return scCurrentProgressH * scaleRatio();
}

/**
 * @brief Adjust current value to let it between min range and max range
 */
void CSPlayerProgress::adjustCurrentValue()
{
    if (_value < _minRange) _value = _minRange;
    else if (_value > _maxRange) _value = _maxRange;
}

/**
 * @brief CSPlayerProgress::valueInRange
 * @return
 */
bool CSPlayerProgress::valueInRange() const
{
    return (_value > _minRange && _value < _maxRange);
}

}   // cs
