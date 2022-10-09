#include "cs_bubble_tooltip.h"
#include <QDesktopWidget>
#include <QScreen>


namespace cs
{

CSBubbleTooltip::CSBubbleTooltip()
    : cs::CSArtWare(nullptr), _fm(QFontMetrics(font()))
{
    init_member();
    init_ui();
    init_timers();
}

CSBubbleTooltip::~CSBubbleTooltip()
{
    _bound_wgt = nullptr;
    DELETE_Q_POINTER(_tm_show);
}

void CSBubbleTooltip::bind_widget(QWidget *wgt)
{
    _bound_wgt = wgt;
    recalc_bound_wgt_global_rect();
}

QWidget *CSBubbleTooltip::bound_widget() const
{
    return _bound_wgt;
}

void CSBubbleTooltip::set_max_width(int w)
{
    _max_width = w;
    update();
}

int CSBubbleTooltip::max_width() const
{
    return _max_width;
}

void CSBubbleTooltip::set_text(const QString &txt)
{
    _txt = txt;

    reset_font_attributes();
    adjust_own_geometry();
    recalc_arrow_polygon();
    recalc_border_rect();
    recalc_icon_rect();
    recalc_txt_rect();
    update();
}

QString CSBubbleTooltip::text() const
{
    return _txt;
}

void CSBubbleTooltip::set_icon(const QPixmap &pix)
{
    _icon = pix;
    update();
}

void CSBubbleTooltip::set_show_duration(int msec)
{
    _show_duration = msec;
    _tm_show->setInterval(msec);
}

int CSBubbleTooltip::show_duration() const
{
    return _show_duration;
}

void CSBubbleTooltip::init_member()
{
    _bound_wgt = nullptr;
    _align = BottomRight;
    _show_duration = 2*1000;
    _max_width = 300;
    _border_radius = 8;
    _sz_arrow = QSize(10, 6);
    _bgColor = Qt::white;
    _color = Qt::red;

    init_icon();
    recalc_screen_size();
    reset_font_attributes();
}

void CSBubbleTooltip::init_ui()
{
    resize(100, 20);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void CSBubbleTooltip::init_icon()
{
    _icon = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
                "89504e470d0a1a0a0000000d49484452000000140000001408060000008d891d0d0000016649444154388dad953b4e425110863f5f50"
                "186401c6462ddc821812e20a7c008db6b2176c750d16c4c2de9868a4b4b250120b8d162ec046687e3337732370ce05af3ac99f9c3b8f"
                "ff3c32f35f043114044dc199e059d0177c081eddd7f09ca036700876054f822b414bb0eec5055fb73c66397b9308e7046d3f452db2d1"
                "386a9edbf6da80d0023782a54871164a826baf1d21ac0b7a827246e1ad23162bfb49eb29a1bdcdab602b929c428e58cc5011bc19977d"
                "1c082e23497908718ec3596007e8f077eb245c82176f87d8ae794eb8665cb6f8cc6ad29c84c6d1b72b0f80e23f5c39b179e01d58067a"
                "41f4dbbac04ce01db515e332c27ba03a85b01a7842db06eeecca17403308e7b766c235d4d895c843ff64520c9bded8c5d46172f43065"
                "f4ba11fff0e835c6c5e1d807bd1429ca422a0e561b95af935fc8d769967ca5d877f1b4d93c12ac0a16048b820df759cc72128519c6a4"
                "ae37d138f75fc0c0616bf3592c9c2ee00b74b074513dc5a92a0000000049454e44ae426082")));
}

void CSBubbleTooltip::init_timers()
{
    _tm_show = new QTimer(this);
    _tm_show->setSingleShot(true);
    _tm_show->setInterval(_show_duration);
    connect(_tm_show, &QTimer::timeout, [&]()
    {
        hide();
    });
}

void CSBubbleTooltip::showEvent(QShowEvent *e)
{
    cs::CSArtWare::showEvent(e);

    _tm_show->stop();
    _tm_show->start();
}

void CSBubbleTooltip::drawAll(QPainter &p)
{
    p.setRenderHints(QPainter::Antialiasing);

    draw_border(p);
    draw_arrow(p);
    draw_icon(p);
    draw_text(p);
}

void CSBubbleTooltip::draw_border(QPainter &p)
{
    p.save();
    p.setBrush(_bgColor);
    p.setPen(Qt::transparent);
    p.drawRoundedRect(_rc_border, _border_radius, _border_radius);
    p.restore();
}

void CSBubbleTooltip::draw_arrow(QPainter &p)
{
    const auto &poly = _arrow_polyon;

    p.save();
    p.setBrush(_bgColor);
    p.setPen(Qt::transparent);
    p.drawPolygon(poly);
    p.restore();
}

