#ifndef CSSECTORLINKARTWARE_H
#define CSSECTORLINKARTWARE_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSSectorLinkArtWare : public cs::CSArtWare
{
public:
    enum Type
    {
        Up,
        Down
    };

public:
    CSSectorLinkArtWare(Type type, QWidget *parent = nullptr);

    void setText(const QString &txt);
    void setTextColor(const QColor &color);

    QString text() const;
    QColor textColor() const;
    Type type() const;

protected:
    void drawAll(QPainter &p) override;
    void drawImage(QPainter &p);
    void drawText(QPainter &p);

private:
    void setType(Type type);
    void updatePixmap();

private:
    QRect calcImageRect() const;
    QRect calcTextRect() const;

private:
    QColor _txtColor;
    Type _type;
    QPixmap _pix;
    QString _txt;

};

}   // `cs`


#endif // CSSECTORLINKARTWARE_H
