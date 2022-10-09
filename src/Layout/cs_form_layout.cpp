#include "cs_form_layout.h"
#include "Control/Base/cswidget.h"


namespace cs
{

CSFormLayout::CSFormLayout(CSWidget *wgt)
    : cs::CSLayout(wgt)
{
    init_member();
}

void CSFormLayout::set_spaces(int hSpace, int vSpace)
{
    _space_h = hSpace;
    _space_v = vSpace;
    refresh();
}

void CSFormLayout::set_horizontal_space(int space)
{
    _space_h = space;
    refresh();
}

void CSFormLayout::set_vertical_space(int space)
{
    _space_v = space;
    refresh();
}

int CSFormLayout::horizontal_space() const
{
    return _space_h;
}

int CSFormLayout::vertical_space() const
{
    return _space_v;
}

void CSFormLayout::set_column_count(int n)
{
    if (n <= 0) return;

    _col_count = n;
    refresh();
}

int CSFormLayout::column_count() const
{
    return _col_count;
}

void CSFormLayout::init_member()
{
    _space_h = 6;
    _space_v = 6;
    _col_count = 1;
}

void CSFormLayout::resetLayout()
{
    if (!_wgt) return;

    // Set items' geometries
    recalc_all_properties();
    reset_all_geometries();

    // Set items' attributes
    for (auto item : _listItems)
    {
        if (!item) continue;

        item->setParent(_wgt);
        item->setHidden(false);
    }

    // Resize `_wgt`
    int more = ((_listItems.count() % _col_count > 0) ? 1 : 0);
    int h = _margins.top() + _margins.bottom() + (_row_h + _space_v)
            * (more + _listItems.count() / _col_count) - _space_v;
    _wgt->resize(_wgt->width(), h);
}

void CSFormLayout::recalc_all_properties()
{
    if (!_wgt) return;

    _col_w = (_wgt->width() - _margins.left() - _margins.right() + _space_h) / _col_count - _space_h;
    _row_h = 0;
    if (!_listItems.isEmpty())
    {
        _row_h = _listItems.first()->height();
    }
}

void CSFormLayout::reset_all_geometries()
{
    if (!_wgt) return;

    const int left = _margins.left();
    const int top = _margins.top();
    int w = _col_w;
    int h = _row_h;

    for (int i = 0, n = _listItems.size(); i < n; ++i)
    {
        auto item = _listItems.at(i);
        if (!item) continue;

        int row = i / _col_count;
        int col  = i % _col_count;
        int x = left + (w + _space_h) * col;
        int y = top + (h + _space_v) * row;
        item->setGeometry(x, y, w, h);
    }
}

void CSFormLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    CSLayout::resizeSlot(s, e);

    if (s != _wgt || !_wgt || !e || e->oldSize().width() == e->size().width()) return;

    recalc_all_properties();
    reset_all_geometries();
}


}   // cs
