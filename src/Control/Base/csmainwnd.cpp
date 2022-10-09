#include "csmainwnd.h"


namespace cs
{

CSMainWnd::CSMainWnd(QWidget *parent)
    : cs::CSAdjustableWgt(parent)
{
    initMember();
}

CSMainWnd::~CSMainWnd()
{
    DELETE_Q_POINTER(_barTitle);
    DELETE_Q_POINTER(_panelCenter);
}

CSTitleBar *CSMainWnd::cstitleBar() const
{
    return _barTitle;
}

void CSMainWnd::resizeEvent(QResizeEvent *e)
{
    CSAdjustableWgt::resizeEvent(e);
    resizeUI();
    _barTitle->updateMaximizeStatus();
}

void CSMainWnd::initMember()
{
    _barTitle = new CSTitleBar(this);
    _panelCenter = new QWidget(this);

    // Set object name
    _barTitle->setObjectName("bar_title");
    _panelCenter->setObjectName("panel_title");
}

void CSMainWnd::resizeUI()
{
    // Resize title bar
    const int titleBarH = 40;
    int panelCenterH = height() - titleBarH;

    _barTitle->setGeometry(0, 0, width(), titleBarH);
    _panelCenter->setGeometry(0, titleBarH, width(), panelCenterH);
}

}   // `cs`

