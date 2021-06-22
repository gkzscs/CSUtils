#include "csartware.h"
#include "Core/csutils.h"


namespace cs
{

CSArtWare::CSArtWare(QWidget *parent)
    : QWidget(parent)
{
    initMember();
}

void CSArtWare::setPaintAreaSize(const QSize &s)
{
    _sizePaintArea = s;
    update();
}

QSize CSArtWare::paintAreaSize() const
{
    return _sizePaintArea;
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

QRect CSArtWare::paintAreaRect() const
{
    int w = _sizePaintArea.width();
    int h = _sizePaintArea.height();
    int x = (width() - w) / 2;
    int y = (height() - h) / 2;

    return QRect(x, y, w, h);
}

void CSArtWare::autoSetPaintAreaSize()
{
    const int margin = 1;
    setPaintAreaSize(QSize(width()-margin*2, height()-margin*2));
}

void CSArtWare::initMember()
{
    _sizePaintArea = QSize(40, 40);
}

void CSArtWare::initUI()
{
    // Set attribute
    resize(40, 40);
    autoSetPaintAreaSize();
}

}   // `cs`
