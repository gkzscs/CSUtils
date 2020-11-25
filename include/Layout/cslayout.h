#ifndef CSLAYOUT_H
#define CSLAYOUT_H

#include "Core/cscontainer.h"


namespace cs
{   // Start of namespace `cs`

class CSWidget;

class CSUTILS_EXPORT CSLayout : public CSContainer<QWidget>
{
    Q_OBJECT

public:
    CSLayout(CSWidget *wgt = nullptr);
    virtual ~CSLayout() override;

    virtual void refreshUI();

    void setMargins(QMargins m);
    void setMargins(int left, int top, int right, int bottom);
    QMargins margins() const;

protected:
    virtual void actualRefresh() override;
    virtual void clearLayout();
    virtual void resetLayout() = 0;

protected:
    virtual void init();
    virtual void initMember();
    virtual void initUI();
    virtual void initSignalSlot();

protected:
    virtual void refreshOldItems();

protected slots:
    virtual void resizeSlot(QObject *s, QResizeEvent *e);

protected:
    CSWidget *_wgt;
    QMargins _margins;
    QList<QWidget *> _listOldItems;

};


/************************************* Extern template class **************************************/
extern template class CSContainer<QWidget>;

}   // End of namespace `cs`


#endif // CSLAYOUT_H
