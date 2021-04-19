#ifndef CSHBOXLAYOUT_H
#define CSHBOXLAYOUT_H

#include "Layout/cslayout.h"


namespace cs
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSHBoxLayout : public CSLayout
{
    Q_OBJECT

public:
    CSHBoxLayout(CSWidget *wgt = nullptr);

    void setSpace(int space);
    int space() const;

protected:
    virtual void resetLayout() override;

protected:
    void initMember();

protected slots:
    virtual void resizeSlot(QObject *s, QResizeEvent *e) override;

protected:
    int _space;

};

}   // End of namespace `cs`


#endif // CSHBOXLAYOUT_H
