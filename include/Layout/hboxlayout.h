#ifndef HBOXLAYOUT_H
#define HBOXLAYOUT_H

#include "Layout/layout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT HBoxLayout : public Layout
{
public:
    HBoxLayout(CSWidget *wgt = nullptr);

    void setSpace(int n);
    int space() const;

    virtual void changeSize(const QSize &newSize, const QSize &oldSize) override;

protected:
    virtual void init() override;

    virtual void resetLayout() override;

protected:
    int _space;

};

}   // End of namespace `cs`


#endif // HBOXLAYOUT_H
