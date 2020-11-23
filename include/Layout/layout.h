#ifndef LAYOUT_H
#define LAYOUT_H

#include "Core/container.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT Layout : public Container<QWidget>
{
public:
    Layout(CSWidget *wgt = nullptr);
    virtual ~Layout() override;

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
extern template class Container<QWidget>;

}   // End of namespace `cs`

#endif // LAYOUT_H
