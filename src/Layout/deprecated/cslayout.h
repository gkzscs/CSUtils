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
    ~CSLayout() override;

    void setWidget(CSWidget *wgt);
    void setMargins(QMargins m);
    void setMargins(int left, int top, int right, int bottom);
    QMargins margins() const;

    // Overwrite the function of deep clear
    void deepClear();
    void tryRefresh();

protected:
    void refresh() override;
    void actualRefresh() override;
    virtual void clearLayout();
    virtual void resetLayout() = 0;

protected:
    void initMember();
    void initSignalSlot();

protected:
    virtual void refreshByOuterWidget(QWidget *s, QResizeEvent *e) = 0;
    virtual void refreshByInnerWidgets(QWidget *s, QResizeEvent *e) = 0;
    virtual void refreshOldItems();

protected slots:
    void resizeSlot(QWidget *s, QResizeEvent *e);

protected:
    bool _resized;
    CSWidget *_wgt;
    QMargins _margins;
    QList<QWidget *> _listOldItems;

};

}   // End of namespace `cs`


#endif // CSLAYOUT_H
