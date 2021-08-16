#ifndef CSBATTERYARTWARE_H
#define CSBATTERYARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSBatteryArtWare : public CSArtWare
{
    Q_OBJECT

public:
    CSBatteryArtWare(QWidget *parent = nullptr);

    void setTextVisible(bool flag);
    void setValue(int v);

    bool textVisible() const;
    int value() const;

protected:
    void drawAll(QPainter &p) override;
    void drawBody(QPainter &p);
    void drawHead(QPainter &p);
    void drawBackground(QPainter &p);

private:
    void initMember();

private:
    QRect calcBodyRect() const;
    QRect calcHeadRect() const;
    QRect calcBgRect() const;

private:
    bool _textVisible;
    int _value;

};

}   // `cs`

#endif // CSBATTERYARTWARE_H
