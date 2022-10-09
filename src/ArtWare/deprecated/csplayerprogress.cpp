#include "csplayerprogress.h"


namespace cs
{

static const int scMargin = 12;
static const int scTotalProgressH = 4;
static const int scCurrentProgressH = 6;


CSPlayerProgress::CSPlayerProgress(QWidget *parent)
    : cs::CSArtWare(parent)
{
    initMember();
    initUI();
}

void CSPlayerProgress::setBgColor(const QColor &bgColor)
{
    _colorBg = bgColor;
    update();
}

void CSPlayerProgress::setRange(double max)
{
    if (max <= _minRange) return;
    _maxRange = max;
    adjustCurrentValue();

    update();
    emit rangeChangedSignal(_minRange, _maxRange);
}

void CSPlayerProgress::setRange(double min, double max)
{
    if (max <= min) return;
    _minRange = min;
    _maxRange = max;
    adjustCurrentValue();

    update();
    emit rangeChangedSignal(_minRange, _maxRange);
}

void CSPlayerProgress::setValue(double val)
{
    _value = val;
    adjustCurrentValue();

    update();
    emit valueChangedSignal(_value);
}

double CSPlayerProgress::minRange() const
{
    return _minRange;
}

double CSPlayerProgress::maxRange() const
{
    return _maxRange;
}

double CSPlayerProgress::value() const
{
    return _value;
}

double CSPlayerProgress::progress() const
{
    double prgr = (_value - _minRange) / (_maxRange - _minRange);
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
        double val = calcCurrentValue(e->x());
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
        double val = calcCurrentValue(e->x());
        setValue(val);

        emit valueChangedByHandSignal(val);
    }
}

void CSPlayerProgress::initMember()
{
//    _sizeOrg = QSize(100, 30);
    _minRange = 0.0;
    _maxRange = 100.0;
    _value = 50.0;
    _colorBg = QColor(255, 255, 255, 128);
    _controlling = false;
    _posPressed = QPoint(0, 0);
}

void CSPlayerProgress::initUI()
{
    // Set attributes
    resetOriginSize(100, 30);
//    resize(_sizeOrg);
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
    pen.setWidth(penW);
    pen.setColor(_colorBg);
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
    pen.setWidth(penW);
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

QLine CSPlayerProgress::calcTotalProgressLine()
{
    int w = static_cast<int>(width() - margin()*2);
    int x = margin();
    int y = height() / 2;

    return QLine(x, y, x+w, y);
}

QLine CSPlayerProgress::calcCurrentProgressLine()
{
    int w = static_cast<int>(progress() * (width() - margin()*2));
    int x = margin();
    int y = height() / 2;

    if (_controlling && valueInRange())
    {
        w = _posPressed.x() - x;
    }

    return QLine(x, y, x+w, y);
}

/**
 * @brief Calculate the rect of hot region belongs to total progress, not the region that is shown
 * @return
 */
QRect CSPlayerProgress::calcTotalProgressRect()
{
    int w = width() - margin()*2;
    int h = totalProgressHeight() * 3;
    int x = margin();
    int y = (height() - h) / 2;

    return QRect(x, y, w, h);
}

QRect CSPlayerProgress::calcCurrentProgressRect()
{
    int w = static_cast<int>(progress() * (width() - margin()*2));
    int h = currentProgressHeight();
    int x = margin();
    int y = (height() - h) / 2;

    return QRect(x, y, w, h);
}

QRect CSPlayerProgress::calcControlPointRect()
{
    int w = static_cast<int>(24 * scaleRatio());
    int h = static_cast<int>(24 * scaleRatio());
    int x = margin() + static_cast<int>(progress() * (width() - margin()*2)) - w/2;
    int y = (height() - h) / 2;

    if (_controlling && valueInRange())
    {
        x = _posPressed.x() - w/2;
    }

    return QRect(x, y, w, h);
}

/**
 * @brief Calculate current value by the position of mouse
 * @param posCurrent
 * @return
 */
double CSPlayerProgress::calcCurrentValue(int x)
{
    double val = _minRange + (x - margin()) * (_maxRange - _minRange) / (width() - margin()*2);
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
int CSPlayerProgress::margin() const
{
    return static_cast<int>(scMargin * scaleRatio());
}

/**
 * @brief CSPlayerProgress::totalProgressHeight
 * @return
 */
int  CSPlayerProgress::totalProgressHeight() const
{
    return static_cast<int>(scTotalProgressH * scaleRatio());
}

/**
 * @brief CSPlayerProgress::currentProgressHeight
 * @return
 */
int  CSPlayerProgress::currentProgressHeight() const
{
    return static_cast<int>(scCurrentProgressH * scaleRatio());
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
