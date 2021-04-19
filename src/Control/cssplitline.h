#ifndef CSSplitLine_H
#define CSSplitLine_H

#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSSplitLine : public CSWidget
{
    Q_OBJECT

public:
    enum Type
    {
        Normal,
        CircleRect
    };

public:
    CSSplitLine(QWidget *parent = nullptr);
    CSSplitLine(Type type, QWidget *parent = nullptr);

    void setType(Type type);
    Type getType() const;

protected:
    virtual void initUI() override;

protected:
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    void drawNormal(QPainter &p);
    void drawCircleRect(QPainter &p);

private:
    Type _type;

};

} // End of namespace `cs`

#endif // CSSplitLine_H
