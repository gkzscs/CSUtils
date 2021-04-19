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
    _rowCount = (row < 1 ? 1 : row);
    _colCount = (col < 1 ? 1 : col);

    refresh();
}

void CSGridLayout::setSpaces(int hSpace, int vSpace)
{
    _hSpace = (hSpace < 0 ? 0 : hSpace);
    _vSpace = (vSpace < 0 ? 0 : vSpace);

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
    _rowCount = 3;
    _colCount = 3;
    _hSpace = 6;
    _vSpace = 6;
}

void CSGridLayout::resizeUI()
{
    if (!_wgt) return;
    auto s = _wgt->size();

    // Set each item's geometry
    int x = _margins.left();
    int y = _margins.top();
    const int w = (s.width()-margins().left()-_margins.right()+_hSpace) / _colCount - _hSpace;
    const int h = (s.height()-_margins.top()-_margins.bottom()+_vSpace) / _rowCount - _vSpace;

    for (int i = 0, n = _listItems.count(); i < n; ++i)
    {
        _listItems.at(i)->setGeometry(x, y, w, h);

        x += w + _hSpace;
        if ((i+1) % _colCount == 0)
        {
            x = _margins.left();
            y += h + _vSpace;
        }
    }
}

void CSGridLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    CSLayout::resizeSlot(s, e);

    if (s != _wgt || !_wgt || !e || e->oldSize() == e->size()) return;
    resizeUI();
}

}   // End of `cs`
