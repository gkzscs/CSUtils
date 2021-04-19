#ifdef  CSPAIRCTRL_IMPL_HPP
#include "cspairctrl.h"
#include <QMargins>


namespace cs
{

template <typename T1, typename T2>
CSPairCtrl<T1, T2>::CSPairCtrl(QWidget *parent)
    : CSWidget(parent)
{
    initMember();
    initUI();
}

template <typename T1, typename T2>
CSPairCtrl<T1, T2>::~CSPairCtrl()
{
    if (_ctrlLeft) _ctrlLeft->deleteLater();
    if (_ctrlRight) _ctrlRight->deleteLater();
}

template <typename T1, typename T2>
T1 *CSPairCtrl<T1, T2>::leftControl() const
{
    return _ctrlLeft;
}

template <typename T1, typename T2>
T2 *CSPairCtrl<T1, T2>::rightControl() const
{
    return _ctrlRight;
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::setWidthFactor(double f)
{
    if (f < 0) f = 0;
    else if (f > 1) f = 1;

    _factor = f;

    resizeUI();
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::setSpace(int s)
{
    _space = s;

    resizeUI();
}

template <typename T1, typename T2>
double CSPairCtrl<T1, T2>::widthFactor() const
{
    return _factor;
}

template <typename T1, typename T2>
int CSPairCtrl<T1, T2>::space() const
{
    return  _space;
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::initMember()
{
    _ctrlLeft = new T1(this);
    _ctrlRight = new T2(this);
    _space = 0;
    _factor = 0.5;

    // Set object name
    _ctrlLeft->setObjectName("ctrl_left");
    _ctrlRight->setObjectName("ctrl_right");
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::initUI()
{
    // Set attributes
    resize(160, 30);
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::resizeUI()
{
    // Calculate the geometry of controls
    auto margins = contentsMargins();
    int totalW = width() - _space - margins.left() - margins.right();
    int leftW = totalW * _factor;
    int rightW = totalW - leftW;
    int x = margins.left();
    int y = margins.top();
    int h = height() - margins.top() - margins.bottom();

    // Set geometry
    _ctrlLeft->setGeometry(x, y, leftW, h);
    _ctrlRight->setGeometry(x+leftW+_space, y, rightW, h);
}

template <typename T1, typename T2>
void CSPairCtrl<T1, T2>::resizeEvent(QResizeEvent *event)
{
    CSWidget::resizeEvent(event);

    resizeUI();
}

}   // End of `cs`

#endif
