#include "cslayout.h"
#include "Core/csappevent.h"
#include "Control/Base/cswidget.h"


namespace cs
{   // Start of namespace `cs`

CSLayout::CSLayout(CSWidget *wgt)
    : CSContainer<QWidget>(), _wgt(wgt)
{
    initMember();
    initSignalSlot();
}

CSLayout::~CSLayout()
{
    _wgt = nullptr;
}

// Can not be called by user, you should use `CSWidget::setLayout()`
void CSLayout::setWidget(CSWidget *wgt)
{
    _wgt = wgt;
    if (!wgt) return;

    refresh();
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

/**
 * @brief Must over write functions about release memory of items, or the process would crash,
 * clear old item list before refresh
 */
void CSLayout::deepClear()
{
    _listOldItems.clear();

    CSContainer<QWidget>::deepClear();
}

/**
 * @brief Refresh the layout if received resize signals
 */
void CSLayout::tryRefresh()
{
    if (!_resized) return;

    refresh();
}

void CSLayout::refresh()
{
    _resized = true;

    // Here can not add the line of code below, or the ui will be very strange
//    if (!_wgt || !_wgt->isVisible()) return;
    if (_batchOn) return;

    actualRefresh();
    _resized = false;
}

void CSLayout::actualRefresh()
{
    // Clear layout
    clearLayout();

    // Reset layout
    resetLayout();

    // Reset container
    refreshOldItems();
}

void CSLayout::clearLayout()
{
    for (auto item : _listOldItems)
    {
        if (!item || _listItems.contains(item)) continue;
        item->setParent(nullptr);
        item->setHidden(true);
    }
}

void CSLayout::resetLayout()
{
    // To do
}

void CSLayout::initMember()
{
    _resized = false;
    _margins = QMargins(0, 0, 0, 0);
}

void CSLayout::initSignalSlot()
{
    connect(CSAppEvent::instance(), &CSAppEvent::resizeSignal, this, &CSLayout::resizeSlot);
}

/**
 * @brief Refresh the widget that owns the layout
 * @param s
 * @param e
 */
void CSLayout::refreshByOuterWidget(QWidget *s, QResizeEvent *e)
{
    Q_UNUSED(s)
    Q_UNUSED(e)

    // To do
}

/**
 * @brief Refresh widget inside the layout
 * @param s
 * @param e
 */
void CSLayout::refreshByInnerWidgets(QWidget *s, QResizeEvent *e)
{
    Q_UNUSED(s)
    Q_UNUSED(e)

    // To do
}

void CSLayout::refreshOldItems()
{
    // Clear container
    _listOldItems.clear();

    // Reset container
    _listOldItems = _listItems;
}

void CSLayout::resizeSlot(QWidget *s, QResizeEvent *e)
{
    Q_UNUSED(s)
    Q_UNUSED(e)

    // Can not call `_wgt->isVisible()`, or the progress will crash
//    if (_wgt && _wgt->isVisible() /*&& e && e->oldSize() != QSize(-1, -1)*/)
    {
        refreshByInnerWidgets(s, e);
        refreshByOuterWidget(s, e);
//        return;
    }

    if (s && (s == _wgt || _listItems.contains(s))) _resized = true;
}

}
