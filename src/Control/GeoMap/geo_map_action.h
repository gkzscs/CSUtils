#ifndef GEO_MAP_ACTION_H
#define GEO_MAP_ACTION_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT GeoMapAction : public cs::CSWidget
{
    Q_OBJECT

public:
    GeoMapAction(QWidget *parent = nullptr);
    GeoMapAction(const QString &txt, QWidget *parent = nullptr);
    GeoMapAction(const QPixmap &pix, const QString &txt, QWidget *parent = nullptr);

    void set_icon(const QPixmap &pix);
    QPixmap icon() const;

    void set_text(const QString &txt);
    QString text() const;

    void set_icon_size(const QSize &sz);
    QSize icon_size() const;

    void set_space(int n);
    int space() const;

    void set_padding_left(int n);
    int padding_left() const;

    void set_padding_right(int n);
    int padding_right() const;

private:
    void init_member();
    void init_ui();

protected:
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void draw_all(QPainter &p);
    void draw_icon(QPainter &p);
    void draw_text(QPainter &p);

    void calc_all();
    void calc_icon_rect();
    void calc_text_rect();

signals:
    void triggered();

private:
    QPixmap _icon;
    QString _txt;
    QSize   _sz_icon;
    int     _space;
    int     _padding_left;
    int     _padding_right;

private:
    // Assist variables
    QRect _rc_icon;
    QRect _rc_txt;

};

}   // cs

#endif // GEO_MAP_ACTION_H
