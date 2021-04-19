#ifndef CSLabelControl_H
#define CSLabelControl_H

#include "cswidget.h"


namespace cs
{   // Start of namespace `cs`

template <typename T>
class CSUTILS_EXPORT CSLabelControl : public CSWidget
{
public:
    CSLabelControl(QWidget *parent = nullptr);
    virtual ~CSLabelControl() override;

    void setWidthFactor(double f);
    void setSpacing(int n);

    double getWidthFactor() const;
    int getSpacing() const;
    QLabel *label() const;
    T *control() const;

protected:
    virtual void initMember() override;
    virtual void initUI() override;

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    QLabel *_lab;
    T *_control;    // This must be an instance of `QWidget`

    int _space;
    double _factor;
};

}   // End of namespace `cs`

#endif // CSLabelControl_H
