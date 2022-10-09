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

    void setBgColor(const QColor &bgColor);
    void setRange(double max);
    void setRange(double min, double max);
    void setValue(double val);

    double minRange() const;
    double maxRange() const;
    double value() const;
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
    QLine calcTotalProgressLine();
    QLine calcCurrentProgressLine();
    QRect calcTotalProgressRect();
    QRect calcCurrentProgressRect();
    QRect calcControlPointRect();
    double calcCurrentValue(int x);
    double scaleRatio() const;
    int margin() const;
    int totalProgressHeight() const;
    int currentProgressHeight() const;

    void adjustCurrentValue();
    bool valueInRange() const;

signals:
    void rangeChangedSignal(double minRange, double maxRange);
    void valueChangedSignal(double val);
    void valueChangedByHandSignal(double val);

private:
    double _minRange;
    double _maxRange;
    double _value;
    QColor _colorBg;

    bool _controlling;
    QPoint _posPressed;

};

}   // cs

#endif // CSPLAYERPROGRESS_H
