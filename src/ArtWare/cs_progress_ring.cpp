#include "cs_progress_ring.h"


namespace cs
{

CSProgressRing::CSProgressRing(QWidget *parent)
    : cs::CSArtWare(parent)
{
    init_member();
    init_ui();
}

void CSProgressRing::set_value(int prgr)
{
    prgr = (prgr < 0 ? 0 : prgr);
    prgr = (prgr > 100 ? 100 : prgr);
    _prgr = prgr;
    update();
}

int CSProgressRing::value() const
{
    return _prgr;
}

void CSProgressRing::set_font_color(const QColor &color)
{
    _font_color = color;
    update();
}

QColor CSProgressRing::font_color() const
{
    return _font_color;
}

void CSProgressRing::init_member()
{
    _prgr = 0;
    _range_min = 0.0;
    _range_max = 100.0;

    _color = QColor(15, 255, 255);
    _font_color = Qt::white;
}

void CSProgressRing::init_ui()
{
    resetOriginSize(72, 72);
}

void CSProgressRing::resizeEvent(QResizeEvent *e)
{
    cs::CSArtWare::resizeEvent(e);

    calc_ring_width();
    calc_ring_rect();
    calc_progress_txt_rect();
    calc_percent_txt_rect();
}

void CSProgressRing::drawAll(QPainter &p)
{
    draw_ring(p);
    draw_progress_txt(p);
    draw_percent_txt(p);
}

void CSProgressRing::draw_ring(QPainter &p)
{
    const QColor bgColor(189, 189, 189);
    int startAngle = 90 * 16;
    int spanTotalAngle = -360 * 16;
    int spanAngle = static_cast<int>((_prgr - _range_min) * spanTotalAngle / (_range_max - _range_min));

    // Set pen's width
    auto pen = p.pen();
    pen.setWidthF(_ring_w);

    p.save();
    scalePainter(p);
    p.setRenderHint(QPainter::Antialiasing);
    pen.setColor(bgColor);
    p.setPen(pen);
    p.drawArc(_rc_ring, startAngle, spanTotalAngle);

    pen.setColor(_color);
    p.setPen(pen);
    p.drawArc(_rc_ring, startAngle, spanAngle);
    p.restore();
}

void CSProgressRing::draw_progress_txt(QPainter &p)
{
    auto txt = QString::number(_prgr);
    auto f = p.font();
    f.setPixelSize(18);
    f.setBold(true);

    p.save();
    scalePainter(p);
    p.setFont(f);
    p.setPen(_font_color);
    p.drawText(_rc_prgr_txt, Qt::AlignRight | Qt::AlignVCenter, txt);
    p.restore();
}

void CSProgressRing::draw_percent_txt(QPainter &p)
{
    auto txt = "%";
    auto f = p.font();
    f.setPixelSize(12);
    f.setBold(true);

    p.save();
    scalePainter(p);
    p.setFont(f);
    p.setPen(_font_color);
    p.drawText(_rc_percent_txt, Qt::AlignRight | Qt::AlignVCenter, txt);
    p.restore();
}

void CSProgressRing::calc_ring_width()
{
    _ring_w = 6;
}

void CSProgressRing::calc_ring_rect()
{
    int w = width() - _ring_w;
    int h = height() - _ring_w;
    int x = (width() - w) / 2;
    int y = (height() - h) / 2;

    _rc_ring = QRect(x, y, w, h);
}

void CSProgressRing::calc_progress_txt_rect()
{
    int w = width() / 2;
    int h = height();
    int x = 10;
    int y = 0;

    _rc_prgr_txt = QRect(x, y, w, h);
}

void CSProgressRing::calc_percent_txt_rect()
{
    int x = _rc_prgr_txt.right() + 4;
    int y = 0;
    int w = 10;
    int h = height();

    _rc_percent_txt = QRect(x, y, w, h);
}

}   // cs
