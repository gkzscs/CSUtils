#ifndef CSHBoxLayout_H
#define CSHBoxLayout_H

#include "Layout/cslayout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSHBoxLayout : public CSLayout
{
public:
    CSHBoxLayout(CSWidget *wgt = nullptr);

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


#endif // CSHBoxLayout_H
