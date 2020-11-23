#ifndef CSVBoxLayout_H
#define CSVBoxLayout_H

#include "Layout/cslayout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSVBoxLayout : public CSLayout
{
public:
    CSVBoxLayout(CSWidget *wgt = nullptr);

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

#endif // CSVBoxLayout_H
