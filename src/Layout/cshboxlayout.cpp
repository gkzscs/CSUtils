#include "cshboxlayout.h"


namespace cs
{   // Start of namespace `cs`

CSHBoxLayout::CSHBoxLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    init();
}

void CSHBoxLayout::setSpace(int n)
{
    _space = n;
    refresh();
}

int CSHBoxLayout::space() const
{
    return _space;
}

void CSHBoxLayout::changeSize(const QSize &newSize, const QSize &oldSize)
{
    if (newSize.height() == oldSize.height()) return;

    const int h = _wgt->width() - _margins.top() - _margins.bottom();
    for (auto item : _listItems) item->resize(item->width(), h);
}

void CSHBoxLayout::init()
{
    _space = 0;
}

void CSHBoxLayout::resetLayout()
{
    if (!_wgt) return;

    const int h = _wgt->width() - _margins.top() - _margins.bottom();
    const int y = _margins.top();
    int x = _margins.left();

    for (auto item : _listItems)
    {
        item->setParent(_wgt);
        item->setHidden(false);
        item->setGeometry(x, y, item->width(), h);

        x += item->width() + _space;
    }

    _wgt->resize(x-_space+_margins.right(), _wgt->height());
}

}   // End of namespace `cs`
