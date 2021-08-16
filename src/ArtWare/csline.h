#ifndef CSLine_H
#define CSLine_H

#include "Control/Base/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT CSLine : public CSArtWare
{
    Q_OBJECT

public:
    enum Type
    {
        Normal,
        CircleRect
    };

public:
    CSLine(QWidget *parent = nullptr);
    CSLine(Type type, QWidget *parent = nullptr);

    void setType(Type type);
    Type getType() const;

protected:
    void drawAll(QPainter &p) override;
    void drawNormal(QPainter &p);
    void drawCircleRect(QPainter &p);

private:
    void initUI();

private:
    Type _type;

};

}   // End of `cs`

#endif // CSLine_H
