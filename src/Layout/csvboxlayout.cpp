#include "csvboxlayout.h"
#include "Control/cswidget.h"


namespace cs
{

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

    const int h = _wgt->height() - _margins.top() - _margins.bottom();
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

}

