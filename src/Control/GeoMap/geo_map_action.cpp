#include "geo_map_action.h"


namespace cs
{

GeoMapAction::GeoMapAction(QWidget *parent)
    : cs::CSWidget(parent)
{
    init_member();
    init_ui();
}

GeoMapAction::GeoMapAction(const QString &txt, QWidget *parent)
    : GeoMapAction(parent)
{
    set_text(txt);
}

GeoMapAction::GeoMapAction(const QPixmap &pix, const QString &txt, QWidget *parent)
    : GeoMapAction(txt, parent)
{
    set_icon(pix);
}

void GeoMapAction::set_icon(const QPixmap &pix)
{
    _icon = pix;
    update();
}

QPixmap GeoMapAction::icon() const
{
    return _icon;
}

void GeoMapAction::set_text(const QString &txt)
{
    _txt = txt;
    update();
}

QString GeoMapAction::text() const
{
    return _txt;
}

void GeoMapAction::set_icon_size(const QSize &sz)
{
    _sz_icon = sz;
    update();
}

QSize GeoMapAction::icon_size() const
{
    return _sz_icon;
}

void GeoMapAction::set_space(int n)
{
    _space = n;
    update();
}

int GeoMapAction::space() const
{
    return _space;
}

void GeoMapAction::set_padding_left(int n)
{
    _padding_left = n;
    update();
}

int GeoMapAction::padding_left() const
{
    return _padding_left;
}

void GeoMapAction::set_padding_right(int n)
{
    _padding_right = n;
    update();
}

int GeoMapAction::padding_right() const
{
    return _padding_right;
}

void GeoMapAction::init_member()
{
    _space = 30;
    _padding_left = 30;
    _padding_right = 10;
    _sz_icon = QSize(36, 36);
}

void GeoMapAction::init_ui()
{
    resize(250, 56);
}

void GeoMapAction::resizeEvent(QResizeEvent *e)
{
    cs::CSWidget::resizeEvent(e);

    calc_all();
}

void GeoMapAction::paintEvent(QPaintEvent *e)
{
    cs::CSWidget::paintEvent(e);

    QPainter p(this);
    draw_all(p);
}

void GeoMapAction::mouseReleaseEvent(QMouseEvent *e)
{
    cs::CSWidget::mouseReleaseEvent(e);

    emit triggered();
}

void GeoMapAction::draw_all(QPainter &p)
{
    draw_icon(p);
    draw_text(p);
}

void GeoMapAction::draw_icon(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(_rc_icon, _icon.scaled(_rc_icon.size()));
    p.restore();
}

void GeoMapAction::draw_text(QPainter &p)
{
    p.save();
    p.drawText(_rc_txt, Qt::AlignVCenter | Qt::AlignLeft, _txt);
    p.restore();
}

void GeoMapAction::calc_all()
{
    calc_icon_rect();
    calc_text_rect();
}

void GeoMapAction::calc_icon_rect()
{
    int w = _sz_icon.width();
    int h = _sz_icon.height();
    int x = _padding_left;
    int y = (height() - h) / 2;

    _rc_icon = QRect(x, y, w, h);
}

void GeoMapAction::calc_text_rect()
{
    int x = _padding_left + _sz_icon.width() + _space;
    int y = 0;
    int w = width() - x - _padding_right;
    int h = height();

    _rc_txt = QRect(x, y, w, h);
}


}   // cs
