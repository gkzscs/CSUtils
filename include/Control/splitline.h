#ifndef SPLITLINE_H
#define SPLITLINE_H

#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT SplitLine : public CSWidget
{
    Q_OBJECT

public:
    enum Type
    {
        Normal,
        CircleRect
    };

public:
    SplitLine(QWidget *parent = nullptr);
    SplitLine(Type type, QWidget *parent = nullptr);

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

#endif // SPLITLINE_H
