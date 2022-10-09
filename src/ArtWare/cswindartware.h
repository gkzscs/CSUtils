#ifndef CSWINDARTWARE_H
#define CSWINDARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSWindArtWare : public cs::CSArtWare
{
public:
    CSWindArtWare(QWidget *parent = nullptr);

    void setDirection(double angle);
    void setLevel(int lv);

    double direction() const;
    int level() const;

private:
    void drawAll(QPainter &p) override;
    void drawWind(QPainter &p);

    void drawWindLevel0(QPainter &p);
    void drawWindNoMoreThanLevel7(QPainter &p, const QSize &s);
    void drawWindAboveLevel7(QPainter &p, const QSize &s);

private:
    QRect calcWindRect() const;

private:
    void initMember();

private:
    int _level;
    double _angle;

};

}   // `cs`

#endif // CSWINDARTWARE_H
