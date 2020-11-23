#ifndef CSContainer_H
#define CSContainer_H

<<<<<<< HEAD
#include "Control/cswidget.h"
=======
#include <QObject>
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013
#include <QTime>


namespace cs
<<<<<<< HEAD
{   // Start of namespace `cs`
=======
{
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

template <typename T>
class CSUTILS_EXPORT CSContainer : public QObject
{
public:
    CSContainer();
<<<<<<< HEAD
    virtual ~CSContainer();
=======
    virtual ~CSContainer() override;
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

    virtual bool add(T *item);
    virtual bool insert(int idx, T *item);
    virtual bool remove(T *item);
    virtual bool remove(int idx);
    virtual bool replace(T *oldItem, T *newItem);
    virtual bool replace(int idx, T *item);
    virtual bool move(int oldIdx, int newIdx);
    virtual bool swap(int idx1, int idx2);
    virtual T *at(int idx) const;
    virtual int indexOf(T *item) const;
    virtual void clear();

    virtual int count() const;
    virtual bool isEmpty() const;
    virtual QList<T *> allItems() const;

protected:
<<<<<<< HEAD
    virtual void init();
=======
    void init();
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

protected:
    virtual void refresh();
    virtual void actualRefresh();
    virtual void dealAdd(T *item);
    virtual void dealRemove(T *item);
<<<<<<< HEAD
    virtual void clearLayout(QWidget *wgt);
=======
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

protected:
    QList<T *> _listItems;
    QTime _lastRefresh;
    bool _flag;

};

<<<<<<< HEAD
}   // End of namespace `cs`
=======
}
>>>>>>> 78105573c0b48a6f559f0788e5d1ba19a49cb013

#endif // CSContainer_H
