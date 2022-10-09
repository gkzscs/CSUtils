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

void CSLayout::dealAdd(QWidget *item)
{
    auto wgt = dynamic_cast<cs::CSWidget *>(item);
    if (!wgt) return;

    connect(wgt, &cs::CSWidget::resizeSignal, this, &cs::CSLayout::resizeSlot);
}

void CSLayout::dealAdd(const QList<QWidget *> &listItems)
{
    for (auto item : listItems)
    {
        auto wgt = dynamic_cast<cs::CSWidget *>(item);
        if (!wgt) return;

        connect(wgt, &cs::CSWidget::resizeSignal, this, &cs::CSLayout::resizeSlot);
    }
}

void CSLayout::dealRemove(QWidget *item)
{
    auto wgt = dynamic_cast<cs::CSWidget *>(item);
    if (!wgt) return;

    disconnect(wgt, &cs::CSWidget::resizeSignal, this, &cs::CSLayout::resizeSlot);
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
    _margins = QMargins(0, 0, 0, 0);
}

void CSLayout::initSignalSlot()
{
//    connect(CSAppEvent::instance(), &CSAppEvent::resizeSignal, this, &CSLayout::resizeSlot);
    connect(_wgt, &cs::CSWidget::resizeSignal, this, &cs::CSLayout::resizeSlot);
}

void CSLayout::refreshOldItems()
{
    // Clear container
    _listOldItems.clear();

    // Reset container
    _listOldItems = _listItems;
}

void CSLayout::resizeSlot(QObject *s, QResizeEvent *e)
{
    Q_UNUSED(s)
    Q_UNUSED(e)

    auto wgt = dynamic_cast<QWidget *>(s);
    if (!wgt) return;
    if (!_listItems.contains(wgt)) return;

    refresh();
}

}
