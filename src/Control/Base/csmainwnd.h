#ifndef CSMAINWND_H
#define CSMAINWND_H

#include "Control/Base/csadjustablewgt.h"


namespace cs
{

class CSUTILS_EXPORT CSMainWnd : public cs::CSAdjustableWgt
{
    Q_OBJECT

public:
    CSMainWnd(QWidget *parent = nullptr);
    ~CSMainWnd() override;

    CSTitleBar *cstitleBar() const;
    QWidget *centerPanel() const;

protected:
    void resizeEvent(QResizeEvent *e) override;

private:
    void initMember();

private:
    void resizeUI();

protected:
    CSTitleBar *_barTitle;
    QWidget *_panelCenter;

};

}   // `cs`

#endif // CSMAINWND_H
