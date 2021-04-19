#ifndef CSGRIDLAYOUT_H
#define CSGRIDLAYOUT_H

#include "Layout/cslayout.h"


namespace cs
{

class CSUTILS_EXPORT CSGridLayout : public CSLayout
{
    Q_OBJECT

public:
    CSGridLayout(CSWidget *wgt = nullptr);

    void setRowColumnCounts(int row, int col);
    void setSpaces(int hSpcae, int vSpcae);
    QPair<int, int> rowColumnCounts() const;
    QPair<int, int> spaces() const;

protected:
    virtual void resetLayout() override;

protected:
    void initMember();

protected:
    void resizeUI();

protected slots:
    virtual void resizeSlot(QObject *s, QResizeEvent *e) override;

protected:
    int _rowCount;
    int _colCount;
    int _hSpace;
    int _vSpace;

};

}   // End of `cs`

#endif // CSGRIDLAYOUT_H
