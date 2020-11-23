#include "csvboxlayout.h"
#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSVBoxLayout::CSVBoxLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    init();
}

void CSVBoxLayout::setSpace(int space)
{
    _space = space;
    refreshUI();
}

int CSVBoxLayout::space() const
{
    return _space;
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

void CSVBoxLayout::initMember()
{
    _space = 6;
}

void CSVBoxLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    if (s != _wgt || !_wgt || e->oldSize().height() == e->size().height()) return;

    const int h = e->size().height() - _margins.top() - _margins.bottom();
    for (auto item : _listItems) item->resize(item->width(), h);
}

}   // End of namespace `cs`


