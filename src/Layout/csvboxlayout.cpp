#include "csvboxlayout.h"
#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSVBoxLayout::CSVBoxLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    init();
}

void CSVBoxLayout::setSpace(int n)
{
    _space = n;
    refresh();
}

int CSVBoxLayout::space() const
{
    return _space;
}

void CSVBoxLayout::changeSize(const QSize &newSize, const QSize &oldSize)
{
    if (newSize.width() == oldSize.width()) return;

    const int w = _wgt->width() - _margins.left() - _margins.right();
    for (auto item : _listItems) item->resize(w, item->height());
}

void CSVBoxLayout::init()
{
    _space = 0;
}

void CSVBoxLayout::resetLayout()
{
    if (!_wgt) return;

    const int w = _wgt->width() - _margins.left() - _margins.right();
    const int x = _margins.left();
    int y = _margins.top();

    for (auto item : _listItems)
    {
        item->setParent(_wgt);
        item->setGeometry(x, y, w, item->height());
        item->setHidden(false);

        y += item->height() + _space;
    }

    _wgt->resize(_wgt->width(), y-_space+_margins.bottom());
}

}   // End of namespace `cs`
