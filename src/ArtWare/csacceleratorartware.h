#ifndef CSACCELERATORARTWARE_H
#define CSACCELERATORARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSAcceleratorArtWare : public cs::CSArtWare
{
public:
    CSAcceleratorArtWare(QWidget *parent = nullptr);

    void setValue(int v);

    int value() const;

protected:
    void drawAll(QPainter &p) override;
    void drawArch(QPainter &p);
    void drawPointer(QPainter &p);

    void drawArch(QPainter &p, int curSpanAngle);

private:
    QRect calcArchRect() const;
    QPoint calcPointerBasePoint() const;
    QPolygon calcTrianglePolygon() const;
    int calcRotateAngle() const;

private:
    void initMember();
    void initUI();

private:
    int _value;

};

}   // `cs`

#endif // CSACCELERATORARTWARE_H
