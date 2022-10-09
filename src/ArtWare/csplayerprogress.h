#ifndef CSPLAYERPROGRESS_H
#define CSPLAYERPROGRESS_H

#include "csartware.h"


namespace cs
{

class CSUTILS_EXPORT CSPlayerProgress : public cs::CSArtWare
{
    Q_OBJECT

public:
    CSPlayerProgress(QWidget *parent = nullptr);

//    void setBgColor(const QColor &bgColor);
    void setRange(qint64 min, qint64 max);
    void setValue(qint64 val);

    qint64 minRange() const;
    qint64 maxRange() const;
    qint64 value() const;
    double progress() const;

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    void initMember();
    void initUI();

private:
    void drawAll(QPainter &p) override;
    void drawTotalProgress(QPainter &p);
    void drawCurrentProgress(QPainter &p);
    void drawControlPoint(QPainter &p);

private:
    QLineF calcTotalProgressLine();
    QLineF calcCurrentProgressLine();
    QRectF calcTotalProgressRect();
    QRectF calcCurrentProgressRect();
    QRectF calcControlPointRect();
    qint64 calcCurrentValue(double x);
    double scaleRatio() const;
    double margin() const;
    double totalProgressHeight() const;
    double currentProgressHeight() const;

    void adjustCurrentValue();
    bool valueInRange() const;

signals:
    void rangeChangedSignal(qint64 minRange, qint64 maxRange);
    void valueChangedSignal(qint64 val);
    void valueChangedByHandSignal(qint64 val);

private:
    qint64 _minRange;
    qint64 _maxRange;
    qint64 _value;
//    QColor _colorBg;

    bool _controlling;
    QPointF _posPressed;

};

}   // cs

#endif // CSPLAYERPROGRESS_H
