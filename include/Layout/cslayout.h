<<<<<<< HEAD
#ifndef CSLayout_H
#define CSLayout_H
=======
#ifndef CSLAYOUT_H
#define CSLAYOUT_H
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

#include "Core/cscontainer.h"


namespace cs
<<<<<<< HEAD
{   // Start of namespace `cs`

class CSUTILS_EXPORT CSLayout : public CSContainer<QWidget>
{
=======
{

class CSWidget;

class CSUTILS_EXPORT CSLayout : public CSContainer<QWidget>
{
    Q_OBJECT

>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
public:
    CSLayout(CSWidget *wgt = nullptr);
    virtual ~CSLayout() override;

<<<<<<< HEAD
    void setMargins(QMargins m);
    void setMargins(int left, int top, int right, int bottom);
    QMargins margins() const;
    virtual void refresh() override;
    virtual void changeSize(const QSize &newSize, const QSize &oldSize);

protected:
    virtual void init() override;

    virtual void actualRefresh() override;
    virtual void clearLayout(QWidget *wgt) override;
    virtual void resetLayout() = 0;

protected:
    CSWidget *_wgt;
    QMargins _margins;

    QList<QWidget *> _oldItems;

};


/************************************* Extern template class **************************************/
extern template class CSContainer<QWidget>;

}   // End of namespace `cs`

#endif // CSLayout_H
=======
    virtual void refreshUI();

    void setMargins(QMargins m);
    void setMargins(int left, int top, int right, int bottom);
    QMargins margins() const;

protected:
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

}
#endif // CSLAYOUT_H
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
