#ifndef CSLayout_H
#define CSLayout_H

#include "Core/cscontainer.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSLayout : public CSContainer<QWidget>
{
public:
    CSLayout(CSWidget *wgt = nullptr);
    virtual ~CSLayout() override;

    void setMargins(QMargins m);
    void setMargins(int left, int top, int right, int bottom);
    QMargins margins() const;
    virtual void refresh() override;
    virtual void changeSize(const QSize &newSize, const QSize &oldSize);

protected:
    virtual void init() override;

    virtual void actualRefresh() override;
    virtual void clearLayout(QWidget *wgt) override;
    virtual void resetLayout() = 0;

protected:
    CSWidget *_wgt;
    QMargins _margins;

    QList<QWidget *> _oldItems;

};


/************************************* Extern template class **************************************/
extern template class CSContainer<QWidget>;

}   // End of namespace `cs`

#endif // CSLayout_H
