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
    void setColor(const QColor &color);

    bool textVisible() const;
    int value() const;
    QColor color() const;

protected:
    void drawAll(QPainter &p) override;
    void drawBody(QPainter &p);
    void drawHead(QPainter &p);
    void drawBackground(QPainter &p);

private:
    void initMember();
    void initUI();

private:
    QRect calcBodyRect() const;
    QRect calcHeadRect() const;
    QRect calcBgRect() const;

private:
    bool _textVisible;
    int _value;
    QColor _color;

};

}   // `cs`

#endif // CSBATTERYARTWARE_H
