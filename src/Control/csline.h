#ifndef CSLine_H
#define CSLine_H

#include "Control/cswidget.h"


namespace cs
{

class CSUTILS_EXPORT CSLine : public CSWidget
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
    void initUI();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    void drawNormal(QPainter &p);
    void drawCircleRect(QPainter &p);

private:
    Type _type;

};

}   // End of `cs`

#endif // CSLine_H
