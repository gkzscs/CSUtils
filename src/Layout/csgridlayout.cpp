#include "csgridlayout.h"
#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSGridLayout::CSGridLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    initMember();
}

void CSGridLayout::setRowColumnCounts(int row, int col)
{
    _rowCount = row;
    _colCount = col;

    refresh();
}

void CSGridLayout::setSpaces(int hSpace, int vSpace)
{
    _hSpace = hSpace;
    _vSpace = vSpace;

    refresh();
}

QPair<int, int> CSGridLayout::rowColumnCounts() const
{
    return qMakePair(_rowCount, _colCount);
}

QPair<int, int> CSGridLayout::spaces() const
{
    return qMakePair(_hSpace, _vSpace);
}

void CSGridLayout::resetLayout()
{
    // Set items' attributes
    if (!_wgt) return;
    for (auto item : _listItems)
    {
        item->setParent(_wgt);
        item->setHidden(false);
    }

    // Set each item's geometry
    resizeUI();
}

void CSGridLayout::initMember()
{
    setSpaces(6, 6);
}

void CSGridLayout::resizeUI()
{
    if (!_wgt) return;
    auto s = _wgt->size();

    // Set each item's geometry
    int x = _margins.left();
    int y = _margins.top();
    const int w = (s.width()-margins().left()-_margins.right()+_hSpace) / _listItems.count() - _hSpace;
    const int h = (s.height()-_margins.top()-_margins.bottom()+_vSpace) / _listItems.count() - _vSpace;

    for (int i = 0, n = _listItems.count(); i < n; ++i)
    {
        _listItems.at(i)->setGeometry(x, y, w, h);

        x += w + _hSpace;
        y += h + _vSpace;
    }
}

void CSGridLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    CSLayout::resizeSlot(s, e);

    if (s != _wgt || !_wgt || !e || e->oldSize() == e->size()) return;
    resizeUI();
}

}   // End of `cs`
