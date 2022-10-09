#include "cshboxlayout.h"
#include "Control/Base/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSHBoxLayout::CSHBoxLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    initMember();
}

void CSHBoxLayout::setSpace(int space)
{
    _space = space;
    refresh();
}

int CSHBoxLayout::space() const
{
    return _space;
}

void CSHBoxLayout::resetLayout()
{
    if (!_wgt) return;

    const int h = _wgt->height() - _margins.top() - _margins.bottom();
    const int y = _margins.top();
    int x = _margins.left();

    for (auto item : _listItems)
    {
        if (!item) continue;

        item->setParent(_wgt);
        item->setHidden(false);
        item->setGeometry(x, y, item->width(), h);

        x += item->width() + _space;
    }

    _wgt->resize(x-_space+_margins.right(), _wgt->height());
}

void CSHBoxLayout::initMember()
{
    setSpace(6);
}

void CSHBoxLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    CSLayout::resizeSlot(s, e);

    if (s != _wgt || !_wgt || !e || e->oldSize().height() == e->size().height()) return;

    const int h = e->size().height() - _margins.top() - _margins.bottom();
    for (auto item : _listItems)
    {
        if (!item) continue;
        item->resize(item->width(), h);
    }
}

}   // End of `cs`
