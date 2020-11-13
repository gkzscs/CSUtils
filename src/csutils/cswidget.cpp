#include "cswidget.h"
#include "csutils.h"


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

void CSWidget::init()
{
    initMember();
    initUI();
    initSignalSlot();
}

void CSWidget::initMember()
{
    // Do nothing
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
