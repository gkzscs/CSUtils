#ifndef CS_PROGRESS_RING_H
#define CS_PROGRESS_RING_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSProgressRing : public cs::CSArtWare
{
public:
    explicit CSProgressRing(QWidget *parent = nullptr);

    void set_value(int prgr);
    int value() const;

    void set_font_color(const QColor &color);
    QColor font_color() const;

private:
    void init_member();
    void init_ui();

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    void drawAll(QPainter &p) override;
    void draw_ring(QPainter &p);
    void draw_progress_txt(QPainter &p);
    void draw_percent_txt(QPainter &p);

    void calc_ring_width();
    void calc_ring_rect();
    void calc_progress_txt_rect();
    void calc_percent_txt_rect();

private:
    double  _range_min;
    double  _range_max;
    int     _prgr;

private:
    // Assist variables
    int     _ring_w;
    QRect   _rc_ring;
    QRect   _rc_prgr_txt;
    QRect   _rc_percent_txt;

    QColor  _font_color;

};

}   // cs

#endif // CS_PROGRESS_RING_H
