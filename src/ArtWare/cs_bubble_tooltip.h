#ifndef CS_BUBBLE_TOOLTIP_H
#define CS_BUBBLE_TOOLTIP_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSBubbleTooltip : public cs::CSArtWare
{
    Q_OBJECT

public:
    enum BubbleAlign
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

public:
    CSBubbleTooltip();
    ~CSBubbleTooltip() override;

    void bind_widget(QWidget *wgt);
    QWidget *bound_widget() const;

    void set_max_width(int w);
    int max_width() const;

    void set_text(const QString &txt);
    QString text() const;

    void set_icon(const QPixmap &pix);

    void set_show_duration(int msec);
    int show_duration() const;

private:
    void init_member();
    void init_ui();

    void init_icon();
    void init_timers();

protected:
    void showEvent(QShowEvent *event) override;

private:
    void drawAll(QPainter &p) override;
    void draw_border(QPainter &p);
    void draw_arrow(QPainter &p);
    void draw_icon(QPainter &p);
    void draw_text(QPainter &p);

    void recalc_border_rect();
    void recalc_arrow_polygon();
    void recalc_icon_rect();
    void recalc_txt_rect();
    void recalc_bound_wgt_global_rect();
    void recalc_screen_size();

    void reset_font_attributes();
    void adjust_own_geometry();
    void adjust_own_size();
    void adjust_own_align();
    void adjust_own_position();

private:
    QWidget         *_bound_wgt;
    QTimer          *_tm_show;

    int             _show_duration;
    int             _max_width;
    BubbleAlign     _align;
    QString         _txt;
    QPixmap         _icon;

private:
    // Assist variables
    QFontMetrics    _fm;
    int             _line_height;
    int             _border_radius;
    int             _txt_left;
    QSize           _sz_arrow;
    QSize           _sz_screen;
    QRect           _rc_bound_wgt;
    QRect           _rc_border;
    QRect           _rc_icon;
    QRect           _rc_txt;
    QPolygon        _arrow_polyon;

};

}   // cs

#endif // CS_BUBBLE_TOOLTIP_H
