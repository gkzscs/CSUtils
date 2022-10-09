#ifndef CS_WIND_DIRECTION_H
#define CS_WIND_DIRECTION_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSWindVane : public cs::CSArtWare
{
public:
    explicit CSWindVane(QWidget *parent = nullptr);

    void set_wind_direction(double angle);
    double wind_direction() const;

private:
    void init_member();

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    void drawAll(QPainter &p) override;
    void draw_pixmap(QPainter &p);

    void calc_pixmap_rect();

private:
    double  _wind_direction;
    QPixmap _pixmap;

private:
    // Assist variables
    QRect   _rc_pixmap;

};

}   // cs

#endif // CS_WIND_DIRECTION_H
