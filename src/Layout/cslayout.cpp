#include "cslayout.h"


namespace cs
{   // Start of namespace `cs`

CSLayout::CSLayout(CSWidget *wgt)
    : CSContainer<QWidget>(), _wgt(wgt)
{
    init();
}

CSLayout::~CSLayout()
{
    _wgt = nullptr;

    qDeleteAll(_listOldItems);
    _listOldItems.clear();
}

void CSLayout::setMargins(QMargins m)
{
    _margins = m;
    refresh();
}

void CSLayout::setMargins(int left, int top, int right, int bottom)
{
    QMargins m(left, top, right, bottom);
    setMargins(m);
}

QMargins CSLayout::margins() const
{
    return _margins;
}

void CSLayout::refresh()
{
    CSContainer<QWidget>::refresh();
}

void CSLayout::changeSize(const QSize &newSize, const QSize &oldSize)
{
    Q_UNUSED(newSize)
    Q_UNUSED(oldSize)

    // To do
}

void CSLayout::init()
{
    if (_wgt) _wgt->setLayout(this);
}

void CSLayout::actualRefresh()
{
    // Clear CSLayout
    clearLayout(_wgt);

    // Reset CSLayout
    resetLayout();

    // Reset container
    _listOldItems = _listItems;
}

void CSLayout::clearLayout(QWidget *wgt)
{
    if (!wgt) return;

    for (auto item : _listOldItems)
    {
        if (_listItems.contains(item)) continue;
        item->setParent(nullptr);
        item->setHidden(true);
    }
}

void CSLayout::resetLayout()
{
    // To do
}

} // End of namespace `cs`
