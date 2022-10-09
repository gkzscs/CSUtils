#include "csartware.h"
#include "Core/csutils.h"


namespace cs
{

CSArtWare::CSArtWare(QWidget *parent)
    : QWidget(parent)
{
    initMember();
    initUI();
}

void CSArtWare::setColor(const QColor &color)
{
    _color = color;
    update();
}

void CSArtWare::setBgColor(const QColor &cl)
{
    _bgColor = cl;
    update();
}

void CSArtWare::set_font_pixel_size(int px)
{
    _font_px = px;
    update();
}

QColor CSArtWare::color() const
{
    return _color;
}

QColor CSArtWare::bgColor() const
{
    return _bgColor;
}

int CSArtWare::font_pixel_size() const
{
    return _font_px;
}

void CSArtWare::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    cs::CSUtils::enableStyleSheet(this);

    // Draw all you want to show
    QPainter p(this);
    drawAll(p);
}

void CSArtWare::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    calc_center_point();
}

void CSArtWare::drawAll(QPainter &p)
{
    Q_UNUSED(p)

    // To do
}

/**
 * @brief Set the origin size
 * @param sz
 */
void CSArtWare::resetOriginSize(int w, int h)
{
    _sizeOrg = QSize(w, h);
    resize(_sizeOrg);
}

/**
 * @brief Scale the painter by current size
 * @param p
 */
void CSArtWare::scalePainter(QPainter &p)
{
    double fw = static_cast<double>(width()) / _sizeOrg.width();
    double fh = static_cast<double>(height()) / _sizeOrg.height();

    p.scale(fw, fh);
}

void CSArtWare::rotate_coordinates(QPainter &p, double angle)
{
    p.translate(_pt_center);
    p.rotate(angle);
    p.translate(-_pt_center);
}

void CSArtWare::calc_center_point()
{
    _pt_center = QPoint(width()/2, height()/2);
}

void CSArtWare::use_own_font(QPainter &p)
{
    auto f = font();
    f.setPixelSize(_font_px);
    p.setFont(f);
}

void CSArtWare::initMember()
{
    _color = Qt::white;
    _bgColor = Qt::transparent;
    _font_px = 14;
}

void CSArtWare::initUI()
{
    // Set attribute
    resetOriginSize(40, 40);
}

}   // `cs`
