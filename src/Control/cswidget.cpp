#include "cswidget.h"
#include "Core/csutils.h"
#include "Layout/cslayout.h"
#include "Core/csappevent.h"


namespace cs
{   // Start of namespace `cs`

CSWidget::CSWidget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

CSWidget::~CSWidget()
{
    // Do nothing
}

QPoint CSWidget::globalPos() const
{
    return mapToGlobal(QPoint(0, 0));
}

void CSWidget::setLayout(CSLayout *layout)
{
    if (_layout)
    {
        _layout->deleteLater();
    }

    _layout = layout;
    layout->refreshUI();
}

void CSWidget::init()
{
    initMember();
    initUI();
    initSignalSlot();
}

void CSWidget::initMember()
{
    _layout = nullptr;
}

void CSWidget::initUI()
{
    // Do nothing
}

void CSWidget::initSignalSlot()
{
    // Do nothing
}

void CSWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    // Enable style sheet
    CSUtils::enableStyleSheet(this);
}

void CSWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)

    if (_layout) emit CSAppEvent::instance()->resizeSignal(this, event);
}

} // End of namespace `cs`
