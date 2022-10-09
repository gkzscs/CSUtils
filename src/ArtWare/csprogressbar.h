#ifndef CSPROGRESSBAR_H
#define CSPROGRESSBAR_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSProgressBar : public cs::CSArtWare
{
    Q_OBJECT

public:
    CSProgressBar(QWidget *parent = nullptr);

//    void setBgColor(const QColor &cl);
    void setRange(double min, double max);
    void setValue(double val);

//    QColor bgColor() const;
    double minRange() const;
    double maxRange() const;
    double value() const;

private:
    void initMember();
    void initUI();

private:
    void drawAll(QPainter &p) override;
    void drawBaseBar(QPainter &p);
    void drawCurrentBar(QPainter &p);

private:
    QLineF calcBaseLine();
    QLineF calcCurrentLine();

    void alterPen(QPainter &p, double w, const QColor &cl);

private:
    void adjustValue();

private:
    double _minRange;
    double _maxRange;
    double _value;
//    QColor _colorBg;

};

}   // cs

#endif // CSPROGRESSBAR_H
