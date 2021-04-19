#ifndef CSPAIRCTRL_H
#define CSPAIRCTRL_H

/*****************************************************************************************
 * @author  cs
 * @date    2021-01-22
 * @brief   Create 2 controls that are subclass of `QWidget`, combine them and
 *          set horizontal layout by hand (use `resizeUI()` to realize it). You can use
 *          `CSPairCtrl` flexibly.
*****************************************************************************************/

#include "Control/cswidget.h"


namespace cs
{

template <typename T1, typename T2>
class CSPairCtrl : public CSWidget
{
public:
    CSPairCtrl(QWidget *parent = nullptr);
    virtual ~CSPairCtrl() override;

    // Access to inner controls
    T1 *leftControl() const;
    T2 *rightControl() const;

    // Set and get properties
    void setWidthFactor(double f);
    void setSpace(int s);

    double widthFactor() const;
    int space() const;

protected:
    // Initialize member and ui
    void initMember();
    void initUI();

protected:
    // Adaptive design when resize the widget
    void resizeUI();

protected:
    // Override methods
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    // T1, T2 must be subclass type of `QWidget`
    T1 *_ctrlLeft;
    T2 *_ctrlRight;

    // Customed properties
    int _space;
    double _factor;

};

}   // End of `cs`


// Include implement part
#define CSPAIRCTRL_IMPL_HPP
#include "cspairctrl_impl.hpp"


#endif // CSPAIRCTRL_H
