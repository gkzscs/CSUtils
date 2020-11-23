#ifndef VBOXLAYOUT_H
#define VBOXLAYOUT_H

#include "Layout/layout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT VBoxLayout : public Layout
{
public:
    VBoxLayout(CSWidget *wgt = nullptr);

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

#endif // VBOXLAYOUT_H
