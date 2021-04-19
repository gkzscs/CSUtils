#include "csvboxlayout.h"
#include "Control/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSVBoxLayout::CSVBoxLayout(CSWidget *wgt)
    : CSLayout(wgt)
{
    initMember();
}

void CSVBoxLayout::setSpace(int space)
{
    _space = space;
    refresh();
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
    setSpace(6);
}

void CSVBoxLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    CSLayout::resizeSlot(s, e);

    if (s != _wgt || !_wgt || !e || e->oldSize().width() == e->size().width()) return;

    const int w = e->size().width() - _margins.left() - _margins.right();
    for (auto item : _listItems) item->resize(w, item->height());
}

}   // End of namespace `cs`


