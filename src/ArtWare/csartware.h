#ifndef CSARTWARE_H
#define CSARTWARE_H

/*************************************************************************************
 * @author: cs
 * @date: 2021/05/17
 * @brief:
 * The controls of this category are created for special use, they will show different
 * form with different configuration. In other words, they are dynamic, not always the
 * same.
*************************************************************************************/

#include <QWidget>
#include <QPainter>


namespace cs
{

class CSUTILS_EXPORT CSArtWare : public QWidget
{
    Q_OBJECT

public:
    CSArtWare(QWidget *parent = nullptr);

    void setColor(const QColor &color);
    void setBgColor(const QColor &cl);
    void set_font_pixel_size(int px);

    QColor color() const;
    QColor bgColor() const;
    int font_pixel_size() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

protected:
    virtual void drawAll(QPainter &p) = 0;

protected:
    void resetOriginSize(int w, int h);

    void scalePainter(QPainter &p);
    void rotate_coordinates(QPainter &p, double angle);

    void calc_center_point();

    void use_own_font(QPainter &p);

private:
    void initMember();
    void initUI();

protected:
    QSize   _sizeOrg;
    QColor  _color;
    QColor  _bgColor;
    int     _font_px;

protected:
    // Assist variables
    QPoint  _pt_center;

};

}   // `cs`

#endif // CSARTWARE_H
