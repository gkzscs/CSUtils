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

QColor CSArtWare::color() const
{
    return _color;
}

void CSArtWare::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    cs::CSUtils::enableStyleSheet(this);

    // Draw all you want to show
    QPainter p(this);
    drawAll(p);
}

void CSArtWare::drawAll(QPainter &p)
{
    Q_UNUSED(p)

    // To do
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

void CSArtWare::initMember()
{
    _sizeOrg = QSize(40, 40);
    _color = Qt::white;
}

void CSArtWare::initUI()
{
    // Set attribute
    resize(_sizeOrg);
}

}   // `cs`
