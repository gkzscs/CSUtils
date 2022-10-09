#ifndef CSGcsBattery_H
#define CSGcsBattery_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSGcsBattery : public cs::CSArtWare
{
public:
    CSGcsBattery(QWidget *parent = nullptr);

    void setChargeStatus(bool charge);
    void setQuantity(double val);

    bool chargeStatus() const;
    double quantity() const;

private:
    void initMember();

private:
    void drawAll(QPainter &p) override;
    void drawImage(QPainter &p);
    void drawElectricQuantity(QPainter &p);

private:
    QRectF calcElectricQuantityRect() const;

    void updateColor();

private:
    bool _charge;
    double _quantity;
    QPixmap _pixBattery;
    QPixmap _pixFlash;

};

}   // cs

#endif // CSGcsBattery_H
