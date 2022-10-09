#include "cs_wind_vane.h"


namespace cs
{

CSWindVane::CSWindVane(QWidget *parent)
    : cs::CSArtWare(parent)
{
    init_member();
}

void CSWindVane::set_wind_direction(double angle)
{
    _wind_direction = angle;
    update();
}

double CSWindVane::wind_direction() const
{
    return _wind_direction;
}

void CSWindVane::init_member()
{
    _wind_direction = 0;
    _pixmap = QPixmap::fromImage(QImage::fromData(QByteArray::fromHex(
                "89504e470d0a1a0a0000000d49484452000000280000002808060000008cfeb86d0000001974455874536f6674776172650041"
                "646f626520496d616765526561647971c9653c000001744944415478daec57818d83300c2cd50fc0081d8111e804304247a01b"
                "7403ba0123543f01bf01dd202330024daa205ddd44e4832324e4932ca4c460e76cc7e670100804024134a669aab5745ad4f40d"
                "65f7ea2d1c2b3d4ef96074cb185b598473ad7e34b0f4d4f2abe58fa81a872a2d05acddb32cbba664ae03568610562cdb03bcd7"
                "a572ae45235a7270e0e108a9d13f599d9c1cae4d91731f0c58a37d40feb5701874b2e474504158732b18b6dbcc1654774fd281"
                "bea738af928f53a3112d05e83646c8bbe3eca4231a3567610c84d191b07601c317582facae82b581ad6020bcb7c01c5dcc319b"
                "123c615e32080c518c187edf8196ec1f573a6faad38429776cbff7e60a8ec57125c10de9141405e93affc6cf4a07efa4c5f5f6"
                "7926ad30e960b05824345f03f4828b2424c4334315e3b92bf26dde8b7a0d83ec17b5abd5c53a98a4d5f986058f9eb9fbc6c071"
                "ade42e16e7b845744ed8fe0873e9c6ad2d07d67d8dfc5bfc34edf3b75320100876849700030008e08c9d229ddae60000000049"
                "454e44ae426082")));
}

void CSWindVane::resizeEvent(QResizeEvent *e)
{
    cs::CSArtWare::resizeEvent(e);

    calc_pixmap_rect();
}

void CSWindVane::drawAll(QPainter &p)
{
    cs::CSArtWare::drawAll(p);
    draw_pixmap(p);
}

void CSWindVane::draw_pixmap(QPainter &p)
{
    int angle = static_cast<int>(_wind_direction + 180) % 360;

    p.save();
    rotate_coordinates(p, angle);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(_rc_pixmap, _pixmap.scaled(_rc_pixmap.size()));
    p.restore();
}

void CSWindVane::calc_pixmap_rect()
{
    int w = qMin(width(), height());
    int h = w;
    int x = (width() - w) / 2;
    int y = (height() - h) / 2;

    _rc_pixmap = QRect(x, y, w, h);
}


}   // cs
