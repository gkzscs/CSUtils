#ifndef CSLINKQUALITYARTWARE_H
#define CSLINKQUALITYARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSLinkQualityArtWare : public cs::CSArtWare
{
public:
    enum Type
    {
        Up,
        Down
    };

public:
    CSLinkQualityArtWare(Type type, QWidget *parent = nullptr);

    void setValue(int val);

    int value() const;

private:
    void drawAll(QPainter &p) override;
    void drawArrow(QPainter &p);
    void drawLinkQuality(QPainter &p);
    void drawText(QPainter &p);

    void drawUpArrow(QPainter &p);
    void drawDownArrow(QPainter &p);
    void drawLinkQuality(QPainter &p, int val);

private:
    QRect calcArrowRect() const;
    QLine calcLinkQualityLine(int level) const;
    QRect calcTextRect() const;

private:
    void setType(Type type);

private:
    Type _type;
    int _value;

};

}   // `cs`

#endif // CSLINKQUALITYARTWARE_H
