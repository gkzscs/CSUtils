#include "cslayout.h"
#include "Core/csappevent.h"
#include "Control/cswidget.h"


namespace cs
{

CSLayout::CSLayout(CSWidget *wgt)
    : CSContainer<QWidget>(), _wgt(wgt)
{
    init();
}

CSLayout::~CSLayout()
{
    _wgt = nullptr;
}

void CSLayout::setMargins(QMargins m)
{
    _margins = m;
    refreshUI();
}

void CSLayout::setMargins(int left, int top, int right, int bottom)
{
    auto m = QMargins(left, top, right, bottom);
    setMargins(m);
}

QMargins CSLayout::margins() const
{
    return _margins;
}

void CSLayout::refreshUI()
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
        if (_listItems.contains(item)) continue;
        item->setParent(nullptr);
        item->setHidden(true);
    }
}

void CSLayout::init()
{
    initMember();
    initUI();
    initSignalSlot();
}

void CSLayout::initMember()
{
    _margins = QMargins(0, 0, 0, 0);
}

void CSLayout::initUI()
{

}

void CSLayout::initSignalSlot()
{
    connect(CSAppEvent::instance(), &CSAppEvent::resizeSignal, this, &CSLayout::resizeSlot);
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

    // To do
}

}