void CSBubbleTooltip::draw_icon(QPainter &p)
{
    if (_icon.isNull()) return;

    p.save();
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(_rc_icon, _icon.scaled(_rc_icon.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    p.restore();
}

void CSBubbleTooltip::draw_text(QPainter &p)
{
    p.save();    
    use_own_font(p);
    p.setPen(_color);
    p.drawText(_rc_txt, Qt::TextWordWrap | Qt::AlignLeft | Qt::AlignTop, _txt);
    p.restore();
}

void CSBubbleTooltip::recalc_border_rect()
{
    int x = 0;
    int y = 0;
    int w = width();
    int h = height() - _sz_arrow.height();
    switch (_align)
    {
    case TopLeft:
    case TopRight:
        break;
    case BottomLeft:
    case BottomRight:
        y = _sz_arrow.height();
        break;
    }

    _rc_border = QRect(x, y, w, h);
}

void CSBubbleTooltip::recalc_arrow_polygon()
{
    int x = 20;
    int w = _sz_arrow.width();
    int h = _sz_arrow.height();
    QPoint pt1, pt2, pt3;

    switch (_align)
    {
    case TopLeft:
        pt1 = QPoint(width()-x, height());
        pt2 = QPoint(width()-x+w/2, height()-h);
        pt3 = QPoint(width()-x-w/2, height()-h);
        break;
    case TopRight:
        pt1 = QPoint(x, height());
        pt2 = QPoint(x+w/2, height()-h);
        pt3 = QPoint(x-w/2, height()-h);
        break;
    case BottomLeft:
        pt1 = QPoint(width()-x, 0);
        pt2 = QPoint(width()-x+w/2, h);
        pt3 = QPoint(width()-x-w/2, h);
        break;
    case BottomRight:
        pt1 = QPoint(x, 0);
        pt2 = QPoint(x+w/2, h);
        pt3 = QPoint(x-w/2, h);
        break;
    }

    _arrow_polyon.clear();
    _arrow_polyon.append(pt1);
    _arrow_polyon.append(pt2);
    _arrow_polyon.append(pt3);
}

void CSBubbleTooltip::recalc_icon_rect()
{
    const int left = 6;
    const int top = 6;
    int x = _rc_border.x() + left;
    int y = _rc_border.y() + top;
    int h = _fm.height();
    int w = h;

    _rc_icon = QRect(x, y, w, h);
}

void CSBubbleTooltip::recalc_txt_rect()
{
    const int left = _txt_left;
    const int right = 6;
    const int hMargin = left + right;
    const int top = 6;
    int x = _rc_border.x() + left;
    int y = _rc_border.y() + top;
    int w = _rc_border.width() - hMargin;
    int h = _rc_border.height() - top*2;

    _rc_txt = QRect(x, y, w, h);
}

void CSBubbleTooltip::recalc_bound_wgt_global_rect()
{
    if (!_bound_wgt)
    {
        _rc_bound_wgt = QRect(0, 0, 0, 0);
        return;
    }

    auto pos = _bound_wgt->mapToGlobal(QPoint(0, 0));
    _rc_bound_wgt = QRect(pos.x(), pos.y(), _bound_wgt->width(), _bound_wgt->height());
}

void CSBubbleTooltip::recalc_screen_size()
{
    _sz_screen = QApplication::desktop()->size();
}

void CSBubbleTooltip::reset_font_attributes()
{
    auto f = font();
    f.setPixelSize(_font_px);
    _fm = QFontMetrics(f);
    _line_height = _fm.height() + _fm.leading();
    _txt_left = 6 + _fm.height() + 4;
}

void CSBubbleTooltip::adjust_own_geometry()
{
    adjust_own_size();
    adjust_own_align();
    adjust_own_position();
}

void CSBubbleTooltip::adjust_own_size()
{
    const int left = _txt_left;
    const int right = 6;
    const int hMargin = left + right;
    const int top = 6;
    int totalW = _fm.width(_txt);
    int lineW = (totalW <= _max_width-hMargin ? totalW : _max_width-hMargin);
    int lineCount = (totalW/lineW) + (totalW%lineW > 0 ? 1 : 0);
    int h = _line_height * lineCount - _fm.leading() + _sz_arrow.height() + top*2;

    resize(lineW+hMargin, h);
}

void CSBubbleTooltip::adjust_own_align()
{
    const int w = width();
    const int h = height();
    const auto rcWgt = _rc_bound_wgt;
    const int screenW = _sz_screen.width();
//    const int screenH = _sz_screen.height();

    if (rcWgt.x()+w <= screenW)
    {
        if (rcWgt.y()-h > 0) _align = TopRight;
        else _align = BottomRight;
    }
    else
    {
        if (rcWgt.y()-h > 0) _align = TopLeft;
        else _align = BottomLeft;
    }
}

void CSBubbleTooltip::adjust_own_position()
{
    const int right = 30;
    int x = _rc_bound_wgt.x();
    int y = _rc_bound_wgt.y() + _rc_bound_wgt.height();

    switch (_align)
    {
    case TopLeft:
        x = _rc_bound_wgt.x() - width() + right;
        y = _rc_bound_wgt.y() - height();
        break;
    case TopRight:
        y = _rc_bound_wgt.y() - height();
        break;
    case BottomLeft:
        x = _rc_bound_wgt.x() - width() + right;
        break;
    case BottomRight:
        break;
    }

    move(x, y);
}

}   // cs
