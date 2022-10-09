#ifndef CSCARRIERARTWARE_H
#define CSCARRIERARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSCarrierArtWare : public CSArtWare
{
    Q_OBJECT

public:
    CSCarrierArtWare(QWidget *parent = nullptr);

    void setIntensity(int intensity);

    int intensity() const;

protected:
    void drawAll(QPainter &p) override;
    void drawBody(QPainter &p);

private:
    void initMember();
    void initUI();

private:
    QRect calcBlockRect(int intensity);

private:
    int _intensity;

};

}   // `cs`

#endif // CSCARRIERARTWARE_H
