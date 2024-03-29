﻿#include "cswidget.h"
#include "Core/csutils.h"
#include "Control/Base/cstitlebar.h"
#include "Layout/cslayout.h"
#include "Core/csappevent.h"


namespace cs
{   // Start of namespace `cs`

CSWidget::CSWidget(QWidget *parent)
    : QWidget(parent)
{
    _layout = nullptr;
}

CSWidget::~CSWidget()
{
//    DELETE_Q_POINTER(_layout);
    _layout = nullptr;
}

void CSWidget::setCSLayout(CSLayout *layout)
{
    if (_layout && _layout != layout)
    {
        _layout->deleteLater();
    }

    _layout = layout;
    if (layout) layout->setWidget(this);
}

CSLayout *CSWidget::cslayout() const
{
    return _layout;
}

QPoint CSWidget::globalPos() const
{
    return mapToGlobal(QPoint(0, 0));
}

void CSWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    // Enable style sheet
    CSUtils::enableStyleSheet(this);
}

void CSWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

//    emit CSAppEvent::instance()->resizeSignal(this, event);
    emit resizeSignal(this, event);
}

} // End of namespace `cs`
